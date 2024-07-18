CFLAGS=-Wall -Werror -Wextra -std=c11


all: clean s21_decimal.a
	gcc $(CFLAGS) main.c s21_decimal.a -o main

clean: 
	rm -rf *.a *.o 

s21_decimal.a:
	gcc $(CFLAGS) s21_decimal.c -c 
	ar rc s21_decimal.a s21_decimal.o
	ranlib s21_decimal.a