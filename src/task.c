/*
 * Copyright 2013-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <sys/types.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "task.h"
#include "proc.h"
#include "frame.h"

struct task *
task_add(struct task **head, struct frame *frame, struct code *code)
{
	struct task *new;

	assert(head != NULL);
	assert(frame != NULL);

	new = malloc(sizeof *new);
	if (new == NULL) {
		return NULL;
	}

	if (-1 == frame_refcount(frame, +1)) {
		free(new);
		return NULL;
	}

	new->frame = frame;
	new->code  = code;
	new->data  = NULL;
	new->pid   = -1;

	new->ts.s = NULL;

	new->next = *head;
	*head = new;

	return new;
}

void
task_remove(struct task **head, struct task *task)
{
	struct task **next, **t;

	assert(head != NULL);

	/*
	 * On eval error we may have left-over frames still pushed here;
	 * unwind until the branch point is reached (i.e. a frame which
	 * belongs to our parent task).
	 */
	{
		if (-1 == frame_refcount(task->frame, -1)) {
			perror("frame_refcount");
		}

		while (task->frame != NULL && task->frame->refcount == 0) {
			struct frame *q;

			q = frame_pop(&task->frame);
			frame_free(q);
		}
	}

	for (t = head; *t != NULL; t = next) {
		next = &(*t)->next;

		if (*t == task) {
			free(*t);
			*t = *next;
			return;
		}
	}
}

struct task *
task_next(const struct task *tasks)
{
	const struct task *t;

	assert(tasks != NULL);

	for (t = tasks; t != NULL; t = t->next) {
		if (t->pid != -1) {
			/* blocked on waiting for child */
			continue;
		}

		return (struct task *) t;
	}

	/*
	 * All tasks are blocked on waiting for their respective child.
	 * Now the caller should wait(2) for whichever raises SIGCHLD first,
	 * and re-enter for that child's task.
	 */

	return NULL;
}

struct task *
task_find(const struct task *head, pid_t pid)
{
	const struct task *p;

	assert(pid != -1);

	for (p = head; p != NULL; p = p->next) {
		if (p->pid == pid) {
			return (struct task *) p;
		}
	}

	return NULL;
}

void
task_prioritise(struct task **head, struct task *task)
{
	struct task **t;

	assert(head != NULL);
	assert(task != NULL);

	for (t = head; *t != task; t = &(*t)->next)
		;

	*t = (*t)->next;

	task->next = *head;
	*head = task;
}

/*
 * Returns the number of newly prioritised tasks
 * which were waiting for the given PID,
 * or -1 on error.
 */
int
task_wait(struct task **head, pid_t pid, int options)
{
	int n;

	assert(head != NULL);

	/*
	 * When we're called here, at least one SIGCHLD was delivered, so there
	 * must be at least one child waiting. There may also be more, and so we
	 * wait() repeatedly until they're all reaped.
	 *
	 * A caller may also want to block, depending on the options flag passed.
	 * Subsequent calls should never block, because there may be no further
	 * children waiting. So subsequent calls are passed WNOHANG.
	 */

	n = 0;

	for (;;) {
		struct task *t;
		pid_t r;

		r = proc_wait(pid, options);

		if (r == -1 && errno == ECHILD) {
			/* TODO: DEBUG_WAIT "no child" */
			return 0;
		}

		if (r == -1) {
			return -1;
		}

		if (r == 0) {
			/* children exist, but not dead yet */
			assert(options & WNOHANG);
			break;
		}

		/*
		 * TODO: maybe set some variables about the child here; stuff from waitpid()
		 *
		 * If this is called from inside the SIGCHLD handler
		 * (rather than using a self pipe), I'd need to pre-populate these variables,
		 * because I won't malloc(3) inside a signal handler.
		 */

		t = task_find(*head, r);
		if (t == NULL) {
			fprintf(stderr, "stray child, PID=%lu\n", (unsigned long) r);
			continue;
		}

		/* This task is no longer waiting for a child */
		t->pid = -1;

		task_prioritise(head, t);

		n++;

		if (pid != -1) {
			break;
		}

		options |= WNOHANG;
	}

	return n;
}

