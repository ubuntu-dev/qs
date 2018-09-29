/*
 * Automatically generated from the files:
 *	src/parser.sid
 * and
 *	src/parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 26 "src/parser.act"


	#include <assert.h>
	#include <limits.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <ctype.h>
	#include <errno.h>

	#include <unistd.h>

	#include "debug.h"
	#include "lex.h"
	#include "code.h"
	#include "parser.h"
	#include "err.h"

	enum err_state {
		ERR_NONE,
		ERR_SYNTAX,
		ERR_ERRNO
	};

	struct act_string {
		const char *s;
		const char *e;
	};

	struct act_state {
		struct lex_tok t;
		enum lex_type save;
		enum err_state e;
		int (*dispatch)(struct code *);
	};

	typedef struct act_string string;
	typedef enum opcode opcode;
	typedef struct code *code;
	typedef struct lex_mark *mark;
	typedef const char * rule;
	typedef enum lex_type type;

	#define CURRENT_TERMINAL act_state->t.type
	#define ERROR_TERMINAL   tok_error
	#define ADVANCE_LEXER    lex_next(lex_state, &act_state->t);
	#define SAVE_LEXER(type) act_state->save   = type;
	#define RESTORE_LEXER    act_state->t.type = act_state->save;

#line 62 "src/parser.c"


#ifndef ERROR_TERMINAL
#error "-s no-numeric-terminals given and ERROR_TERMINAL is not defined"
#endif

/* BEGINNING OF FUNCTION DECLARATIONS */

