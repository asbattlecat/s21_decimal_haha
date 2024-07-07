#include "s21_decimal.h"

void nulling(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result) {
  for (int i = 0; i < 4 && value_1 != NULL; i++) {
    value_1->bits[i] = 0;
  }
  for (int i = 0; i < 4 && value_2 != NULL; i++) {
    value_2->bits[i] = 0;
  }
  for (int i = 0; i < 4 && result != NULL; i++) {
    result->bits[i] = 0;
  }
}

int get_scale(s21_decimal val){
  return val.bits[3] >> 16 & 0xFF;
}

void set_scale(s21_decimal *val, int scale) {
  if (scale > 255) scale = scale & 0xFF;
  val->bits[3] &= ~(unsigned int)0xFF << 16;
  val->bits[3] |= scale << 16;
}

void set_sign(s21_decimal *value_1, int sign) {
  if (sign > 1) sign = 1;
  value_1->bits[3] = value_1->bits[3] | sign << 31;
}

// считывание бита в определенной позиции в s21_decimal
int get_bit(s21_decimal value, int position) {
  return value.bits[position / 32] >> (position % 32) & 0x01;
}

// помещение бита в определенную позицию в s21_decimal
void set_bit(s21_decimal **value, int position) {
  (*value)->bits[position / 32] |= 0x01 << (position % 32);
}

void print_binary(int num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
}

void print_bits(s21_decimal val) {
  printf("[%10s] %d\n", "Exponent", get_scale(val));
  for (int i = 3; i >= 0; i--) {
    print_binary(val.bits[i]);
    printf(" ");
  }
}