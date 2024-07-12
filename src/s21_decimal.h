#include <stdio.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef struct {
    unsigned long long bits[7];
    int exp;
} s21_big_decimal;

#define EXP 0x00ff0000 // 00000000 11111111 00000000 00000000

void set_1_bit(unsigned int *src, unsigned int index);
void set_0_bit(unsigned int *src, unsigned int index);
void print_binary(int num);
void print_bits(s21_decimal *val);
int get_sign(s21_decimal src);
int get_scale(s21_decimal dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int find_bit(s21_decimal dst, int index);
s21_big_decimal norm_to_big(s21_decimal src);
int get_exp(s21_decimal src);