static void p_128(lex_state, act_state, code *, code *);
static void p_block(lex_state, act_state, code *);
static void p_frame(lex_state, act_state, code, code *);
static void p_assign_Hexpr_C_Cvalue(lex_state, act_state, code *);
static void p_153(lex_state, act_state, string *, code *);
extern void p_script(lex_state, act_state);
static void p_154(lex_state, act_state, code *, code *);
static void p_dup_Hexpr_C_Cdefault(lex_state, act_state, code *);
static void p_155(lex_state, act_state, code *);
static void p_156(lex_state, act_state, code *, opcode *);
static void p_157(lex_state, act_state, code *);
static void p_pipe_Hexpr(lex_state, act_state, code *);
static void p_and_Hexpr(lex_state, act_state, code *);
static void p_expr_Hlist(lex_state, act_state, code *);
static void p_pipe(lex_state, act_state, code, code, code *);
static void p_item(lex_state, act_state, code *);
static void p_dup_Hexpr(lex_state, act_state, code *);
static void p_list(lex_state, act_state, code *);
static void p_expr(lex_state, act_state, code *);
static void p_dup_Hexpr_C_Cclose(lex_state, act_state, code *);
static void p_sep(lex_state, act_state);
static void p_dup_Hexpr_C_Cpair_Hlist(lex_state, act_state, code *);
static void p_pipe_C_Cside(lex_state, act_state, opcode, code, code *);
static void p_or_Hexpr(lex_state, act_state, code *);
static void p_85(lex_state, act_state, code *);
static void p_86(lex_state, act_state, code *, code *);
static void p_88(lex_state, act_state, code *);
static void p_dup_Hexpr_C_Cpair_Hbox(lex_state, act_state, code *);
static void p_90(lex_state, act_state, code *);
static void p_command(lex_state, act_state, code *);
static void p_123(lex_state, act_state, code *, code *);
static void p_dup_Hexpr_C_Cfd(lex_state, act_state, code *);
static void p_concat(lex_state, act_state, code, code, code *);
static void p_125(lex_state, act_state, code *, code *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
p_128(lex_state lex_state, act_state act_state, code *ZIcx, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_bar):
		{
			code ZIrhs;
			code ZIlhs;

			ADVANCE_LEXER;
			p_pipe_Hexpr (lex_state, act_state, &ZIrhs);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			ZIlhs = *ZIcx;
			p_pipe (lex_state, act_state, ZIlhs, ZIrhs, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			ZIc = *ZIcx;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_block(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		type ZIt;
		mark ZIm;

		switch (CURRENT_TERMINAL) {
		case (tok_obrace):
			/* BEGINNING OF EXTRACT: obrace */
			{
#line 113 "src/parser.act"

		ZIm = lex_mark(lex_state->buf, act_state->t.pos);
		if (ZIm == NULL) {
			/* TODO: error out */
		}

		ZIt = act_state->t.type;
	
#line 177 "src/parser.c"
			}
			/* END OF EXTRACT: obrace */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 98 */
		{
			switch (CURRENT_TERMINAL) {
			case (tok_tick): case (tok_obrace): case (tok_word): case (tok_var):
				{
					p_expr_Hlist (lex_state, act_state, &ZIc);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-code */
					{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 209 "src/parser.c"
					}
					/* END OF ACTION: empty-code */
				}
				break;
			}
		}
		/* END OF INLINE: 98 */
		/* BEGINNING OF INLINE: 99 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case (tok_cbrace):
					break;
				default:
					goto ZL4;
				}
				ADVANCE_LEXER;
			}
			goto ZL3;
		ZL4:;
			{
				/* BEGINNING OF ACTION: err-unmatched */
				{
#line 261 "src/parser.act"

		assert((isprint)((ZIt)));
		assert((ZIm) != NULL);

		if (act_state->e == ERR_NONE) {
			err_printf("syntax", (ZIm)->buf, &(ZIm)->pos,
				"unmatched '%c'", (unsigned char) (ZIt));
			act_state->e = ERR_SYNTAX;
		}
	
#line 244 "src/parser.c"
				}
				/* END OF ACTION: err-unmatched */
			}
		ZL3:;
		}
		/* END OF INLINE: 99 */
		/* BEGINNING OF ACTION: free-mark */
		{
#line 283 "src/parser.act"

		free((ZIm));
	
#line 257 "src/parser.c"
		}
		/* END OF ACTION: free-mark */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_frame(lex_state lex_state, act_state act_state, code ZIci, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		opcode ZIo0;
		opcode ZIo1;

		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 291 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: op-pop */
		{
#line 172 "src/parser.act"
 (ZIo0) = OP_POP;  
#line 298 "src/parser.c"
		}
		/* END OF ACTION: op-pop */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 318 "src/parser.c"
		}
		/* END OF ACTION: code-push */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIci); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (ZIci);
	
#line 337 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
		/* BEGINNING OF ACTION: op-push */
		{
#line 171 "src/parser.act"
 (ZIo1) = OP_PUSH; 
#line 344 "src/parser.c"
		}
		/* END OF ACTION: op-push */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 364 "src/parser.c"
		}
		/* END OF ACTION: code-push */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_assign_Hexpr_C_Cvalue(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_oparen):
		{
			type ZIt;
			mark ZIm;

			/* BEGINNING OF EXTRACT: oparen */
			{
#line 122 "src/parser.act"

		ZIm = lex_mark(lex_state->buf, act_state->t.pos);
		if (ZIm == NULL) {
			/* TODO: error out */
		}

		ZIt = act_state->t.type;
	
#line 398 "src/parser.c"
			}
			/* END OF EXTRACT: oparen */
			ADVANCE_LEXER;
			p_list (lex_state, act_state, &ZIc);
			/* BEGINNING OF INLINE: 96 */
			{
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL1;
				}
				{
					switch (CURRENT_TERMINAL) {
					case (tok_cparen):
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: err-unmatched */
					{
#line 261 "src/parser.act"

		assert((isprint)((ZIt)));
		assert((ZIm) != NULL);

		if (act_state->e == ERR_NONE) {
			err_printf("syntax", (ZIm)->buf, &(ZIm)->pos,
				"unmatched '%c'", (unsigned char) (ZIt));
			act_state->e = ERR_SYNTAX;
		}
	
#line 434 "src/parser.c"
					}
					/* END OF ACTION: err-unmatched */
				}
			ZL2:;
			}
			/* END OF INLINE: 96 */
			/* BEGINNING OF ACTION: free-mark */
			{
#line 283 "src/parser.act"

		free((ZIm));
	
#line 447 "src/parser.c"
			}
			/* END OF ACTION: free-mark */
		}
		break;
	case (tok_obrace):
		{
			p_block (lex_state, act_state, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (tok_tick): case (tok_word): case (tok_var):
		{
			p_item (lex_state, act_state, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	{
		rule ZIr;

		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 490 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: expected-value */
		{
#line 249 "src/parser.act"
 (ZIr) = "$var | word | `word | `{ ... } | { ... } | ( ... )"; 
#line 497 "src/parser.c"
		}
		/* END OF ACTION: expected-value */
		/* BEGINNING OF ACTION: err-expected */
		{
#line 251 "src/parser.act"

		assert((ZIr) != NULL);

		if (act_state->e == ERR_NONE) {
			err_printf("syntax", lex_state->buf, &act_state->t.pos,
				"expected %s", (ZIr));
			act_state->e = ERR_SYNTAX;
		}
	
#line 512 "src/parser.c"
		}
		/* END OF ACTION: err-expected */
	}
ZL0:;
	*ZOc = ZIc;
}

static void
p_153(lex_state lex_state, act_state act_state, string *ZIs, code *ZOcx)
{
	code ZIcx;

	switch (CURRENT_TERMINAL) {
	case (tok_equ):
		{
			code ZIci;
			opcode ZIop;

			ADVANCE_LEXER;
			p_assign_Hexpr_C_Cvalue (lex_state, act_state, &ZIci);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZIcx) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 547 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: op-set */
			{
#line 182 "src/parser.act"
 (ZIop) = OP_SET;  
#line 554 "src/parser.c"
			}
			/* END OF ACTION: op-set */
			/* BEGINNING OF ACTION: code-anon */
			{
#line 184 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-anon>\n");
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		/* XXX: leak */
		if (!code_anon((&ZIcx), &m, (ZIop), (ZIci))) {
			goto ZL1;
		}
	
#line 575 "src/parser.c"
			}
			/* END OF ACTION: code-anon */
			/* BEGINNING OF ACTION: code-data */
			{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((*ZIs).s != NULL && (*ZIs).e != NULL);
		assert((*ZIs).e >= (*ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((*ZIs).e - (*ZIs).s), (*ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZIcx), &m, (*ZIs).e - (*ZIs).s, (*ZIs).s)) {
			goto ZL1;
		}
	
#line 598 "src/parser.c"
			}
			/* END OF ACTION: code-data */
		}
		break;
	default:
		{
			code ZI152;
			code ZI151;
			opcode ZIo0;
			opcode ZIo1;
			code ZI149;

			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZI152) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 621 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: code-data */
			{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((*ZIs).s != NULL && (*ZIs).e != NULL);
		assert((*ZIs).e >= (*ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((*ZIs).e - (*ZIs).s), (*ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZI152), &m, (*ZIs).e - (*ZIs).s, (*ZIs).s)) {
			goto ZL1;
		}
	
#line 644 "src/parser.c"
			}
			/* END OF ACTION: code-data */
			p_90 (lex_state, act_state, &ZI152);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZI151) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 662 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: op-run */
			{
#line 169 "src/parser.act"
 (ZIo0) = OP_RUN;  
#line 669 "src/parser.c"
			}
			/* END OF ACTION: op-run */
			/* BEGINNING OF ACTION: code-push */
			{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZI151), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 689 "src/parser.c"
			}
			/* END OF ACTION: code-push */
			/* BEGINNING OF ACTION: code-wind */
			{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZI152); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZI151);
		(ZI151) = (ZI152);
	
#line 708 "src/parser.c"
			}
			/* END OF ACTION: code-wind */
			/* BEGINNING OF ACTION: op-null */
			{
#line 168 "src/parser.act"
 (ZIo1) = OP_NULL; 
#line 715 "src/parser.c"
			}
			/* END OF ACTION: op-null */
			/* BEGINNING OF ACTION: code-push */
			{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZI151), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 735 "src/parser.c"
			}
			/* END OF ACTION: code-push */
			p_125 (lex_state, act_state, &ZI151, &ZI149);
			p_128 (lex_state, act_state, &ZI149, &ZIcx);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOcx = ZIcx;
}

