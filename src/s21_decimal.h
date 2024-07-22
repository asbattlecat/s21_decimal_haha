#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <stdio.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef struct {
    unsigned int bits[8];
} big_decimal;

void set_scale (s21_decimal *decimal,int scale);
void set_sign (s21_decimal *decimal, int sign);
void get_scale (s21_decimal *decimal,int *scale);
void get_sign (s21_decimal *value_1, int *sign_value_1, s21_decimal *value_2, int *sign_value_2);

void print_binary (int number);
void print_decimal (s21_decimal decimal);
void print_big_decimal (big_decimal big_decimal);
void decimal_to_big_decimal (s21_decimal *decimal, big_decimal *big_decimal);
void shift_left_big_decimal (big_decimal *big_decimal, int shift_value);
void addition_big_decimal (big_decimal *big_value_1, big_decimal *big_value_2, big_decimal *result);
void normalize_scales_big_decimal (big_decimal *big_value_1, int scale_1, big_decimal *big_value_2, int scale_2, int *result_scale);
void big_decimal_to_decimal (big_decimal *big_result, s21_decimal *result);
int compare_big_decimal (big_decimal *big_value_1, big_decimal *big_value_2);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif