CC = gcc
CFLAGS = -Wall -Wextra -g

matlab_like_parser: matlab_like_parser.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^

matlab_like_parser.o: matlab_like_parser.c tokeni.h
	$(CC) $(CFLAGS) -c $<

lex.yy.o: lex.yy.c tokeni.h
	$(CC) $(CFLAGS) -c $<

lex.yy.c: lexer.lex
	flex $<

.PHONY: clean
clean:
	rm -f matlab_like_parser *~ *.o lex.yy.c
