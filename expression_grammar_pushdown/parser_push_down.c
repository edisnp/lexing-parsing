#include <stidio.h>
#include <stdlib.h>

#include "tokeni.h"
#define MAX 1024
int stack[MAX]; // static stack implemented via static array
int sp = 0; // <-- pointer to the position of the next element to be pushed onto the stack
int lookahead;

extern int yylex() // <-- function that do lexical analyzing and return tokens
void error(char* message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}
int empty() {
  return sp == 0;
}
int full() {
  return sp >= MAX;
}

void push(int element) {
  /*if(full()) {
    fprintf(stderr, "Stack is full: StackOverflow\n");
    exit(EXIT_FAILURE);
  }*/
  is(full())
    error("Stack-overflow occured!\n");
  stack[sp++] = element;
}
int pop() {
  /*if(empty()) {
    fprintf(stderr, "Stack is empty!\n");
    exit(EXIT_FAILURE);
  }*/
  if(empty())
      error("Stack-underflow occured!\n");
  
  return stack[--sp];
}
int top() {
   /*if(empty()) {
    fprintf(stderr, "Stack is empty!\n");
    exit(EXIT_FAILURE);
  }*/
  if(empty())
    error("Stack is emptyh!\n");
  
  return stack[sp-1];
}

int main(){
  lookahead = yylex(); //reading tokens from the input stream (for example stdin)
  push(E);

  while(!empty()) {
    int element = pop();
    switch(element) {
    case E:
      if(lookahead == '(' || lookahead == num_token) {
        printf("E => TE'\n");
        push(EP);
        push(T);
      }else {
        error("Expected input: ( or num_token");
      }
      break;
    case T:
      if(lookahead == '(' || lookaheda == num_token) {
        printf("T => FT'\n");
        push(TP);
        push(F);
      }else {
        error("Expected input: ( or num_token");
      }
      break;
    case EP:
      if(lookahead == '+') {
        printf("E' => +TE'\n");
        push(EP);
        push(T);
        push('+');
      }else if(lookahead == eoi || lookahead == ')') {
        printf("E' => eps\n");
      }else {
        error("Expected input: +, eoi, or )");
      }
      break;
    case TP:
      if(lookahead == '*') {
        printf("T' => *FT'\n");
        push(TP);
        push(F);
        push('*');
      else if(lookahead == '+' || lookahead == eoi || lookahead ==  ')') {
        printf("T' => eps\n");
      }else {
        error("Expected input: *, +, ), or eoi");
      }
      break;
    case F:
      if(lookahead == '(') {
        printf("F => (E)\n");
        push(')');
        push(E);
        push('(');
      }else if(lookahead == num_token) {
        printf("F => num\n");
        push(num_token);
      }else {
        error("Expected input: ( or num_token");
      }
      break;
    default:
      if(lookahead != element) {
        error("Input is not part of the language!\n");
      }
      lookahead = yylex(); // <-- reading next token from the input stream
    }
  }
  if(lookahead == eoi)
    printf("Accepted!\n");
  else
    printf("Not accepted!\n");

  return 0;
}
