#include "s21_decimal.h"

int main() {
    s21_decimal value = {0};
    //set_scale_and_sign (&value, 2, 1);
    //print_binary (value.bits[3]);
    int x = 0b1010;
    printf ("%d\n", x);
    x = x << 3;
    x = x >> 2;
    printf ("%d\n", x);
}

void set_scale_and_sign (s21_decimal *decimal,int scale, int sign) {
    decimal->bits[3] &= ~0x00FF000;
    decimal->bits[3] &= ~(1 << 31);

    decimal->bits[3] |= (scale << 16);
    decimal->bits[3] |= (sign << 31);
}

void get_scale_and_sign (s21_decimal *decimal,int *scale, int *sign) {
    *scale = (decimal->bits[3] >> 16) & 0xFF;
    *sign = (decimal->bits[3] >> 31) & 1;
}

void print_binary (int number) {
    for (int i = 31; i >= 0; i--) {
        int bit = (number >> i) & 1;
        printf ("%d", bit);
        if (i % 4 == 0) printf (" ");
    }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    //int return_value = OK;
}