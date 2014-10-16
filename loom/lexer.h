#ifndef __SHED_LEXER_H
#define __SHED_LEXER_H

typedef enum {
	ASSIGN, APPEND, REMOVE, SLICE, MULTIPLY, VOID
} AssignmentOperator;

typedef enum {
	EQUALITY, INEQUALITY, AND, OR, XOR, NOT,
	BITAND, BITOR, BITXOR, BITNOT, BITLSH, BITRSH,
	ADD, SUB, MUL, DIV, MOD, EXP, INCREMENT, DECREMENT,
	NOOP, LBRACKET, RBRACKET
} Operator;

typedef enum {
	NOPRE, CALL, THREAD_CALL, VALUE
} PrefixOperator;

typedef enum {
	NOPOST, ARRAY, HASH, ELEMENT
} PostfixOperator;

typedef struct EvaluatorT {
	PrefixOperator 	   preOp;
	char*		   lhs_label;
	PostfixOperator    postOp;
	Operator 	   op;
	struct EvaluatorT* rhs;
} Evaluator;
const Evaluator EVALUATOR_INIT = {NOPRE, NULL, NOPOST, NOOP, NULL};

typedef struct {
	PrefixOperator     preOp;
	char* 	           lhs_label;
	PostfixOperator    postOp;
	AssignmentOperator op;
	Evaluator*         rhs;
} Statement;
const Statement STATEMENT_INIT = {NOPRE, NULL, NOPOST, VOID, NULL};

// These structures are for storing the lexed statement list
// This is essentially a doubly linked list
typedef struct NodeT {
	Statement* 	statement;
	struct NodeT*	next;
	struct NodeT* 	prev;
} Node;

#endif
