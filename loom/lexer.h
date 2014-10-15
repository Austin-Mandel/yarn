#ifndef __SHED_LEXER_H
#define __SHED_LEXER_H

typedef enum {
	ASSIGN, APPEND, REMOVE, SLICE, MULTIPLY, VOID
} AssignmentOperator;

typedef enum {
	EQUALITY, INEQUALITY, AND, OR, XOR, NOT,
	BITAND, BITOR, BITXOR, BITNOT, BITLSH, BITRSH,
	ADD, SUB, MUL, DIV, MOD, EXP, INCREMENT, DECREMENT,
	NONE, LBRACKET, RBRACKET
} Operator;

typedef struct {
	char* lhs_label;
	Operator op; 
	Evaluator rhs;
} Evaluator;

typedef struct {
	char* lhs_label;
	AssignmentOperator op;
	Evaluator rhs;
} Statement;

#endif
