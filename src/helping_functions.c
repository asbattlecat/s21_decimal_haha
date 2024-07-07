#include "s21_decimal.h"

void nulling(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result) {
  for (int i = 0; i < 4 && value_1 != NULL; i++) {
    value_1->bits[i] = ZERO;
  }
  for (int i = 0; i < 4 && value_2 != NULL; i++) {
    value_2->bits[i] = ZERO;
  }
  for (int i = 0; i < 4 && result != NULL; i++) {
    result->bits[i] = ZERO;
  }
}

void set_scale(s21_decimal *value_1, int scale) {
  if (scale > 255) scale = scale & MAX_8_BITS;
  value_1->bits[3] = value_1->bits[3] | scale << 16;
}

void set_sign(s21_decimal *value_1, int sign) {
  if (sign > 1) sign = 1;
  value_1->bits[3] = value_1->bits[3] | sign << 31;
}

// считывание бита в определенной позиции в s21_decimal
int get_bit(s21_decimal value, int position) {
  if (!(position >= 0 && position <= 95)) return ERROR;
  int one = 1, int_number;
  int_number = define_int_number(&position);
  return (((one << position) & value.bits[int_number]) >> position);
}

// помещение бита в определенную позицию в s21_decimal
int set_bit(s21_decimal **result, int position) {
  if (!(position >= 0 && position <= 95)) return ERROR;
  int return_value = OK;
  int one = 1, int_number;
  int_number = define_int_number(&position);
  (*result)->bits[int_number] = (*result)->bits[int_number] | (one << position);
  return return_value;
}

// функция для определения того, какой бит в каком из интов мы рассматриваем
int define_int_number(int *position) {
  int int_number;
  if (*position <= 31) {
    int_number = 0;
  } else if (*position >= 32 && *position <= 63) {
    *position -= 32;
    int_number = 1;
  } else if (*position >= 64 && *position <= 95) {
    *position -= 64;
    int_number = 2;
  }
  return int_number;
}

void print_binary(int num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
}

void print_bits(s21_decimal value_1) {
  for (int i = 3; i >= 0; i--) {
    print_binary(value_1.bits[i]);
  }
}