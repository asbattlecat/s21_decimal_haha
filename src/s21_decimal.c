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
  value_1.bits[0] = 0b11000000000000000000000000000000;
  value_2.bits[0] = 0b10000000000000000000000000000000;
  // result of sum: 0b...100001
  set_scale(&value_1, 0);
  set_sign(&value_1, 0);
  if (!s21_add(value_1, value_2, &result)) {
    printf("Result: \n\n");
    print_bits(result);
    printf("\n");
  }
  for (int i = 0; i <= 3; i++) {
    printf("%u ", value_1.bits[i]);
  }
}

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

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // buffer - для "запоминания" того, что к следующему биту перешла 1
  int return_value = OK, buffer = 0, sum;
  int first, second;
  for (int position = 0; position < 95; position++) {
    first = get_bit(value_1, position);
    second = get_bit(value_2, position);
    sum = first + second + buffer;
    buffer = 0;
    if (sum == 1) {
      set_bit(&result, position);
    } else if (sum == 2) {
      buffer = 1;
    } else if (sum == 3) {
      buffer = 1;
      set_bit(&result, position);
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
int set_bit(s21_decimal **result, int position) {
  if (!(position >= 0 && position <= 95)) return ERROR;
  int return_value = OK;
  int one = 1, int_number;
  int_number = define_int_number(&position);
  (*result)->bits[int_number] = (*result)->bits[int_number] | (one << position);
  return return_value;
}

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