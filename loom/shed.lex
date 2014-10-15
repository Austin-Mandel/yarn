%x comment string statment
%top {
	#include <assert.h>
	#include <stdlib.h>
	#include <string.h>
	#include "lexer.h"

	Node* node, prevNode;
	CodeBlock* defaultBlk;
	Statement* temp;

	/* Helper Functions */
	void getOp(char* yytext, Statement* temp) {
		if        (yytext[0] == '=') {
			// Assignment operation
			temp->op = ASSIGN;
		} else if (yytext[0] == '+') {
			// Append operation
			temp->op = APPEND;
		} else if (yytext[0] == '-') {
			// Remove operation
			temp->op = REMOVE;
		} else if (yytext[0] == '/') {
			// Slice operation
			temp->op = SLICE;
		} else if (yytext[0] == '*') {
			// Multiply operation
			temp->op = MULTIPLY;
		} else {
			printf ("Syntax Error: Unknown operator '%s'", yytext);
		}
	}
}

/* Scalar Value patterns 							*/
INTEGER		[0-9]+
SIGNED_INTEGER	[\+\-]{INTEGER}
HEX_INTEGER	0x[A-Fa-f0-9]+
BIN_INTEGER	0b[01]+
DOUBLE		[\+\-]?{INTEGER}+\.{INTEGER}+|NaN|Inf 

/* Tokens									*/
LABEL		[a-zA-Z_][a-zA-Z0-9_]*
ASSIGNMENT	"="|"+="|"-="|"/="|"*="
OPERATOR	"+"|"-"|"*"|"%"|"^"|"&"|"!"|"("|")"|"++"|"--"|"&&"|"||"|"<<"|">>"
POSTFIX_BEGIN	"["|"<"
POSTFIX_END	"]"|">"
BLOCK_BEGIN	"{"
BLOCK_END	"}"

%%
%option stack

		/* COMMENT PARSING */
"#"		BEGIN(comment);
<comment>{
	[^\n]*	/* Eat up all non-newline text */
	[\n]	BEGIN(INITIAL);
}

		/* STRING PARSING */
\"	BEGIN(string);
<string>{
	[^\"]*	yymore();
	\"	{	
			yyless(1);
			printf("Got string: %s\n", yytext);
			BEGIN(INITIAL);
		};
}

		/* STATEMENT PARSING */
{LABEL}		{
			temp->lhs_label = &yytext;
		};	
<statement>{
		/* Array Handling */
	"["	{
		temp->postOp = ARRAY;
		
	};

	{ASSIGNMENT}	getOp (yytext, temp);
	
			/* End of statement */
	";"	{
			prevNode = node;
			node = malloc(sizeof(Node));
			assert(node != NULL);
			prevNode->next = node;
			node->prev = prevNode;
			temp = malloc(sizeof(Statement));
			assert(temp != NULL);
			node->statement = temp;
			
			yy_pop_state();
		};
}
	/* Default action is to complain */
.*	printf("Syntax error: %s", yytext);

%%

int main() {
	/* Create a temporary struct to hold incomplete statements */
	temp = malloc(sizeof(Statement));
	assert(temp != NULL);

	/* Create the initial structure for storing Statments in a Code Block */
	node = malloc(sizeof(Node));
	assert(node != NULL);

	/* Create the default code block */
	defaultBlk = malloc(sizeof(CodeBlock));
	asset(defaultBlk != NULL);

	/* Setup code block structure */
	node->prev = NULL;
	node->statement = temp;
	defaultBlk->first = node;

	/* Lex the input */
	yylex();
}
