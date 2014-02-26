#ifndef VAR_H
#define VAR_H

struct ast;

struct var {
	const char *name;
	struct ast *a;
	struct var *next;
};

struct var *
var_set(struct var **v, const char *name, struct ast *a);

struct ast *
var_get(struct var *v, const char *name);

void
var_free(struct var *v);

#endif

