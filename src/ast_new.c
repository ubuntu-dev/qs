#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

struct ast_list *
ast_new_list(size_t n, const char *s)
{
	struct ast_list *list;

	assert(s != NULL);

	list = malloc(sizeof *list + n + 1);
	if (list == NULL) {
		return NULL;
	}

	list->s    = (char *) list + sizeof *list;
	list->next = NULL;

	memcpy(list->s, s, n);
	list->s[n] = '\0';

	return list;
}

struct ast_node *
ast_new_node_list(struct ast_list *list)
{
	struct ast_node *node;

	assert(list != NULL);

	node = malloc(sizeof *node);
	if (node == NULL) {
		return NULL;
	}

	node->type   = AST_LIST;
	node->u.list = list;
	node->next   = NULL;

	return node;
}

struct ast_node *
ast_new_node_node(struct ast_node *child)
{
	struct ast_node *node;

	assert(child != NULL);

	node = malloc(sizeof *node);
	if (node == NULL) {
		return NULL;
	}

	node->type   = AST_NODE;
	node->u.node = child;
	node->next   = NULL;

	return node;
}

