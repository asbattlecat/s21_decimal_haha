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
void set_scale(s21_decimal *bit, int scale);
int get_scale(s21_decimal val);
void set_sign(s21_decimal *bit, int sign);
int get_bit(s21_decimal value, int position);
void set_bit(s21_decimal **result, int position);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif