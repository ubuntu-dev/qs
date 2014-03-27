#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "debug.h"
#include "pipe.h"
#include "code.h"

const char *
code_name(enum code_type type)
{
	switch (type) {
	case CODE_NULL: return "null";
	case CODE_ANON: return "anon";
	case CODE_RET:  return "ret";
	case CODE_DATA: return "data";
	case CODE_NOT:  return "not";
	case CODE_TICK: return "tick";
	case CODE_CALL: return "call";
	case CODE_EXEC: return "exec";
	case CODE_IF:   return "if";
	case CODE_JOIN: return "join";
	case CODE_PIPE: return "pipe";
	case CODE_SET:  return "set";
	}

	return "?";
}

struct code *
code_anon(struct code **head, struct frame *frame,
	enum code_type type, struct code *code)
{
	struct code *new;

	assert(head != NULL);
	assert(frame != NULL);

	new = malloc(sizeof *new);
	if (new == NULL) {
		return NULL;
	}

	new->type   = type;
	new->frame  = frame;
	new->u.code = code;

	new->next = *head;
	*head = new;

	if (debug & DEBUG_STACK) {
		fprintf(stderr, "code -> %s\n", code_name(new->type));
		/* TODO: could dump code here */
	}

	return new;
}

struct code *
code_data(struct code **head, struct frame *frame,
	size_t n, const char *s)
{
	struct code *new;

	assert(head != NULL);
	assert(frame != NULL);
	assert(s != NULL);

	new = malloc(sizeof *new + n + 1);
	if (new == NULL) {
		return NULL;
	}

	new->type   = CODE_DATA;
	new->frame  = frame;
	new->u.s    = memcpy((char *) new + sizeof *new, s, n);
	new->u.s[n] = '\0';

	new->next = *head;
	*head = new;

	if (debug & DEBUG_STACK) {
		fprintf(stderr, "code -> %s \"%.*s\"\n", code_name(new->type), (int) n, s);
	}

	return new;
}

struct code *
code_pipe(struct code **head, struct frame *frame,
	struct pipe *pipe)
{
	struct code *new;

	assert(head != NULL);
	assert(frame != NULL);

	new = malloc(sizeof *new);
	if (new == NULL) {
		return NULL;
	}

	new->type   = CODE_PIPE;
	new->frame  = frame;
	new->u.pipe = pipe;

	new->next = *head;
	*head = new;

	if (debug & DEBUG_STACK) {
		fprintf(stderr, "code -> %s\n", code_name(CODE_PIPE));
		/* TODO: could dump pipe redir list here */
	}

	return new;
}

struct code *
code_push(struct code **head, struct frame *frame,
	enum code_type type)
{
	struct code *new;

	assert(head != NULL);
	assert(frame != NULL);
	assert(type != CODE_IF);
	assert(type != CODE_SET);
	assert(type != CODE_ANON);
	assert(type != CODE_DATA);
	assert(type && !(type & (type - 1)));

	new = malloc(sizeof *new);
	if (new == NULL) {
		return NULL;
	}

	new->type  = type;
	new->frame = frame;

	new->next = *head;
	*head = new;

	if (debug & DEBUG_STACK) {
		fprintf(stderr, "code -> %s\n", code_name(new->type));
	}

	return new;
}

struct code *
code_pop(struct code **head)
{
	struct code *node;

	assert(head != NULL);

	node = *head;
	*head = node->next;
	node->next = NULL;

	if (debug & DEBUG_STACK) {
		fprintf(stderr, "code <- %s\n", code_name(node->type));
	}

	return node;
}

void
code_free(struct code *code)
{
	struct code *p, *next;

	for (p = code; p != NULL; p = next) {
		next = p->next;

		free(p);
	}
}

static int
code_dumpinline(FILE *f, const struct code *code)
{
	const struct code *p;
	const struct pipe *q;

	assert(f != NULL);

	for (p = code; p != NULL; p = p->next) {
		switch (p->type) {
		case CODE_DATA:
			fprintf(f, "'%s' ", p->u.s);
			break;

		case CODE_PIPE:
			fprintf(f, "#%s", code_name(p->type));
			for (q = p->u.pipe; q != NULL; q = q->next) {
				fprintf(f, "[%d=%d]", q->lfd, q->rfd);
			}
			fprintf(f, " ");
			break;

		case CODE_IF:
		case CODE_SET:
		case CODE_ANON:
			fprintf(f, "#%s", code_name(p->type));
			fprintf(f, "{ ");
			code_dumpinline(f, p->u.code);
			fprintf(f, "} ");
			break;

		default:
			fprintf(f, "#%s ", code_name(p->type));
		}
	}

	return 0;
}

int
code_dump(FILE *f, const struct code *code)
{
	assert(f != NULL);

	code_dumpinline(f, code);

	fprintf(f, "\n");

	return 0;
}

