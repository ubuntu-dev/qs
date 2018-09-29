/*
 * Automatically generated from the files:
 *	src/parser.sid
 * and
 *	src/parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 74 "src/parser.act"


	#include <stdio.h>

	typedef struct lex_state * lex_state;
	typedef struct act_state * act_state;

	int
	parse(struct lex_state *l,
		int (*dispatch)(struct code *));

#line 25 "src/parser.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void p_script(lex_state, act_state);
/* BEGINNING OF TRAILER */

#line 339 "src/parser.act"


#line 35 "src/parser.h"

/* END OF FILE */
