#include "stack.h"
#include <string.h>
#include <ctype.h> // для isdigit

char postfix[N*2]; // увеличиваем размер для пробелов
int post_index = 0;

int priority(char op) {  // приоритет операций
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

char* func_postfix(char* str, int len) {
    post_index = 0;
    top = -1;

    int expect_operand = 1; // Флаг: ожидаем операнд 1  или оператор 0

    for (int i = 0; i < len; ++i) {
        char c = str[i];
        if (c == ' ') continue;

        // Проверяем, является ли текущий символ числом
        if (isdigit(c) || (c == '-' && expect_operand)) {
            // Если это унарный минус или начало числа
            if (c == '-' && expect_operand) {
                postfix[post_index++] = c; // Добавляем минус как часть числа
                i++;
                if (i >= len || !isdigit(str[i])) {
                    fprintf(stderr, "Ошибка: ожидалось число после унарного минуса\n");
                    exit(EXIT_FAILURE);
                }
                c = str[i];
            }
            // Собираем число включая дробную часть
            while (i < len && (isdigit(str[i]) || str[i] == '.')) {
                postfix[post_index++] = str[i++];
            }
            postfix[post_index++] = ' '; // Пробел после числа
            i--; // т.к. цикл for тоже увеличивает i
            expect_operand = 0; // После числа ожидаем оператор
        } else if (c == '(') {
            push(c);
            expect_operand = 1; // После открывающей скобки ожидаем операнд
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[post_index++] = pop();
                postfix[post_index++] = ' ';
            }
            pop(); // убираем '('
            expect_operand = 0; // После закрывающей скобки ожидаем оператор
        } else {
            // Это оператор (+, -, *, /)
            if (expect_operand && c == '-') {
                // Унарный минус уже обработан выше, здесь это ошибка
                fprintf(stderr, "Ошибка: некорректное использование оператора\n");
                exit(EXIT_FAILURE);
            }
            while (top != -1 && stack[top] != '(' && priority(stack[top]) >= priority(c)) {
                postfix[post_index++] = pop();
                postfix[post_index++] = ' ';
            }
            push(c);
            expect_operand = 1; // После оператора ожидаем операнд
        }
    }

    // Выталкиваем оставшиеся операторы
    while (top != -1) {
        char op = pop();
        if (op != '(') {
            postfix[post_index++] = op;
            postfix[post_index++] = ' ';
        }
    }
    postfix[post_index] = '\0'; // Завершаем строку
    return postfix;
}

#ifdef POSTFIX_MAIN
int main() {
    char str[N];
    printf("Введите выражение: ");
    fgets(str, N, stdin);
    str[strcspn(str, "\n")] = '\0'; // удаляем символ новой строки
    char* res = func_postfix(str, strlen(str));
    printf("%s\n", res);
    return 0;
}
#endif
