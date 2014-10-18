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

typedef enum {
	INT_T, LONG_T, DOUBLE_T, STRING_T, ARRAY_T, HASH_T, CALL_T, CODE_T, 
	THREAD_T, GENERIC_T
} LabelType;

/* Labels can hold any kind of value - because they all overlap!
 * FIELDS:
 *		  Note, any Ignored fields are NULL pointers.
 *
 * name		- The label's textual name
 *
 * As a generic label:
 * type		- Always GENERIC.
 *		- This can point to anything, like C's void*.
 * scalar	- Ignored.
 * data		- Ignored.
 *
 * As a SCALAR:
 * type   	- The type of the scalar, int, long, double or string
 * scalar	- The value of the scalar:
 *		  As an INT:
 *			- holds a signed 32 bit integer
 *		  As a LONG:
 *			- holds an unsigned 64 bit integer
 *		  As a DOUBLE:
 *			- holds a double precision floating point value
 *		  As a STRING:
 *			- holds a pointer to a C string
 * data		- Ignored.
 *			
 * As an ARRAY:
 * type		- Always ARRAY.
 * scalar	- Always an unsigned integer, representing they array's size.
 *		  You cannot have arrays with sizes larger than 2^32-1.
 * data		- An array of labels, possibly with some NULL entries.
 *
 * As a HASH:
 *		  All hashes uses jenkin's one-at-a-time hash to generate the
 *		  value's index. Also, hashes are necessarily even valued in
 *		  size, as the pairs are stored key,value,key,value, etc.
 *		  The code is then jenkins(key) % (length/2) + 1.
 *		  (perl5 hashes anyone?)
 *
 * type		- Always HASH.
 * scalar	- Always an unsigned integer, representing the number of entries
 *		  in the hash map. You can not have more than 2^32-1 key,value
 *		  pairs.
 * data		- An array, where every even index is a key, and ever odd it's
 *		  value. Every value is, of course, a Label struct.
 *
 * As a CODE BLOCK:
 * type		- Always CODE.
 * scalar	- A string, the name of the code block.
 *		  NOTE: Could be anonymous, in which case this will be NULL.
 * data		- Array of Statement structs, and hashmap of params.
 *		  NOTE ON ARRAY ORGANIZATION:
 *			Index - Description
 *			    0 - The size of the parameters hash. An unsigned int.
 *				If 0, no parameters.
 *		      data[0] - The hash, in the format described earlier.
 *				NOTE: If the hash size is 0, this is the start
 *			        of the code array!
 *		    data[1] + - The code array. size is (scalar - data[0] - 1).
 *
 * As a CALL:
 * type		- Always CALL.
 * scalar	- If the call is threaded, a pointer to that thread's label.
 *		  Otherwise, it will be NULL.
 * data		- An array. It will always be at least length 2.
 * 		  NOTE ON ARRAY ORGANIZATION:
 *			Index - Description
 *			    0 - Always the size of the parameter list that follows,
 *			        or 0 if no list.
 *		  		NOTE: Even if data[0] is 0, there is STILL a next 
 *				element!
 * 			    1 - If data[0] > 0, this is the start of the parameter
 *				list. Otherwise, this element is the same as 
 *				data[0] + 1, and this is the last element.
 *		      data[0] - The last parameter, if data[0] > 0.
 *		  data[0] + 1 - A pointer to a CODE type label.
 *
 * As a THREAD:
 * type		- Always THREAD.
 * scalar	- Always the name of the thread (a c string)
 * data		- Ignored. This kind of info is bat's job :).
 *
 *	NOTE ON LITERAL VALUES
 *
 * The lexer will lex literal values into a label, with a special name, NULL.
 * Literally, the pointer will be null. 
 * Since you can't possibly type a label with no name, this is a perfect 
 * "reserved" Label name.
 * In this case, the scalarType value will indicate the literal's type, and
 * the scalar field will hold the literal's data.
 */ 
typedef struct {
	char*	   name;
	void* 	   scalar;
	LabelType  type;
	void*	   data;
} Label;
extern const Label LABEL_INIT;

typedef struct EvaluatorT {
	PrefixOperator 	   preOp;
	Label*		   lhs_label;
	PostfixOperator    postOp;
	Operator 	   op;
	struct EvaluatorT* rhs_eval;
} Evaluator;
extern const Evaluator EVALUATOR_INIT;

typedef struct {
	PrefixOperator     preOp;
	Label*	           lhs_label;
	PostfixOperator    postOp;
	AssignmentOperator op;
	Evaluator*         rhs_eval;
} Statement;
extern const Statement STATEMENT_INIT;

// These structures are for storing the lexed statement list
// This is essentially a doubly linked list
typedef struct NodeT {
	Statement* 	statement;
	struct NodeT*	next;
	struct NodeT* 	prev;
} Node;

#endif
