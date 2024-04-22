#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

void error(char *message) {
  fprintf(stderr, "Syntatical error: %s\n", message);
  exit(EXIT_FAILURE);
}

int lookahead;
extern int yylex();

void matlab_program_start();
void matlab_program();
void if_statement();
void for_statement();
void if_statementP();
void for_statementP();
void error_statement();
void assignment();
void lista();
void listaP();
void listaPP();

void matlab_program_start() {
  if(lookahead == function_token) {
    printf("MatlabProgramStart -> function_token id = id(id) MatlabProgram\n");
    lookahead = yylex();
    if(lookahead != id_token)
      error("expect id_token");
    lookahead = yylex();
    if(lookahead != '=')
      error("expect equality sign '='");
    lookahead = yylex();
    if(lookahead != id_token)
      error("expect id_token");
    lookahead = yylex();
    if(lookahead != '(')
      error("expect ( at the input stream");
    lookahead = yylex();
    if(lookahead != id_token)
      error("expect id_token");
    lookahead = yylex();
    if(lookahead != ')')
      error("expect ) at the input stream");

    lookahead = yylex();
    matlab_program();
  }else {
    error("function token at the input is mandatory");
  }
}
void matlab_program() {
  if(lookahead == if_token) {
    printf("MatlabProgram => IfStatement MatlabProgram\n");
    if_statement();
    matlab_program();
  }else if(lookahead == for_token) {
    printf("MatlabProgram => ForStatement MatlabProgram\n");
    for_statement();
    matlab_program();
  }else if(lookahead == eoi) {
    printf("MatlabProgram => eps\n");
  }else {
    error("expected for or if token");
  }
}

void if_statement() {
  if(lookahead == if_token) {
    printf("IfStatement => if_token IfStatementP\n");
    lookahead = yylex();
    if_statementP();
  }else{
    error("expect if_token");
  }
}
void if_statementP() {
  if(lookahead == length_token) {
    printf("IfStatementP => length_token (id) compare_token num_token error_statement end_token\n");
    lookahead = yylex();
    if(lookahead != '(')
      error("expected ( at the input stream");
    lookahead = yylex();
    if(lookahead != id_token)
      error("expected id_token at the input stream");
    lookahead = yylex();
    if(lookahead != ')')
      error("extected )");
    lookahead = yylex();
    if(lookahead != compare_token)
      error("compare_token error");
    lookahead = yylex();
    if(lookahead != num_token)
      error("num_token expected!");

    lookahead = yylex();
    error_statement();

    if(lookahead != end_token)
      error("expected end_token at the end of if block!");

    lookahead = yylex();
  }else if(lookahead == isequal_token) {
    printf("IfStatement => ~isequal(id, id) ErrorStatement end_token\n");
    lookahead = yylex();
    if(lookahead != '(')
      error("expected (");
    lookahead = yylex();
    if(lookahead != id_token)
      error("id_token error");
    lookahead = yylex();
    if(lookahead != ',')
      error("separator error");
    lookahead = yylex();
    if(lookahead != id_token)
      error("expected id_token");
    lookahead = yylex();
    if(lookahead != ')')
      error("expected (");

    lookahead = yylex();
    error_statement();

    if(lookahead != end_token)
      error("expected end_token at the end of if block!");
    lookahead = yylex();
  }else {
    error("expected length_token or isequal_token at the input");
  }
}

void for_statement() {
  if(lookahead == for_token) {
    printf("ForStatement => for_token id = ForStatementP\n");
    lookahead = yylex();
    if(lookahead != id_token)
      error("id_token error");
    lookahead = yylex();
    if(lookahead != '=')
      error("=");

    lookahead = yylex();
    for_statementP();
  }else {
    error("expected for_token at the input");
  }
}

void for_statementP() {
  if(lookahead == num_token) {
    printf("ForStatementP => num_token:num_token:num_token Assignment\n");
    lookahead = yylex();
    if(lookahead != ':')
      error(":");
    lookahead = yylex();
    if(lookahead != num_token)
      error("num_token");
    lookahead = yylex();
    if(lookahead != ':')
      error(":");
    lookahead = yylex();
    if(lookahead != num_token)
      error("num_token");

    lookahead = yylex();
    assignment();
    if(lookahead != end_token)
      error("end_token error");
    lookahead = yylex();
  }else if(lookahead == length_token) {
    printf("ForStatementP => length_token(id):num_token:num_token assignment error_statement end_token\n");
    lookahead = yylex();
  
    if(lookahead != '(')
      error("(");
    lookahead = yylex();
    
    if(lookahead != id_token)
      error("id_token");
    lookahead = yylex();

    if(lookahead != ')')
      error(")");
    lookahead = yylex();
    if(lookahead != ':')
      error(":");
    
    lookahead = yylex();
    if(lookahead != num_token)
      error("num_token");
    lookahead = yylex();
    if(lookahead != ':')
      error(":");
    lookahead = yylex();
    if(lookahead != num_token)
      error("num_token");

    lookahead = yylex();
    assignment();
    error_statement();

    if(lookahead != end_token)
      error("end_token");
    lookahead = yylex();
  }else {
    error("num_token or length_token expected");
  }
}

void assignment() {
  if(lookahead == id_token) {
    printf("Assignment => id(num_token) = [Lista]\n");
    lookahead = yylex();
    if(lookahead != '(')
      error("(");
    lookahead = yylex();
    if(lookahead != id_token)
      error("num_token EError");
    lookahead = yylex();
    if(lookahead != ')')
      error(")");
    lookahead = yylex();
    if(lookahead != '=')
      error("=");
    lookahead = yylex();
    if(lookahead != '[')
      error("[");

    lookahead = yylex();
    lista();
    if(lookahead != ']')
      error("]");
    lookahead = yylex();
  }else {
    error("id_token error");
  }
}
void lista() {
  if(lookahead == num_token) {
    printf("lista => listaP\n");
    listaP();
  }else if(lookahead == ']') {
    printf("lista => eps\n");
  }else {
    error("lista error");
  }
}
void listaP() {
  if(lookahead == num_token) {
    printf("listaP => num_token listaPP\n");
    lookahead = yylex();
    listaPP();
  }else {
    error("listaP error");
  }
}
void listaPP() {
  if(lookahead == ',') {
    printf("listaPP => , num_token listaPP\n");
    lookahead = yylex();
    if(lookahead != num_token)
      error("num_token");
    lookahead = yylex();
    listaPP();
  }else if(lookahead == ']') {
    printf("listaPP => eps\n");
  }else {
    error("listaPP error");
  }
}
void error_statement() {
  if(lookahead == error_token){
    printf("error_statement => error_token(comment)\n");
    lookahead = yylex();
    if(lookahead != '(')
      error(")");
    lookahead = yylex();
    if(lookahead != text_token)
      error("text token error");
    lookahead = yylex();
    if(lookahead != ')')
      error("(");
    lookahead = yylex();
  }else {
    error("error_statement error");
  }
}

int main() {
  lookahead = yylex();
  matlab_program_start();

  if(lookahead == eoi)
    printf("Accepted!\n");
  else
    printf("Not accepted!\n");

  return 0;
}
