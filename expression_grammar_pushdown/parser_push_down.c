#include <stidio.h>
#include <stdlib.h>

#include "tokeni.h"
#define MAX 1024
int stack[MAX];
int sp = 0; // <-- pointer to the position of the next element to be pushed onto the stack
int lookahead;

extern int yylex() // <-- function that do lexical analyzing and return tokens

int empty() {
  return sp == 0;
}
int full() {
  return sp >= MAX;
}

void push(int element) {
  if(full()) {
    fprintf(stderr, "Stack is full: StackOverflow\n");
    exit(EXIT_FAILURE);
  }
  stack[sp++] = element;
}
int pop() {
  if(empty()) {
    fprintf(stderr, "Stack is empty!\n");
    exit(EXIT_FAILURE);
  }
  return stack[--sp];
}
int top() {
   if(empty()) {
    fprintf(stderr, "Stack is empty!\n");
    exit(EXIT_FAILURE);
  }
  return stack[sp-1];
}

int main(){
  lookahead = yylex();
  push(E);

  while(!empty()) {
    int element = pop();
    switch(element) {
cas
