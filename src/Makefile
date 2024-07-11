GCC=gcc
CVERSION=-std=c11
CFLAGS = 

s21_decimal.a:clear
	$(GCC) $(CVERSION) $(CFLAGS) s21_decimal.c s21_strdec.c -c
	ar cr s21_decimal.a s21_decimal.o s21_strdec.o
clear:
	rm -rf s21_decimal.a s21_decimal.o s21_strdec.o
test:s21_decimal.a
	$(GCC) $(CVERSION) $(CFLAGS) s21_decimal.a s21_test.c -o s21_test && ./s21_test
