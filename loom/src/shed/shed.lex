%option stack
%x comment statement_begin statement evaluator
%top {
	#include <assert.h>
	#include <stdlib.h>
	#include <string.h>
	#include "lexer.h"
	#include "utils.h"

	Node* defaultBlock;
	Node* curNode;
	Node* prevNode;
	Statement* temp;

	void getOp(char* yytext, Statement* temp);
	void nextStatement();
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

		/*     RULES     */

\s		/* Eat up whitespace */

		/* COMMENT PARSING */
\#.*		BEGIN(comment);
<comment>{
	[^\n]*	/* Eat up all non-newline text */
	[\n]	BEGIN(INITIAL);
}


		/* STATEMENT PARSING */

		/* Statments starting with a string literal */
"\"\""		{
			// Create new label
			Label label = LABEL_INIT;
			label.type  = STRING_T;
			label.scalar = strdup(yytext);
		}

\".+\"		{
			printf("Got string: %s\n", yytext);
		}

{LABEL}		{	// Create new label
			Label label = LABEL_INIT;
			label.name = strdup(yytext);
			printf("Label discovered: %s\n", label.name);
			temp->lhs_label = &label;
			BEGIN(statement_begin);
		}
<statement_begin>{ASSIGNMENT} 	getOp(yytext, temp); //BEGIN(statement);
<statement_begin>";"		{
					printf("Statement completed:\n");
					printStatement(temp);
					nextStatement();
					BEGIN(INITIAL);
				}

%%



		/*     USER CODE     */

/* Same as default yywrap function, always returns true */
int yywrap () {
	return 1;
}

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

void nextStatement() {
	temp = malloc(sizeof(Statement));
	assert(temp != NULL);
}

int main () {
	nextStatement();	
	yylex();
	free(temp);
}

		/*     EOF     */