void
p_script(lex_state lex_state, act_state act_state)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		/* BEGINNING OF INLINE: 148 */
		{
		ZL3_148:;
			switch (CURRENT_TERMINAL) {
			case (tok_nl): case (tok_semi): case (tok_tick): case (tok_obrace):
			case (tok_word): case (tok_var):
				{
					/* BEGINNING OF INLINE: script::global-expr-list */
					{
						{
							code ZIc;

							/* BEGINNING OF INLINE: 146 */
							{
								switch (CURRENT_TERMINAL) {
								case (tok_tick): case (tok_obrace): case (tok_word): case (tok_var):
									{
										p_expr (lex_state, act_state, &ZIc);
										if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
											RESTORE_LEXER;
											goto ZL1;
										}
									}
									break;
								default:
									{
										/* BEGINNING OF ACTION: empty-code */
										{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 800 "src/parser.c"
										}
										/* END OF ACTION: empty-code */
									}
									break;
								}
							}
							/* END OF INLINE: 146 */
							p_sep (lex_state, act_state);
							if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
								RESTORE_LEXER;
								goto ZL1;
							}
							/* BEGINNING OF ACTION: dispatch */
							{
#line 142 "src/parser.act"

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<dispatch>: ");
			code_dump(stderr, (ZIc));
		}

		if (-1 == act_state->dispatch((ZIc))) {
			goto ZL1;
		}
	
#line 826 "src/parser.c"
							}
							/* END OF ACTION: dispatch */
							/* BEGINNING OF INLINE: 148 */
							goto ZL3_148;
							/* END OF INLINE: 148 */
						}
						/* UNREACHED */
					}
					/* END OF INLINE: script::global-expr-list */
				}
				/* UNREACHED */
			default:
				break;
			}
		}
		/* END OF INLINE: 148 */
		switch (CURRENT_TERMINAL) {
		case (tok_eof):
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
p_154(lex_state lex_state, act_state act_state, code *ZIcx, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_tick): case (tok_obrace): case (tok_word): case (tok_var):
		{
			p_expr_Hlist (lex_state, act_state, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: code-wind */
			{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (ZIcx); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (*ZIcx);
	
#line 886 "src/parser.c"
			}
			/* END OF ACTION: code-wind */
		}
		break;
	default:
		{
			ZIc = *ZIcx;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_dup_Hexpr_C_Cdefault(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		string ZIs;

		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 928 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: stdin */
		{
#line 161 "src/parser.act"
 (ZIs).s = "0"; (ZIs).e = (ZIs).s + 1; 
#line 935 "src/parser.c"
		}
		/* END OF ACTION: stdin */
		/* BEGINNING OF ACTION: code-data */
		{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((ZIs).s != NULL && (ZIs).e != NULL);
		assert((ZIs).e >= (ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((ZIs).e - (ZIs).s), (ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZIc), &m, (ZIs).e - (ZIs).s, (ZIs).s)) {
			goto ZL1;
		}
	
#line 958 "src/parser.c"
		}
		/* END OF ACTION: code-data */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_155(lex_state lex_state, act_state act_state, code *ZOnew)
{
	code ZInew;

	switch (CURRENT_TERMINAL) {
	case (tok_equ):
		{
			ADVANCE_LEXER;
			p_157 (lex_state, act_state, &ZInew);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			p_dup_Hexpr_C_Cdefault (lex_state, act_state, &ZInew);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOnew = ZInew;
}

static void
p_156(lex_state lex_state, act_state act_state, code *ZOn, opcode *ZOo0)
{
	code ZIn;
	opcode ZIo0;

	switch (CURRENT_TERMINAL) {
	case (tok_bar):
		{
			ADVANCE_LEXER;
			p_dup_Hexpr_C_Cfd (lex_state, act_state, &ZIn);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-asc */
			{
#line 179 "src/parser.act"
 (ZIo0) = OP_ASC;  
#line 1025 "src/parser.c"
			}
			/* END OF ACTION: op-asc */
		}
		break;
	default:
		{
			p_155 (lex_state, act_state, &ZIn);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: op-dup */
			{
#line 178 "src/parser.act"
 (ZIo0) = OP_DUP;  
#line 1041 "src/parser.c"
			}
			/* END OF ACTION: op-dup */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOn = ZIn;
	*ZOo0 = ZIo0;
}

static void
p_157(lex_state lex_state, act_state act_state, code *ZOnew)
{
	code ZInew;

	switch (CURRENT_TERMINAL) {
	default:
		{
			p_dup_Hexpr_C_Cclose (lex_state, act_state, &ZInew);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (tok_word): case (tok_var):
		{
			p_dup_Hexpr_C_Cfd (lex_state, act_state, &ZInew);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOnew = ZInew;
}

static void
p_pipe_Hexpr(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		code ZIcx;

		p_dup_Hexpr (lex_state, act_state, &ZIcx);
		p_128 (lex_state, act_state, &ZIcx, &ZIc);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_and_Hexpr(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		code ZIcx;

		/* BEGINNING OF INLINE: 132 */
		{
			switch (CURRENT_TERMINAL) {
			case (tok_tick):
				{
					code ZIci;
					code ZIlhs;
					code ZIrhs;
					code ZI152;
					code ZI151;
					opcode ZIo0;
					opcode ZIo1;
					code ZI149;

					ADVANCE_LEXER;
					p_85 (lex_state, act_state, &ZIci);
					p_86 (lex_state, act_state, &ZIci, &ZIlhs);
					p_88 (lex_state, act_state, &ZIrhs);
					p_pipe (lex_state, act_state, ZIlhs, ZIrhs, &ZI152);
					p_90 (lex_state, act_state, &ZI152);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: empty-code */
					{
#line 153 "src/parser.act"

		(ZI151) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 1164 "src/parser.c"
					}
					/* END OF ACTION: empty-code */
					/* BEGINNING OF ACTION: op-run */
					{
#line 169 "src/parser.act"
 (ZIo0) = OP_RUN;  
#line 1171 "src/parser.c"
					}
					/* END OF ACTION: op-run */
					/* BEGINNING OF ACTION: code-push */
					{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZI151), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 1191 "src/parser.c"
					}
					/* END OF ACTION: code-push */
					/* BEGINNING OF ACTION: code-wind */
					{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZI152); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZI151);
		(ZI151) = (ZI152);
	
#line 1210 "src/parser.c"
					}
					/* END OF ACTION: code-wind */
					/* BEGINNING OF ACTION: op-null */
					{
#line 168 "src/parser.act"
 (ZIo1) = OP_NULL; 
#line 1217 "src/parser.c"
					}
					/* END OF ACTION: op-null */
					/* BEGINNING OF ACTION: code-push */
					{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZI151), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 1237 "src/parser.c"
					}
					/* END OF ACTION: code-push */
					p_125 (lex_state, act_state, &ZI151, &ZI149);
					p_128 (lex_state, act_state, &ZI149, &ZIcx);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case (tok_var):
				{
					string ZIs;
					code ZI152;
					opcode ZIop;
					code ZI151;
					opcode ZIo0;
					opcode ZIo1;
					code ZI149;

					/* BEGINNING OF EXTRACT: var */
					{
#line 101 "src/parser.act"

		assert(act_state->t.s != NULL);
		assert(act_state->t.e >= act_state->t.s);

		ZIs.s = act_state->t.s;
		ZIs.e = act_state->t.e;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "var: \"%.*s\"\n", (int) (ZIs.e - ZIs.s), ZIs.s);
		}
	
#line 1272 "src/parser.c"
					}
					/* END OF EXTRACT: var */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: empty-code */
					{
#line 153 "src/parser.act"

		(ZI152) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 1286 "src/parser.c"
					}
					/* END OF ACTION: empty-code */
					/* BEGINNING OF ACTION: op-call */
					{
#line 165 "src/parser.act"
 (ZIop) = OP_CALL; 
#line 1293 "src/parser.c"
					}
					/* END OF ACTION: op-call */
					/* BEGINNING OF ACTION: code-push */
					{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIop)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZI152), &m, (ZIop))) {
			goto ZL1;
		}
	
#line 1313 "src/parser.c"
					}
					/* END OF ACTION: code-push */
					/* BEGINNING OF ACTION: code-data */
					{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((ZIs).s != NULL && (ZIs).e != NULL);
		assert((ZIs).e >= (ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((ZIs).e - (ZIs).s), (ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZI152), &m, (ZIs).e - (ZIs).s, (ZIs).s)) {
			goto ZL1;
		}
	
#line 1336 "src/parser.c"
					}
					/* END OF ACTION: code-data */
					p_90 (lex_state, act_state, &ZI152);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: empty-code */
					{
#line 153 "src/parser.act"

		(ZI151) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 1354 "src/parser.c"
					}
					/* END OF ACTION: empty-code */
					/* BEGINNING OF ACTION: op-run */
					{
#line 169 "src/parser.act"
 (ZIo0) = OP_RUN;  
#line 1361 "src/parser.c"
					}
					/* END OF ACTION: op-run */
					/* BEGINNING OF ACTION: code-push */
					{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZI151), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 1381 "src/parser.c"
					}
					/* END OF ACTION: code-push */
					/* BEGINNING OF ACTION: code-wind */
					{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZI152); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZI151);
		(ZI151) = (ZI152);
	
#line 1400 "src/parser.c"
					}
					/* END OF ACTION: code-wind */
					/* BEGINNING OF ACTION: op-null */
					{
#line 168 "src/parser.act"
 (ZIo1) = OP_NULL; 
#line 1407 "src/parser.c"
					}
					/* END OF ACTION: op-null */
					/* BEGINNING OF ACTION: code-push */
					{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZI151), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 1427 "src/parser.c"
					}
					/* END OF ACTION: code-push */
					p_125 (lex_state, act_state, &ZI151, &ZI149);
					p_128 (lex_state, act_state, &ZI149, &ZIcx);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case (tok_word):
				{
					string ZIs;

					/* BEGINNING OF EXTRACT: word */
					{
#line 89 "src/parser.act"

		assert(act_state->t.s != NULL);
		assert(act_state->t.e >= act_state->t.s);

		ZIs.s = act_state->t.s;
		ZIs.e = act_state->t.e;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "str: \"%.*s\"\n", (int) (ZIs.e - ZIs.s), ZIs.s);
		}
	
#line 1456 "src/parser.c"
					}
					/* END OF EXTRACT: word */
					ADVANCE_LEXER;
					p_153 (lex_state, act_state, &ZIs, &ZIcx);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			case (tok_obrace):
				{
					code ZI150;
					code ZI149;

					p_block (lex_state, act_state, &ZI150);
					p_123 (lex_state, act_state, &ZI150, &ZI149);
					p_128 (lex_state, act_state, &ZI149, &ZIcx);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 132 */
		/* BEGINNING OF INLINE: 133 */
		{
			switch (CURRENT_TERMINAL) {
			case (tok_and):
				{
					code ZIci;
					opcode ZIo2;

					ADVANCE_LEXER;
					p_and_Hexpr (lex_state, act_state, &ZIci);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: empty-code */
					{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 1510 "src/parser.c"
					}
					/* END OF ACTION: empty-code */
					/* BEGINNING OF ACTION: op-if */
					{
#line 180 "src/parser.act"
 (ZIo2) = OP_IF;   
#line 1517 "src/parser.c"
					}
					/* END OF ACTION: op-if */
					/* BEGINNING OF ACTION: code-anon */
					{
#line 184 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-anon>\n");
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		/* XXX: leak */
		if (!code_anon((&ZIc), &m, (ZIo2), (ZIci))) {
			goto ZL1;
		}
	
#line 1538 "src/parser.c"
					}
					/* END OF ACTION: code-anon */
					/* BEGINNING OF ACTION: code-wind */
					{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIcx); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (ZIcx);
	
#line 1557 "src/parser.c"
					}
					/* END OF ACTION: code-wind */
				}
				break;
			default:
				{
					ZIc = ZIcx;
				}
				break;
			}
		}
		/* END OF INLINE: 133 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_expr_Hlist(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		code ZIcx;

		p_expr (lex_state, act_state, &ZIcx);
		/* BEGINNING OF INLINE: 140 */
		{
			switch (CURRENT_TERMINAL) {
			case (tok_nl): case (tok_semi):
				{
					p_sep (lex_state, act_state);
					p_154 (lex_state, act_state, &ZIcx, &ZIc);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					ZIc = ZIcx;
				}
				break;
			case (ERROR_TERMINAL):
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 140 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_pipe(lex_state lex_state, act_state act_state, code ZIlhs, code ZIrhs, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		opcode ZIo1;
		opcode ZIo2;
		code ZIl;
		opcode ZIo0;

		/* BEGINNING OF ACTION: op-clhs */
		{
#line 173 "src/parser.act"
 (ZIo1) = OP_CLHS; 
#line 1642 "src/parser.c"
		}
		/* END OF ACTION: op-clhs */
		/* BEGINNING OF ACTION: op-crhs */
		{
#line 174 "src/parser.act"
 (ZIo2) = OP_CRHS; 
#line 1649 "src/parser.c"
		}
		/* END OF ACTION: op-crhs */
		p_pipe_C_Cside (lex_state, act_state, ZIo1, ZIlhs, &ZIl);
		p_pipe_C_Cside (lex_state, act_state, ZIo2, ZIrhs, &ZIc);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: op-pipe */
		{
#line 181 "src/parser.act"
 (ZIo0) = OP_PIPE; 
#line 1662 "src/parser.c"
		}
		/* END OF ACTION: op-pipe */
		/* BEGINNING OF ACTION: code-anon */
		{
#line 184 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-anon>\n");
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		/* XXX: leak */
		if (!code_anon((&ZIc), &m, (ZIo0), (ZIl))) {
			goto ZL1;
		}
	
#line 1683 "src/parser.c"
		}
		/* END OF ACTION: code-anon */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_item(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_tick):
		{
			code ZIci;
			code ZIlhs;
			code ZIrhs;

			ADVANCE_LEXER;
			p_85 (lex_state, act_state, &ZIci);
			p_86 (lex_state, act_state, &ZIci, &ZIlhs);
			p_88 (lex_state, act_state, &ZIrhs);
			p_pipe (lex_state, act_state, ZIlhs, ZIrhs, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (tok_var):
		{
			string ZIs;
			opcode ZIop;

			/* BEGINNING OF EXTRACT: var */
			{
#line 101 "src/parser.act"

		assert(act_state->t.s != NULL);
		assert(act_state->t.e >= act_state->t.s);

		ZIs.s = act_state->t.s;
		ZIs.e = act_state->t.e;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "var: \"%.*s\"\n", (int) (ZIs.e - ZIs.s), ZIs.s);
		}
	
#line 1737 "src/parser.c"
			}
			/* END OF EXTRACT: var */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 1751 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: op-call */
			{
#line 165 "src/parser.act"
 (ZIop) = OP_CALL; 
#line 1758 "src/parser.c"
			}
			/* END OF ACTION: op-call */
			/* BEGINNING OF ACTION: code-push */
			{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIop)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIop))) {
			goto ZL1;
		}
	
#line 1778 "src/parser.c"
			}
			/* END OF ACTION: code-push */
			/* BEGINNING OF ACTION: code-data */
			{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((ZIs).s != NULL && (ZIs).e != NULL);
		assert((ZIs).e >= (ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((ZIs).e - (ZIs).s), (ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZIc), &m, (ZIs).e - (ZIs).s, (ZIs).s)) {
			goto ZL1;
		}
	
#line 1801 "src/parser.c"
			}
			/* END OF ACTION: code-data */
		}
		break;
	case (tok_word):
		{
			string ZIs;

			/* BEGINNING OF EXTRACT: word */
			{
#line 89 "src/parser.act"

		assert(act_state->t.s != NULL);
		assert(act_state->t.e >= act_state->t.s);

		ZIs.s = act_state->t.s;
		ZIs.e = act_state->t.e;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "str: \"%.*s\"\n", (int) (ZIs.e - ZIs.s), ZIs.s);
		}
	
#line 1824 "src/parser.c"
			}
			/* END OF EXTRACT: word */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 1838 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: code-data */
			{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((ZIs).s != NULL && (ZIs).e != NULL);
		assert((ZIs).e >= (ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((ZIs).e - (ZIs).s), (ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZIc), &m, (ZIs).e - (ZIs).s, (ZIs).s)) {
			goto ZL1;
		}
	
#line 1861 "src/parser.c"
			}
			/* END OF ACTION: code-data */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_dup_Hexpr(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_obrace):
		{
			code ZIcx;

			p_block (lex_state, act_state, &ZIcx);
			p_123 (lex_state, act_state, &ZIcx, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (tok_tick): case (tok_word): case (tok_var):
		{
			code ZIcx;

			p_command (lex_state, act_state, &ZIcx);
			p_125 (lex_state, act_state, &ZIcx, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_list(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		p_item (lex_state, act_state, &ZIc);
		p_90 (lex_state, act_state, &ZIc);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_expr(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		p_or_Hexpr (lex_state, act_state, &ZIc);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 1974 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: err-syntax */
		{
#line 272 "src/parser.act"

		if (act_state->e == ERR_NONE) {
			err_printf("syntax", lex_state->buf, &act_state->t.pos, NULL);
			act_state->e = ERR_SYNTAX;
		}

		if (act_state->e == ERR_ERRNO) {
			goto ZL2;
		}
	
#line 1990 "src/parser.c"
		}
		/* END OF ACTION: err-syntax */
	}
	goto ZL0;
ZL2:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_dup_Hexpr_C_Cclose(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		opcode ZIop;

		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2023 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: op-null */
		{
#line 168 "src/parser.act"
 (ZIop) = OP_NULL; 
#line 2030 "src/parser.c"
		}
		/* END OF ACTION: op-null */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIop)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIop))) {
			goto ZL1;
		}
	
#line 2050 "src/parser.c"
		}
		/* END OF ACTION: code-push */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_sep(lex_state lex_state, act_state act_state)
{
	switch (CURRENT_TERMINAL) {
	case (tok_nl):
		{
			ADVANCE_LEXER;
		}
		break;
	case (tok_semi):
		{
			ADVANCE_LEXER;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		rule ZIr;

		/* BEGINNING OF ACTION: expected-sep */
		{
#line 247 "src/parser.act"
 (ZIr) = "'\\n' | ';' | '&'"; 
#line 2090 "src/parser.c"
		}
		/* END OF ACTION: expected-sep */
		/* BEGINNING OF ACTION: err-expected */
		{
#line 251 "src/parser.act"

		assert((ZIr) != NULL);

		if (act_state->e == ERR_NONE) {
			err_printf("syntax", lex_state->buf, &act_state->t.pos,
				"expected %s", (ZIr));
			act_state->e = ERR_SYNTAX;
		}
	
#line 2105 "src/parser.c"
		}
		/* END OF ACTION: err-expected */
	}
}

static void
p_dup_Hexpr_C_Cpair_Hlist(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		code ZIm;
		code ZIn;
		opcode ZIo0;
		opcode ZIo1;

		/* BEGINNING OF INLINE: 116 */
		{
			{
				p_dup_Hexpr_C_Cfd (lex_state, act_state, &ZIm);
				p_156 (lex_state, act_state, &ZIn, &ZIo0);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL1;
				}
			}
		}
		/* END OF INLINE: 116 */
		/* BEGINNING OF INLINE: 118 */
		{
			switch (CURRENT_TERMINAL) {
			case (tok_comma):
				{
					ADVANCE_LEXER;
					p_dup_Hexpr_C_Cpair_Hlist (lex_state, act_state, &ZIc);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty-code */
					{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2162 "src/parser.c"
					}
					/* END OF ACTION: empty-code */
				}
				break;
			}
		}
		/* END OF INLINE: 118 */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 2187 "src/parser.c"
		}
		/* END OF ACTION: code-push */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIm); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (ZIm);
	
