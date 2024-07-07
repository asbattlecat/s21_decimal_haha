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

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // buffer - для "запоминания" того, что к следующему биту перешла 1
  int return_value = OK, buffer = 0, sum;
  for (int position = 0; position < 95; position++) {
    sum = get_bit(value_1, position) + get_bit(value_2, position) + buffer;
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