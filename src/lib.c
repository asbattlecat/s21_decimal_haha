#include "s21_decimal.h"

// печать в опщимта
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
//

// зануляет все переменные
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

// получает данные о разрядности
int get_scale(s21_decimal value) { return value.bits[3] >> 16 & 0xFF; }

// считывание бита в определенной позиции в s21_decimal
int get_bit(s21_decimal value, int position) {
  return value.bits[position / 32] >> (position % 32) & 0x01;
}

float get_bit_float(float value, int position) {
  float one = 1.0;
  // return value & (one << position);
}

// получает данные о знаке, если 1 - то знак минус
int get_sign(s21_decimal value) { return value.bits[3] >> 31 & 1; }

// помещение бита в определенную позицию в s21_decimal
void set_bit(s21_decimal **value, int position, int bit) {
  if (bit == 1) {
    (*value)->bits[position / 32] |= 0x01 << (position % 32);
  } else if (bit == 0) {
    (*value)->bits[position / 32] &= ~(0x01 << (position % 32));
  }
}

// устанавливает разрядность
void set_scale(s21_decimal *val, int scale) {
  if (scale > 255) scale = scale & 0xFF;
  val->bits[3] &= ~(unsigned int)0xFF << 16;
  val->bits[3] |= scale << 16;
}

// устанавливает знак
void set_sign(s21_decimal **value, int sign) {
  if (sign > 1) sign = 1;
  if (sign) {
    (*value)->bits[3] |= 1 << 31;
  } else if (!sign) {
    (*value)->bits[3] &= ~(1 << 31);
  }
}

// ищет более старший единичный бит относительно рассматриваемого
int search_bit(s21_decimal value, int position) {
  while (get_bit(value, position) != 1) {
    ++position;
  }
  return position;
}

// функция для сравнения чисел, если одно больше другого - переставить местами
//  если функция возвращает 1, то value_2 > value_1
int search_bigger(s21_decimal value_1, s21_decimal value_2) {
  int first_pos = 0, second_pos = 0, first_count = 0, second_count = 0,
      return_value = 0;
  for (int position = 95; position >= 0; position--) {
    if (get_bit(value_1, position) == 1 && !first_pos) first_pos = position;
    if (get_bit(value_2, position) == 1 && !second_pos) second_pos = position;
    if (get_bit(value_1, position) == 1) first_count++;
    if (get_bit(value_2, position) == 1) second_count++;
  }
  if (second_pos > first_pos) {
    return_value = 1;
  } else if (second_pos == first_pos) {
    if (second_count > first_count) return_value = 1;
  }

  return return_value;
}