#line 2206 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIn); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (ZIn);
	
#line 2225 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
		/* BEGINNING OF ACTION: op-null */
		{
#line 168 "src/parser.act"
 (ZIo1) = OP_NULL; 
#line 2232 "src/parser.c"
		}
		/* END OF ACTION: op-null */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 2252 "src/parser.c"
		}
		/* END OF ACTION: code-push */
	}
	goto ZL0;
ZL1:;
	{
		rule ZIr;

		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2271 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: expected-pair */
		{
#line 248 "src/parser.act"
 (ZIr) = "m '=' n | m '=' | m | x '|' y"; 
#line 2278 "src/parser.c"
		}
		/* END OF ACTION: expected-pair */
		/* BEGINNING OF ACTION: err-expected */
		{
#line 251 "src/parser.act"

		assert((ZIr) != NULL);

		if (act_state->e == ERR_NONE) {
			err_printf("syntax", lex_state->buf, &act_state->t.pos,
				"expected %s", (ZIr));
			act_state->e = ERR_SYNTAX;
		}
	
#line 2293 "src/parser.c"
		}
		/* END OF ACTION: err-expected */
	}
ZL0:;
	*ZOc = ZIc;
}

static void
p_pipe_C_Cside(lex_state lex_state, act_state act_state, opcode ZIop, code ZIci, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		opcode ZIo0;
		code ZIcx;

		/* BEGINNING OF ACTION: op-dup */
		{
#line 178 "src/parser.act"
 (ZIo0) = OP_DUP;  
#line 2317 "src/parser.c"
		}
		/* END OF ACTION: op-dup */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIci), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 2337 "src/parser.c"
		}
		/* END OF ACTION: code-push */
		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIcx) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2350 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIop)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIcx), &m, (ZIop))) {
			goto ZL1;
		}
	
