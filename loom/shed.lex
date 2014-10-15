%x comment string statment
%top {
	#include "lexer.h
}

/* Scalar Value patterns 							*/
INTEGER		[0-9]+
SIGNED_INTEGER	[\+\-]{INTEGER}
HEX_INTEGER	0x[A-Fa-f0-9]+
BIN_INTEGER	0b[01]+
DOUBLE		[\+\-]?{INTEGER}+\.{INTEGER}+|NaN|Inf 

/* Tokens									*/
LABEL		[a-zA-Z_][a-zA-Z0-9_]*
ASSIGNMENT	=|+=|-=|/=|\*=

%%
		/* Create a temporary struct to hold incomplete statements */
		Statement temp;

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
	}
}

		/* STATEMENT PARSING */
{LABEL}	{
		temp.lhs_label = yytext;
		BEGIN(statement);
}
<statement>{
	{ASSIGNMENT}	{
		if        (yytext[0] == '=') {

		} else if (yytext[0] == '+') {

		} else if (yytext[0] == '-') {

		} else if (yytext[0] == '/') {
		
		} else if (yytext[0] == '*') {

		} else {

		}
	};
	
	";"		BEGIN(INITIAL);
}
	/* Default action is to complain */
.*	printf("Syntax error: %s", yytext);

%%


