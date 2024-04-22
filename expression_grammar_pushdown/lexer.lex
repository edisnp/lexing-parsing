%option noyywrap
%option noinput
%option nounput

%{
  #include <stdio.h>
  #include <stdlib.h>

  #include "tokeni.h"
%}

%%

0|[1-9][0-9]* {return num_token;}

[()+*] {return *yytext;}

[\n] {return eoi;}

[ \t] {}

. {
  fprintf(stderr, "Leksicka greska %s\n", yytext);
  exit(EXIT_FAILURE);
}

%%
