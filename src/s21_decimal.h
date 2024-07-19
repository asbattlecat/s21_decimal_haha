#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <stdio.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

void set_scale_and_sign (s21_decimal *decimal,int scale, int sign);
void get_scale_and_sign (s21_decimal *decimal,int *scale, int *sign);
void print_binary (int number);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif