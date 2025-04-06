CC = gcc
CFLAGS = -Wall -g


default: run


all: postfix postfix_out

# Сборка первой части
postfix: postfix_main.o stack.o
	$(CC) $(CFLAGS) -o postfix postfix_main.o stack.o

# Сборка второй части 
postfix_out: postfix_out.o postfix.o stack.o value_stack.o
	$(CC) $(CFLAGS) -o postfix_out postfix_out.o postfix.o stack.o value_stack.o

# Запуск программы postfix_out после сборки
run: postfix_out
	./postfix_out


postfix_main.o: postfix.c stack.h
	$(CC) $(CFLAGS) -DPOSTFIX_MAIN -c postfix.c -o postfix_main.o

postfix.o: postfix.c stack.h
	$(CC) $(CFLAGS) -UPOSTFIX_MAIN -c postfix.c -o postfix.o

postfix_out.o: postfix_out.c value_stack.h
	$(CC) $(CFLAGS) -c postfix_out.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

value_stack.o: value_stack.c value_stack.h
	$(CC) $(CFLAGS) -c value_stack.c

# Очистка
clean:
	rm -f *.o postfix postfix_out
