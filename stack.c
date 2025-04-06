#include "stack.h"

char stack[N];
int top = -1; 

void push(char a) {
    if (top < N - 1) {
        stack[++top] = a;
    } else {
        fprintf(stderr, "Переполнение стека!\n");
        exit(EXIT_FAILURE);
    }
}

char pop() {
    if (top == -1) {
        fprintf(stderr, "Стек пуст!\n");
        exit(EXIT_FAILURE);
    } else {
        return stack[top--];
    }
}
