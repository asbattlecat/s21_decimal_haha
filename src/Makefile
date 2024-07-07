GCC=gcc -Wall -Werror -Wextra -std=c11
FILES=s21_decimal.c s21_decimal.h helping_functions.c

add: build

build:
	$(GCC) $(FILES) && ./a.out

clang:
	clang-format -i -style=google *.c *.h