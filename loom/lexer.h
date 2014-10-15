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

typedef enum {
	NONE, CALL, THREAD_CALL, VALUE
} PrefixOperator;

typedef enum {
	NONE, ARRAY, HASH, ELEMENT
} PostfixOperator;

typedef struct {
	PrefixOperator 	preOp  =	NONE;
	char*		lhs_label;
	PostfixOperator postOp = 	NONE;
	Operator 	op     =	NONE;
	Evaluator* 	rhs;
} Evaluator;

typedef struct {
	PrefixOperator     preOp  = 	NONE;
	char* 	           lhs_label;
	PostfixOperator    postOp =	NONE;
	AssignmentOperator op     = 	VOID;
	Evaluator*         rhs;
} Statement;

// These structures are for storing the lexed statement list
typedef struct {
	Statement* 	statement;
	Node*		next;
	Node* 		prev;
} Node;

typedef struct {
	Node* first;
	Node* last;
} CodeBlock;

#endif
