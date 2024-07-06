#include "s21_decimal.h"

/*
  Рассмотрим порядок интов и битов
  Первый инт (bits[0]) - справа налево от 0 до 31
  Второй инт (bits[1]) - прилепляем его слева от первого инта
  И так далее
*/

int main() {
  s21_decimal value_1, value_2, result;
  nulling(&value_1, &value_2, &result);
  value_1.bits[0] = 0b00000000000000000000000000010101;
  value_2.bits[0] = 0b00000000000000000000000000001100;
  set_scale(&value_1, 0);
  set_sign(&value_1, 0);

  print_bits(value_1);

  for (int i = 0; i <= 3; i++) {
    printf("%u ", value_1.bits[i]);
  }
}

void nulling(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    value_1->bits[i] = ZERO;
  }
  for (int i = 0; i < 4; i++) {
    value_2->bits[i] = ZERO;
  }
  for (int i = 0; i < 4; i++) {
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

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // buffer - для "запоминания" того, что к следующему биту перешла 1
  int return_value = OK, buffer, sum;
  for (int i = 0; i < 95; i++) {
    sum = get_bit(value_1, i) + get_bit(value_2, i);
    buffer = 0;
    if (sum == 0) {
      continue;
    } else if (sum == 1) {

    }
  }
  return return_value;
}

int get_bit(s21_decimal value, int position) {
  if (!(position >= 0 && position <= 95)) return ERROR;

  // int_number - ячейка в bits, в структуре s21_decimal, от 1 до 3
  int one = 1, int_number;
  int_number = define_int_number(&position);
  return (((one << position) & value.bits[int_number]) >> position);
}

// сделать (скопировал из get_bit для переработки)
void set_bit(s21_decimal **result, int position) {
  if (!(position >= 0 && position <= 95)) return ERROR;

  int one = 1, int_number;
  int_number = define_int_number(&position);
  result->bits[int_number] = ;
}

int define_int_number(int *position) {
  int int_number;
  if (position <= 31) {
    int_number = 0;
  } else if (position >= 32 && position <= 63) {
    position -= 32;
    int_number = 1;
  } else if (position >= 64 && position <= 95) {
    position -= 64;
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
  for (int i = 0; i < 4; i++) {
    print_binary(value_1.bits[i]);
    printf("\n");
  }
}