#ifndef __value_stack_h
#define __value_stack_h

#include <stdio.h>
#include <stdlib.h>

#define N 100 

extern double value_stack[N]; 
extern int value_top; 

void value_push(double a); 
double value_pop(); 

#endif
