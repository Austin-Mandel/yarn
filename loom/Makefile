ALL: shed
SRC="src"
SHED_SRC="$(SRC)/shed"
INC="lib"

# Shed - the lexer component
shed: shed_lex shed_c

shed_lex:
	flex $(SHED_SRC)/shed.lex

shed_c: lex.yy.c
	gcc -I$(INC) lex.yy.c $(SHED_SRC)/utils.c -o shed

clean_shed:
	rm lex.yy.c shed

# Cleans up all the components
clean: clean_shed
