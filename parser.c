#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

extern int yylex();
int lookahead;

void E();
void EP();
void T();
void TP();
void F();

int main() {
  lookahead = yylex();

  E();

  if(lookahead == end_of_file)
    printf("Accepted!\n");
  else
    printf("Not-accepted!\n");

  return 0;
}

void syntatical_error(char *message) {
 fprintf(stderr, "Syntatical error occured: %s\n", message);
  exit(EXIT_FAILURE);
}

void E() {
  if(lookahead == '(' || lookahead == number_token) {
    printf("E => TE'\n");
    T();
    EP();
  }else {
    syntatical_error("Expected ( or number at the input");
  }
}
void EP() {
  if(lookahead == '+') {
    printf("E' => +TE'\n");
    lookahead = yylex();
    T();
    EP();
  }else if(lookahead == ')' || lookahead == end_of_file) {
    printf("E' => eps\n");
  }else {
    syntatical_error("Expected +, end_of_file or ) at the input");
  }
}

void T() {
  if(lookahead == '(' || lookahead == number_token) {
    printf("T => FT'\n");
    F();
    TP();
  }else {
    syntatical_error("Expected ( or number at the input");
  }
}
void TP() {
  if(lookahead == '*') {
    printf("T' => *FT'\n");
    lookahead = yylex();
    F();
    TP();
  }else if(lookahead == '+' || lookahead == ')' || lookahead == end_of_file) {
    printf("T' => eps\n");
  }else {
    syntatical_error("Expected *, +, ) or number at the input");
  }
}
void F() {
  if(lookahead == '(') {
    printf("F => (E)\n");
    lookahead = yylex();
    E();
    if(lookahead != ')')
      syntatical_error("Exptected )");
    lookahead = yylex();
  }else if(lookahead == number_token) {
    printf("F => number_token\n");
    lookahead = yylex();
  }else {
    syntatical_error("Exptected number or ( at the input");
  }
}
