#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "../frame.h"
#include "../ast.h"

#include "op.h"

int
eval_ast(struct ast *a, struct ast **out);

int
eval_op_and(struct ast *a, struct ast *b)
{
	struct ast *q;

	/* XXX: i don't like this at all */
	if (-1 == eval_ast(a, &q)) {
		return -1;
	}

	if (q != NULL) {
		errno = EINVAL;
		return -1;
	}

	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	if (-1 == eval_ast(b, &q)) {
		return -1;
	}

	if (q != NULL) {
		errno = EINVAL;
		return -1;
	}

	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int
eval_op_or(struct ast *a, struct ast *b)
{
	struct ast *q;

	/* XXX: i don't like this at all */
	if (-1 == eval_ast(a, &q)) {
		return -1;
	}

	if (q != NULL) {
		errno = EINVAL;
		return -1;
	}

	if (status == EXIT_SUCCESS) {
		return EXIT_SUCCESS;
	}

	if (-1 == eval_ast(b, &q)) {
		return -1;
	}

	if (q != NULL) {
		errno = EINVAL;
		return -1;
	}

	if (status == EXIT_SUCCESS) {
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int
eval_op_join(struct ast *a, struct ast *b)
{
	/* TODO: map down based on $FS (field seperator) */
	(void) a;
	(void) b;

	return -1;
}

int
eval_op_pipe(struct ast *a, struct ast *b)
{
	/* TODO */
	(void) a;
	(void) b;

	errno = ENOSYS;
	return -1;
}

int
eval_op_assign(struct ast *a, struct ast *b)
{
	/* TODO */
	(void) a;
	(void) b;

	errno = ENOSYS;
	return -1;
}

int
eval_op_sep(struct ast *a, struct ast *b)
{
	struct ast *q;

	if (a != NULL) {
		if (-1 == eval_ast(a, &q)) {
			return -1;
		}

		if (q != NULL) {
			errno = EINVAL;
			return -1;
		}
	}

	if (b != NULL) {
		if (-1 == eval_ast(b, &q)) {
			return -1;
		}

		if (q != NULL) {
			errno = EINVAL;
			return -1;
		}
	}

	return 0;
}
