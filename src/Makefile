CFLAGS=-Wall -Werror -Wextra -std=c11 
POSIX=-D_POSIX_C_SOURCE=200809L
COVER=--coverage
TESTS=s21_decimal_test.c

all: clean s21_decimal.a
	gcc $(CFLAGS) $(POSIX) main.c s21_decimal.a -o main

clean:
	rm -rf *.a *.o main *gcno *.gcda test *gcov ./coverage *.info *gch *.html *.css

test: clean s21_decimal.a
	gcc $(CFLAGS) $(TESTS) -c
	ar rc s21_decimal_test.a s21_decimal_test.o
	ranlib s21_decimal_test.a
	gcc $(CFLAGS) $(COVER) -o test s21_decimal.a s21_decimal_test.a s21_decimal.c -lcheck -lm -lsubunit
	chmod +x test
	./test

s21_decimal.a:
	gcc $(CFLAGS) s21_decimal.c -c
	ar rc s21_decimal.a s21_decimal.o
	ranlib s21_decimal.a

clangchk:
	clang-format -n *.c *.h --style=Google
clang:
	clang-format -i *.c *.h --style=Google

