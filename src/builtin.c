#include <sys/types.h>
#include <sys/wait.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "debug.h"
#include "frame.h"
#include "builtin.h"

static int
builtin_cd(struct frame *f, int argc, char *const *argv)
{
	assert(f != NULL);
	assert(argc >= 1);
	assert(argv != NULL);

	if (argc != 2) {
		fprintf(stderr, "usage: cd <dir>\n");
		return 1;
	}

	(void) f;

	/* TODO: support argc=0 to chdir to $home */

	if (-1 == chdir(argv[1])) {
		return -1;
	}

	return 0;
}

static int
builtin_exec(struct frame *f, int argc, char *const *argv)
{
	assert(f != NULL);
	assert(argc >= 1);
	assert(argv != NULL);

	if (-1 == frame_export(f)) {
		return -1;
	}

	(void) execv(argv[0], argv);

	perror(argv[0]);

	return -1;
}

static int
builtin_wait(struct frame *f, int argc, char *const *argv)
{
	int status;
	pid_t pid;
	int r;

	assert(f != NULL);
	assert(argc >= 1);
	assert(argv != NULL);

	if (argc != 2) {
		fprintf(stderr, "usage: wait <pid>\n");
		return 1;
	}

	(void) f;

	/* TODO: support argc=0 to wait() for all children */

	/* TODO: strtol and some error-checking */
	pid = atol(argv[1]);

	(void) execv(argv[0], argv);
	if (-1 == waitpid(pid, &status, 0)) {
		return -1;
	}

	if (!WIFEXITED(status)) {
		/* TODO: call a hook */
		/* XXX: how to set $? here? */
		return -1;
	}

	r = WEXITSTATUS(status);

	if (debug & DEBUG_EXEC) {
		fprintf(stderr, "# $?=%d\n", r);
	}

	return r;
}

static int
builtin_fork(struct frame *f, int argc, char *const *argv)
{
	pid_t pid;

	assert(f != NULL);
	assert(argc >= 1);
	assert(argv != NULL);

	if (argc > 1) {
		fprintf(stderr, "usage: fork\n");
		return -1;
	}

	(void) f;

	/* TODO: support argc=1 for various rfork-style flags */

	pid = fork();
	switch (pid) {
	case -1:
		return -1;

	case 0:
		/* TODO: store $pid = getpid() */

		return 0;

	default:
		return pid;
	}
}

/* TODO: eventually to be replaced by a shell function */
static int
builtin_spawn(struct frame *f, int argc, char *const *argv)
{
	char *fork_argv[] = { "fork", NULL };
	char *wait_argv[] = { "wait", NULL, NULL };
	pid_t pid;
	char s[128];

	assert(f != NULL);
	assert(argc >= 1);
	assert(argv != NULL);

	pid = builtin_fork(f, 1, fork_argv);
	switch (pid) {
	case -1:
		return -1;

	case 0:
		(void) builtin_exec(f, argc, argv);

		exit(errno);

	default:
		sprintf(s, "%ld", (long) pid); /* XXX */

		wait_argv[1] = s;

		if (-1 == builtin_wait(f, 2, wait_argv)) {
			return -1;
		}

		return 0;
	}
}

int
builtin(struct frame *f, int argc, char *const *argv)
{
	size_t i;

	struct {
		const char *name;
		int (*f)(struct frame *f, int, char *const *);
	} a[] = {
		{ "cd",    builtin_cd    },
		{ "exec",  builtin_exec  },
		{ "wait",  builtin_wait  },
		{ "fork",  builtin_fork  },
		{ "spawn", builtin_spawn }
	};

	if (argc < 1) {
		errno = EINVAL;
		return -1;
	}

	assert(f != NULL);
	assert(argv != NULL);
	assert(argv[0] != NULL);

	/* TODO: bsearch */
	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(argv[0], a[i].name)) {
			return a[i].f(f, argc, argv);
		}
	}

	return builtin_spawn(f, argc, argv);
}

