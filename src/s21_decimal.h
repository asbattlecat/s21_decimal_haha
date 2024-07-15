#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <stdio.h>

#define ERROR -1;
#define OK 0
#define TOO_BIG 1
#define TOO_LITTLE 2
#define NULL_DIVIDE 3

typedef struct {
  unsigned int bits[4];
} s21_decimal;

void nulling(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result);
void print_binary(int num);
void print_bits(s21_decimal bit);
int get_scale(s21_decimal val);
int get_bit(s21_decimal value, int position);
float get_bit_float(float value, int position);
int get_sign(s21_decimal value);
void set_sign(s21_decimal **bit, int sign);
void set_bit(s21_decimal **result, int position, int bit);
void set_scale(s21_decimal *bit, int scale);
int search_bit(s21_decimal value, int position);
int search_bigger(s21_decimal value_1, s21_decimal value_2);

// не реализованные части см комментарии над функциями в s21_decimal.c 
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

#endif