#include "s21_decimal.h"


/*
  @param (int) - 123
  Рассмотрим порядок интов и битов
  Первый инт (bits[0]) - справа налево от 0 до 31
  Второй инт (bits[1]) - прилепляем его слева от первого инта
  И так далее
*/
struct s{
  int a
};
int main() {

  double f = __FLT_MAX__ + 40000;
  float s = f;
  int exp;
  float man = frexpf(f, &exp);
  printf("%d %f %f\n", exp, man,s );


  // char buffer[64];
  // float v = 14123.0f;
  // sprintf(buffer, "%f", v);

  // int exponent;
  // float mantissa = frexpf(v,&exponent);
  // float tr = powf(2, exponent--);
  // ufloat uf = { .f = mantissa};
  // for(int i = 22; i >= 0; i--){
  //   int bit = uf.parts.mantissa >> i & 0x01;
  //   if(bit) tr += powf(2, i - 22 + exponent);
  //   printf("%d", uf.parts.mantissa >> i & 1);
  // }
  // printf("\nEXPONENT: %d\nORIGIN: %f\nTR:  %f\nSTRING: %s\n",exponent, v, tr/2, buffer);
  
  // sprintf(buffer, "%f", v);
  // for(;*(buffer + strlen(buffer) - 1) == '0'; *(buffer + strlen(buffer) - 1) = '\0');
  // printf("%s %f\n%d\n", buffer, v, strlen(strchr(buffer, '.') + 1));
}

/**
  Условия для вызова в s21_add s21_sub:
    1. |value_1| > value_2 && value_1 < 0 && value_2 > 0
    2. |value_2| > value_1 && value_2 < 0 && value_1 > 0
  что не реализовано:
    1. работа со scale
    2. обработка ошибок
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // buffer - для "запоминания" того, что к следующему биту перешла 1
  int return_value = OK, buffer = 0, sum, sub_completed = 0;
  if (search_bigger(value_1, value_2) && get_sign(value_2) &&
      !get_sign(value_1)) {
    s21_decimal temp_value_1 = value_1;
    value_1 = value_2;
    value_2 = temp_value_1;
  }
  if (search_bigger(value_2, value_1) && get_sign(value_1) &&
      !get_sign(value_2)) {
    s21_decimal *copy_value_1 = &value_1;
    set_sign(&copy_value_1, 0);
    value_1 = *copy_value_1;
    s21_decimal copy_result = *result;
    s21_sub(value_2, value_1, &copy_result);
    *result = copy_result;
    sub_completed = 1;
  }
  for (int position = 0; position < 95 && !sub_completed; position++) {
    sum = get_bit(value_1, position) + get_bit(value_2, position) + buffer;
    buffer = 0;
    if (sum == 1) {
      set_bit(&result, position, 1);
    } else if (sum == 2) {
      buffer = 1;
    } else if (sum == 3) {
      buffer = 1;
      set_bit(&result, position, 1);
    }
  }
  return return_value;
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
// пока работает только в случае, если value_1 > value_2
/*

не реализовано:
  1. работа со scale
  2. обработка ошибок
*/

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_value = OK, sub;
  if (search_bigger(value_1, value_2)) {
    s21_decimal temp = value_1;
    value_1 = value_2;
    value_2 = temp;
    set_sign(&result, 1);
  }
  s21_decimal *copy_value_1 = &value_1;
  for (int position = 0; position < 95; position++) {
    sub = get_bit(value_1, position) - get_bit(value_2, position);
    if (sub == 1) {
      set_bit(&result, position, 1);
    } else if (sub == -1) {
      // older_one - переменная, которая хранит в себе позицию следующего
      // единичного бита
      int older_one = search_bit(value_1, position);
      set_bit(&copy_value_1, older_one--, 0);
      while (older_one != position) {
        set_bit(&copy_value_1, older_one--, 1);
      }
      set_bit(&result, position, 1);
      value_1 = *copy_value_1;
    }
  }
  return return_value;
}

