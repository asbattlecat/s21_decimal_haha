#include <stdio.h>

#include "s21_decimal.h"

int main(void) {
  s21_decimal dec1, dec2, res_dec;

  dec1.bits[0] = 349;
  dec1.bits[1] = 0x00000000;
  dec1.bits[2] = 0x00000000;
  dec1.bits[3] = 0x80020000;

  dec2.bits[0] = 10000;
  dec2.bits[1] = 0x00000000;
  dec2.bits[2] = 0x00000000;
  dec2.bits[3] = 0x00060000;

  s21_add(dec1, dec2, &res_dec);

  s21_round(dec1, &dec1);

  printf("dec1.bits[0] = %d\n", dec1.bits[0]);
  printf("dec1.bits[1] = %x\n", dec1.bits[1]);
  printf("dec1.bits[2] = %x\n", dec1.bits[2]);
  printf("dec1.bits[3] = %x\n\n", dec1.bits[3]);

  printf("dec2.bits[0] = %d\n", dec2.bits[0]);
  printf("dec2.bits[1] = %x\n", dec2.bits[1]);
  printf("dec2.bits[2] = %x\n", dec2.bits[2]);
  printf("dec2.bits[3] = %x\n\n", dec2.bits[3]);

  printf("res_dec.bits[0] = %x\n", res_dec.bits[0]);
  printf("res_dec.bits[1] = %x\n", res_dec.bits[1]);
  printf("res_dec.bits[2] = %x\n", res_dec.bits[2]);
  printf("res_dec.bits[3] = %x\n\n", res_dec.bits[3]);

  printf("last digit = %d\n", res_dec.bits[0] % 10);

  return 0;
}