ALL: shed_lex shed

shed_lex: shed.lex
	flex shed.lex

shed: lex.yy.c utils.c
	gcc lex.yy.c utils.c -o shed

clean:
	rm shed lex.yy.c
