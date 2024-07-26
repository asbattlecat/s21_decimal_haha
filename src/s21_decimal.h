#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MINUS 0x80000000      // minus 10000000 00000000 00000000 00000000
#define SC 0x00ff0000         // scale 00000000 11111111 00000000 00000000
#define FULLBITES 0xffffffff  // full 11111111 11111111 11111111 11111111
#define FIRST 0xFFFF          // checking 00000000 00000000 11111111 11111111
#define SECOND 0x7F000000     // checking 01111111 00000000 00000000 00000000
#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

typedef struct {
  int bits[4];
} s21_decimal;

//децимал для сложения и вычитания
typedef struct {
  long int bits[7];
  short int scale;
} work_decimal;

//децимал для умножения и деления
typedef struct {
  s21_decimal decimals[2];
} big_decimal;

// Arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison
int s21_is_less(s21_decimal dec1, s21_decimal dec2);
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);

// Conversion
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// Others
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Helpers
int getoverflow(work_decimal *src);
int pointleft(work_decimal *src);
int pointright(work_decimal *src);
int normalize(work_decimal *src, const int summ, const int sign);
work_decimal decimal_to_work(s21_decimal src);
s21_decimal work_to_decimal(work_decimal src);
void scale_to_normal(work_decimal *dec1_work, work_decimal *dec2_work);
big_decimal decimal_to_big(s21_decimal value_1);
int s21_decimal_get_not_zero_bit(s21_decimal decimal);
int s21_int128_binary_equal_zero(s21_decimal decimal);
s21_decimal s21_int128_binary_and(s21_decimal decimal1, s21_decimal decimal2);
int s21_decimal_is_set_bit(s21_decimal decimal, int index);
int s21_is_set_bit(int number, int index);
int s21_set_bit(int number, int index);
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index);
big_decimal big_decimal_binary_shift_left(big_decimal decimal, int shift);
s21_decimal s21_int128_binary_xor(s21_decimal decimal1, s21_decimal decimal2);
big_decimal big_decimal_binary_addition(big_decimal decimal1,
                                        big_decimal decimal2);
big_decimal binary_mul(s21_decimal value_1, s21_decimal value_2);
int s21_int128_binary_compare(s21_decimal d1, s21_decimal d2);
int big_decimal_binary_compare(big_decimal d1, big_decimal d2);
s21_decimal s21_int128_binary_not(s21_decimal decimal);
big_decimal big_decimal_binary_subtraction(big_decimal decimal1,
                                           big_decimal decimal2);
s21_decimal s21_int128_binary_shift_right_one(s21_decimal decimal);
big_decimal big_decimal_binary_shift_right(big_decimal decimal, int shift);
big_decimal big_decimal_binary_division(big_decimal decimal1,
                                        big_decimal decimal2,
                                        big_decimal *remainder);
int big_decimal_get_shift_to_decimal(big_decimal value);
int s21_is_correct_decimal(s21_decimal decimal);
int multiplication(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
void s21_decimal_leveling(s21_decimal value_1, s21_decimal value_2,
                          big_decimal *value_1l, big_decimal *value_2l);
s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional);
big_decimal big_decimal_binary_multiplication(big_decimal decimal1,
                                              s21_decimal decimal2);
int s21_div_calc_fractional(big_decimal *res, big_decimal value_2l,
                            big_decimal *remainder);
int s21_div_helper(big_decimal value_2l, big_decimal res, big_decimal remainder,
                   s21_decimal *result);
s21_decimal s21_decimal_get_from_char(char c);
int s21_get_float_exp_from_string(char *str);
s21_decimal s21_float_string_to_decimal(char *str);

#endif  // S21_DECIMAL_H_
