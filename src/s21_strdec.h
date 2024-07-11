#ifndef S21_STRDEC
#define S21_STRDEC

#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 128

void s21_shift_strdec(char *dh, int l, char s);
void s21_add_strdec(const char *lh, const char *rh, char *result);
void s21_pow_strdec(const char *hh, int p, char *result);
void s21_mult_strdec(const char *lh, const char *rh, char *result);
void s21_sub_strdec(const char *lh, const char *rh, char *result);

#endif