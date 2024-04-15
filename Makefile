CC = gcc
CFLAGS = -Wall -Wextra

parser: parser.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^

parser.o: parser.c tokeni.h
	$(CC) $(CFLAGS) -c $<

lex.yy.o: lex.yy.c tokeni.h
	$(CC) $(CFLAGS) -c $<

lex.yy.c: lexer.lex
	flex $<

.PHONY: clean
clean:
	rm -f parser lex.yy.c *.o *~
