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

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // sub - subtraction
  int resurn_value = OK, sub;
  for (int position = 0; position < 95; position++) {
    sub = get_bit(value_1, position) - get_bit(value_2, position);
    if (sub == 1) {
      set_bit(&result, position);
    } else if (sub == -1) {
      
    }
  }
}

/*
  Правила вычитания:
  1) Разница битов = 0
    1.1) Результат = 0

  2) Разница битов = 1
    2.1) Результат = 1

  3) Разница битов = -1
    3.1) Ищем более старший бит, который равен 1
    3.2) Занимаем у него единицу, он становится 0
    3.3) Все относительно него младшие биты становятся 1,
         а тот бит, для которого занимали - становится 10, то есть 2
    3.4) Производим вычитание, то есть бит, для которого мы занимали единицу,
         становится 1

  Поиск старшего единичного бита относительно рассматриваемого:

*/