#line 2370 "src/parser.c"
		}
		/* END OF ACTION: code-push */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIci); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIcx);
		(ZIcx) = (ZIci);
	
#line 2389 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
		p_frame (lex_state, act_state, ZIcx, &ZIc);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_or_Hexpr(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		code ZIcx;

		p_and_Hexpr (lex_state, act_state, &ZIcx);
		/* BEGINNING OF INLINE: 136 */
		{
			switch (CURRENT_TERMINAL) {
			case (tok_or):
				{
					code ZIci;
					opcode ZIo2;
					opcode ZIo1;

					ADVANCE_LEXER;
					p_or_Hexpr (lex_state, act_state, &ZIci);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: empty-code */
					{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2443 "src/parser.c"
					}
					/* END OF ACTION: empty-code */
					/* BEGINNING OF ACTION: op-if */
					{
#line 180 "src/parser.act"
 (ZIo2) = OP_IF;   
#line 2450 "src/parser.c"
					}
					/* END OF ACTION: op-if */
					/* BEGINNING OF ACTION: code-anon */
					{
#line 184 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-anon>\n");
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		/* XXX: leak */
		if (!code_anon((&ZIc), &m, (ZIo2), (ZIci))) {
			goto ZL1;
		}
	
#line 2471 "src/parser.c"
					}
					/* END OF ACTION: code-anon */
					/* BEGINNING OF ACTION: op-not */
					{
#line 167 "src/parser.act"
 (ZIo1) = OP_NOT;  
#line 2478 "src/parser.c"
					}
					/* END OF ACTION: op-not */
					/* BEGINNING OF ACTION: code-push */
					{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 2498 "src/parser.c"
					}
					/* END OF ACTION: code-push */
					/* BEGINNING OF ACTION: code-wind */
					{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIcx); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (ZIcx);
	
#line 2517 "src/parser.c"
					}
					/* END OF ACTION: code-wind */
				}
				break;
			default:
				{
					ZIc = ZIcx;
				}
				break;
			case (ERROR_TERMINAL):
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 136 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_85(lex_state lex_state, act_state act_state, code *ZOci)
{
	code ZIci;

	switch (CURRENT_TERMINAL) {
	case (tok_obrace):
		{
			p_block (lex_state, act_state, &ZIci);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (tok_tick): case (tok_word): case (tok_var):
		{
			code ZIcx;
			opcode ZIo1;
			opcode ZIo0;

			p_item (lex_state, act_state, &ZIcx);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZIci) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2578 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: op-run */
			{
#line 169 "src/parser.act"
 (ZIo1) = OP_RUN;  
#line 2585 "src/parser.c"
			}
			/* END OF ACTION: op-run */
			/* BEGINNING OF ACTION: code-push */
			{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIci), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 2605 "src/parser.c"
			}
			/* END OF ACTION: code-push */
			/* BEGINNING OF ACTION: code-wind */
			{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIcx); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIci);
		(ZIci) = (ZIcx);
	
#line 2624 "src/parser.c"
			}
			/* END OF ACTION: code-wind */
			/* BEGINNING OF ACTION: op-null */
			{
#line 168 "src/parser.act"
 (ZIo0) = OP_NULL; 
#line 2631 "src/parser.c"
			}
			/* END OF ACTION: op-null */
			/* BEGINNING OF ACTION: code-push */
			{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIci), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 2651 "src/parser.c"
			}
			/* END OF ACTION: code-push */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOci = ZIci;
}

