#ifndef S21_DECIMAL
#define S21_DECIMAL

#define TRUE 1
#define FALSE 0

#define OK 0
#define CONVERTATION_ERROR 1

#define INF 1
#define ZERO 2
#define NAN 3

#define CALCULAITON_ERROR 1

#include <stdio.h>
#include <stdlib.h>

#include "s21_strdec.h"

typedef struct 
{
    int bits[4];
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int get_sign_decimal(const s21_decimal *value);

void s21_print_decimal(s21_decimal value);


int s21_get_scale_decimal(const s21_decimal value);
int s21_get_sign_decimal(s21_decimal value);
void s21_set_scale_decimal(s21_decimal *value, int mantissa);
void s21_set_sign_decimal(s21_decimal *value, int sign);
int s21_is_event_decimal(s21_decimal value);
int s21_getb_decimal(s21_decimal value, int bit);
s21_decimal s21_setb_decimal(s21_decimal *value, int val,int bit);


void s21_normalize_decimal(s21_decimal lh, s21_decimal rh, s21_decimal *lh_n, s21_decimal *rh_n);
void s21_mult_handle(s21_decimal lh, s21_decimal rh);
s21_decimal s21_add_handle(s21_decimal lh, s21_decimal rh);
s21_decimal s21_sub_handle(s21_decimal lh, s21_decimal rh);

size_t s21_getfb_decimal(s21_decimal dec);
void s21_shift_decimal(s21_decimal *dec, int len);

#endif