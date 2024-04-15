%option noyywrap
%option noinput
%option nounput

%{
  #include <stdio.h>
  #include <stdlib.h>

  #include "tokeni.h"
%}
  
%%

0|[1-9][0-9]* { return number_token;}

[ \t] { } // Empty action
[\n] {return end_of_file;}
[()*+] { return *yytext;}

. {
  fprintf(stderr, "Lexical error, unrecognized character: %s\n", yytext);
  exit(EXIT_FAILURE);
}

%%