static void
p_86(lex_state lex_state, act_state act_state, code *ZIci, code *ZOlhs)
{
	code ZIlhs;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		opcode ZIo4;

		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIlhs) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2690 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: op-ctck */
		{
#line 175 "src/parser.act"
 (ZIo4) = OP_CTCK; 
#line 2697 "src/parser.c"
		}
		/* END OF ACTION: op-ctck */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo4)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIlhs), &m, (ZIo4))) {
			goto ZL1;
		}
	
#line 2717 "src/parser.c"
		}
		/* END OF ACTION: code-push */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (ZIci); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIlhs);
		(ZIlhs) = (*ZIci);
	
#line 2736 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOlhs = ZIlhs;
}

static void
p_88(lex_state lex_state, act_state act_state, code *ZOrhs)
{
	code ZIrhs;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		opcode ZIo3;

		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIrhs) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2769 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: op-tick */
		{
#line 170 "src/parser.act"
 (ZIo3) = OP_TICK; 
#line 2776 "src/parser.c"
		}
		/* END OF ACTION: op-tick */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo3)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIrhs), &m, (ZIo3))) {
			goto ZL1;
		}
	
#line 2796 "src/parser.c"
		}
		/* END OF ACTION: code-push */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOrhs = ZIrhs;
}

