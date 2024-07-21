GCC=gcc  -std=c11 #-Wall -Werror -Wextra
FILES=s21_decimal.c lib.c s21_convertation.c

add: build

build:
	$(GCC) $(FILES) && ./a.out

clang:
	clang-format -i -style=google *.c *.h