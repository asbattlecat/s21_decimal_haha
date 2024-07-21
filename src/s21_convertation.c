#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int return_value = OK;
  if (src < 0) set_sign(&dst, 1);
  dst->bits[0] = src;
  return return_value;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_value = OK;
  *dst = src.bits[0];
  if (get_sign(src)) *dst *= -1;
  return return_value;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int r_value = OK;

  ufloat uf = {.f = src};
  int exponent = uf.parts.exponent - 126;
  int lowest_bit = 0;

  for(int bit = 0; bit < 23 && lowest_bit == 0; bit++){
    lowest_bit = uf.parts.mantissa >> bit & 0x01;
  }

  if(lowest_bit - 22 + exponent >= 0){
    dst->bits[0] = uf.parts.mantissa;
    // s21_shift(dst, exponent);
  }else{

  }
  return r_value;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst){
  
}