static void
p_dup_Hexpr_C_Cpair_Hbox(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		type ZIt;
		mark ZIm;
		code ZIdx;

		switch (CURRENT_TERMINAL) {
		case (tok_osquare):
			/* BEGINNING OF EXTRACT: osquare */
			{
#line 131 "src/parser.act"

		ZIm = lex_mark(lex_state->buf, act_state->t.pos);
		if (ZIm == NULL) {
			/* TODO: error out */
		}

		ZIt = act_state->t.type;
	
#line 2834 "src/parser.c"
			}
			/* END OF EXTRACT: osquare */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		p_dup_Hexpr_C_Cpair_Hlist (lex_state, act_state, &ZIdx);
		/* BEGINNING OF INLINE: 122 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case (tok_csquare):
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: err-unmatched */
				{
#line 261 "src/parser.act"

		assert((isprint)((ZIt)));
		assert((ZIm) != NULL);

		if (act_state->e == ERR_NONE) {
			err_printf("syntax", (ZIm)->buf, &(ZIm)->pos,
				"unmatched '%c'", (unsigned char) (ZIt));
			act_state->e = ERR_SYNTAX;
		}
	
#line 2874 "src/parser.c"
				}
				/* END OF ACTION: err-unmatched */
			}
		ZL2:;
		}
		/* END OF INLINE: 122 */
		/* BEGINNING OF ACTION: free-mark */
		{
#line 283 "src/parser.act"

		free((ZIm));
	
#line 2887 "src/parser.c"
		}
		/* END OF ACTION: free-mark */
		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 2900 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIdx); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (ZIdx);
	
#line 2919 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_90(lex_state lex_state, act_state act_state, code *ZIc)
{
	switch (CURRENT_TERMINAL) {
	case (tok_tick): case (tok_word): case (tok_var):
		{
			code ZIci;

			p_list (lex_state, act_state, &ZIci);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: code-wind */
			{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIci); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (*ZIc);
		(*ZIc) = (ZIci);
	
#line 2960 "src/parser.c"
			}
			/* END OF ACTION: code-wind */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
p_command(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		code ZIcx;
		opcode ZIo0;
		opcode ZIo1;

		p_list (lex_state, act_state, &ZIcx);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 3004 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: op-run */
		{
#line 169 "src/parser.act"
 (ZIo0) = OP_RUN;  
#line 3011 "src/parser.c"
		}
		/* END OF ACTION: op-run */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo0)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIo0))) {
			goto ZL1;
		}
	
#line 3031 "src/parser.c"
		}
		/* END OF ACTION: code-push */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIcx); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIc);
		(ZIc) = (ZIcx);
	
#line 3050 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
		/* BEGINNING OF ACTION: op-null */
		{
#line 168 "src/parser.act"
 (ZIo1) = OP_NULL; 
#line 3057 "src/parser.c"
		}
		/* END OF ACTION: op-null */
		/* BEGINNING OF ACTION: code-push */
		{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIo1)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIo1))) {
			goto ZL1;
		}
	
