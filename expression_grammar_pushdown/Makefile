CC = gcc
CLAGS = -Wall -Wextra

parser_push_down: parser_push_down.o lex.yy.o
        $(CC) $(CFLAGS) -o $@ $^
parser_push_down.o: parser_push_down.c tokeni.h
        $(CC) $(CFLAGS) -c $<
lex.yy.o: lex.yy.c tokeni.h
        $(CC) $(CFLAGS) -c $<
lex.yy.c: lexer.lex
        flex $<

.PHONY: clean
clean:
        rm -f *.o parser_push_down lex.yy.c *.o *~
