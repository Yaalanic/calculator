#include "value_stack.h"

double value_stack[N]; // Определяем стек
int value_top = -1; // Инициализируем указатель вершины

void value_push(double a) {
    if (value_top < N - 1) {
        value_stack[++value_top] = a;
    } else {
        fprintf(stderr, "Переполнение стека при вычислении!\n");
        exit(EXIT_FAILURE);
    }
}

double value_pop() {
    if (value_top == -1) {
        fprintf(stderr, "Стек пуст!\n");
        exit(EXIT_FAILURE);
    } else {
        return value_stack[value_top--];
    }
}
