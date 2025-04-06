#include "value_stack.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

// Функция для проверки, является ли строка числом включая дробные
int is_number(const char* str) {
    int has_dot = 0;
    int i = 0;

    // Проверяем, начинается ли строка с минуса для отрицательных чисел
    if (str[0] == '-') {
        i = 1; // Пропускаем знак минус
        if (str[1] == '\0') return 0; // Если строка состоит только из "-", это не число
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] == '.' && !has_dot) {
            has_dot = 1; // Разрешаем только одну точку
        } else if (!isdigit(str[i])) {
            return 0; // Если символ не цифра и не точка, это не число
        }
    }
    return 1;
}

// Функция для выполнения арифметической операции
double apply_operator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Ошибка: деление на ноль!\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            fprintf(stderr, "Неизвестный оператор: %c\n", op);
            exit(EXIT_FAILURE);
    }
}

// Функция для вычисления постфиксного выражения
double evaluate_postfix(const char* postfix) {
    value_top = -1; // Инициализируем стек

    char* postfix_copy = strdup(postfix); // Копируем строку, чтобы не изменять оригинал
    if (!postfix_copy) {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        exit(EXIT_FAILURE);
    }

    char* token = strtok(postfix_copy, " ");
    while (token != NULL) {
        if (is_number(token)) {
            // Если токен — число, преобразуем его в double и кладём в стек
            double num = atof(token);
            value_push(num);
        } else {
            // Если токен — оператор, извлекаем два числа из стека
            if (value_top < 1) {
                fprintf(stderr, "Недостаточно операндов для оператора %s!\n", token);
                free(postfix_copy);
                exit(EXIT_FAILURE);
            }
            double b = value_pop(); 
            double a = value_pop(); 
            double result = apply_operator(a, b, token[0]);
            value_push(result); // Помещаем результат обратно в стек
        }
        token = strtok(NULL, " ");
    }

    // В конце в стеке должен остаться ровно один элемент — результат
    if (value_top != 0) {
        fprintf(stderr, "Ошибка: некорректное постфиксное выражение!\n");
        free(postfix_copy);
        exit(EXIT_FAILURE);
    }

    double final_result = value_pop();
    free(postfix_copy);
    return final_result;
}

int main() {
    char str[N];
    printf("Введите выражение:  ");
    fgets(str, N, stdin);
    str[strcspn(str, "\n")] = '\0'; // Удаляем символ новой строки

  
    extern char* func_postfix(char* str, int len);
    char* postfix = func_postfix(str, strlen(str));

   
    double result = evaluate_postfix(postfix);
    printf("Результат: %.2f\n", result);

    return 0;
}
