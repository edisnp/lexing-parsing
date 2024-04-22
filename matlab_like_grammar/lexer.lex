%option noyywrap
%option noinput
%option nounput

%{
  #include <stdio.h>
  #include <stdlib.h>

  #include "tokeni.h"
%}

%%
error {return error_token;}
length {return length_token;}
if {return if_token;}
for {return for_token;}
end {return end_token;}
function {return function_token;}
[\'][a-zA-Z_0-9 ]*[\'] {return text_token;}
[a-zA-Z_][a-zA-Z_0-9]* {return id_token;}

[%].* {}

[<>] {return compare_token;}
[=()+*,\[\]:] {return *yytext;}
[~]isequal {return isequal_token;}
[ \t\n] {}

0|[1-9][0-9]*|[-][1-9][0-9]* {return num_token;}

. {
  fprintf(stderr, "Lexical error!\n");
  exit(EXIT_FAILURE);
}
%%
  /*
int main() {
  int lookahead;
  while((lookahead = yylex()) != eoi) {
    if(lookahead == function_token)
      printf("YES\n");
    else if(lookahead == id_token)
      printf("jeste\n");
    else if(lookahead == special_character_token) {
      printf("Special\n");
    }else if(lookahead == isequal_token) {
      printf("ISEQ\n");
    }else if(lookahead == end_token) {
      printf("ENDTOKEN\n");
    }else if(lookahead == text_token) {
      printf("TEXT\n");
    }else if(lookahead == for_token) {
      printf("FOR\n");
    }else if(lookahead == length_token) {
      printf("HAAAA\n");
    }else if(lookahead == if_token) {
      printf("KONJINA\n");
    }else if(lookahead == compare_token) {
      printf("UPoredi\n");
    }else if(lookahead == komentar){
      printf("POSTO\n");
    }else{
      printf("NO\n");
    }
  }
  
  
  return 0;
  }*/