#line 3077 "src/parser.c"
		}
		/* END OF ACTION: code-push */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_123(lex_state lex_state, act_state act_state, code *ZIcx, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_osquare):
		{
			code ZId;
			code ZIq;

			p_dup_Hexpr_C_Cpair_Hbox (lex_state, act_state, &ZId);
			p_concat (lex_state, act_state, ZId, *ZIcx, &ZIq);
			p_frame (lex_state, act_state, ZIq, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			code ZId;
			code ZIq;

			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZId) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 3124 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			p_concat (lex_state, act_state, ZId, *ZIcx, &ZIq);
			p_frame (lex_state, act_state, ZIq, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_dup_Hexpr_C_Cfd(lex_state lex_state, act_state act_state, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_var):
		{
			string ZIs;
			opcode ZIop;

			/* BEGINNING OF EXTRACT: var */
			{
#line 101 "src/parser.act"

		assert(act_state->t.s != NULL);
		assert(act_state->t.e >= act_state->t.s);

		ZIs.s = act_state->t.s;
		ZIs.e = act_state->t.e;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "var: \"%.*s\"\n", (int) (ZIs.e - ZIs.s), ZIs.s);
		}
	
#line 3171 "src/parser.c"
			}
			/* END OF EXTRACT: var */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 3185 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: op-call */
			{
#line 165 "src/parser.act"
 (ZIop) = OP_CALL; 
#line 3192 "src/parser.c"
			}
			/* END OF ACTION: op-call */
			/* BEGINNING OF ACTION: code-push */
			{
#line 218 "src/parser.act"

		struct lex_mark m;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-push>: %s\n", op_name((ZIop)));
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_push((&ZIc), &m, (ZIop))) {
			goto ZL1;
		}
	
#line 3212 "src/parser.c"
			}
			/* END OF ACTION: code-push */
			/* BEGINNING OF ACTION: code-data */
			{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((ZIs).s != NULL && (ZIs).e != NULL);
		assert((ZIs).e >= (ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((ZIs).e - (ZIs).s), (ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZIc), &m, (ZIs).e - (ZIs).s, (ZIs).s)) {
			goto ZL1;
		}
	
#line 3235 "src/parser.c"
			}
			/* END OF ACTION: code-data */
		}
		break;
	case (tok_word):
		{
			string ZIs;

			/* BEGINNING OF EXTRACT: word */
			{
#line 89 "src/parser.act"

		assert(act_state->t.s != NULL);
		assert(act_state->t.e >= act_state->t.s);

		ZIs.s = act_state->t.s;
		ZIs.e = act_state->t.e;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "str: \"%.*s\"\n", (int) (ZIs.e - ZIs.s), ZIs.s);
		}
	
#line 3258 "src/parser.c"
			}
			/* END OF EXTRACT: word */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: empty-code */
			{
#line 153 "src/parser.act"

		(ZIc) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 3272 "src/parser.c"
			}
			/* END OF ACTION: empty-code */
			/* BEGINNING OF ACTION: code-data */
			{
#line 200 "src/parser.act"

		struct lex_mark m;

		assert((ZIs).s != NULL && (ZIs).e != NULL);
		assert((ZIs).e >= (ZIs).s);

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-data>: \"%.*s\"\n", (int) ((ZIs).e - (ZIs).s), (ZIs).s);
		}

		m.buf = lex_state->buf;
		m.pos = lex_state->pos;

		if (!code_data((&ZIc), &m, (ZIs).e - (ZIs).s, (ZIs).s)) {
			goto ZL1;
		}
	
#line 3295 "src/parser.c"
			}
			/* END OF ACTION: code-data */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

static void
p_concat(lex_state lex_state, act_state act_state, code ZIa, code ZIb, code *ZOq)
{
	code ZIq;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		/* BEGINNING OF ACTION: empty-code */
		{
#line 153 "src/parser.act"

		(ZIq) = NULL;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<empty-code>\n");
		}
	
#line 3332 "src/parser.c"
		}
		/* END OF ACTION: empty-code */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIb); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIq);
		(ZIq) = (ZIb);
	
#line 3351 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
		/* BEGINNING OF ACTION: code-wind */
		{
#line 233 "src/parser.act"

		struct code **tail;

		if (debug & DEBUG_ACT) {
			fprintf(stderr, "<code-wind>\n");
		}

		for (tail = (&ZIa); *tail != NULL; tail = &(*tail)->next)
			;

		*tail = (ZIq);
		(ZIq) = (ZIa);
	
#line 3370 "src/parser.c"
		}
		/* END OF ACTION: code-wind */
	}
	*ZOq = ZIq;
}

static void
p_125(lex_state lex_state, act_state act_state, code *ZIcx, code *ZOc)
{
	code ZIc;

	switch (CURRENT_TERMINAL) {
	case (tok_osquare):
		{
			code ZId;
			code ZIq;

			p_dup_Hexpr_C_Cpair_Hbox (lex_state, act_state, &ZId);
			p_concat (lex_state, act_state, ZId, *ZIcx, &ZIq);
			p_frame (lex_state, act_state, ZIq, &ZIc);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			ZIc = *ZIcx;
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZOc = ZIc;
}

/* BEGINNING OF TRAILER */

#line 287 "src/parser.act"


	int
	parse(struct lex_state *lex_state,
		int (*dispatch)(struct code *))
	{
		struct act_state a, *act_state = &a;

		assert(lex_state != NULL);
		assert(dispatch != NULL);

		act_state->dispatch = dispatch;
		lex_state->p = lex_state->buf;

		do {
			act_state->e = ERR_NONE;

			ADVANCE_LEXER;

			p_script(lex_state, act_state);
			if (CURRENT_TERMINAL == (tok_error)) {
				/* lexer error (e.g. fgets failing) */
				return -1;
			}

			if (act_state->e == ERR_ERRNO) {
				/* dispatch error */
				return -1;
			}

			if (act_state->e == ERR_SYNTAX) {
				if (debug & DEBUG_ACT) {
					fprintf(stderr, "<panic mode> ...\n");
				}

				/* panic mode */
				while (CURRENT_TERMINAL != (tok_semi) && CURRENT_TERMINAL != (tok_nl)) {
					ADVANCE_LEXER;
					if (CURRENT_TERMINAL == (tok_error)) {
						return -1;
					}
				}

				if (debug & DEBUG_ACT) {
					fprintf(stderr, "... <end panic>\n");
				}
			}
		} while (act_state->e == ERR_SYNTAX);

		return 0;
	}

#line 3468 "src/parser.c"

/* END OF FILE */
