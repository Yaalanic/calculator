#ifndef __stack_h
#define __stack_h

#include <stdio.h>
#include <stdlib.h>

#define N 100 

extern char stack[N]; 
extern int top; 

// Прототипы функций
void push(char a);
char pop();

#endif
