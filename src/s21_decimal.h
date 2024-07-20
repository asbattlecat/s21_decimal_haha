#define MINUS 0x80000000  // sing of minus 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000  // thats scaaale 00000000 11111111 00000000 00000000
#define FULLBITES \
  0xffffffff  // 4 bits are full 11111111 11111111 11111111 11111111

//наш классический децимал
typedef struct {
  int bits[4];
} s21_decimal;

//децимал для вычислений, жирненький слегка
typedef struct {
  long int bits[7];  // будет использоваться бит x2
  short int scale;  // для scale достаточно маленького инта
} work_decimal;

//мне подсказал Бимба, когда курили у горячего Цеха что можно сделать бигдецимал
//из двух обычных - и я решил что это просто отличная идея.
typedef struct {
  s21_decimal decimal[2];
} big_decimal;

int get_overflow(work_decimal *src);
int pointleft(work_decimal *src);
int pointright(work_decimal *src);
int normalize(work_decimal *src, const int summ, const int sign);
work_decimal decimal_to_work(s21_decimal src);
s21_decimal work_to_decimal(work_decimal src);
void scale_to_normal(work_decimal *dec1_work, work_decimal *dec2_work);
int s21_is_equal(s21_decimal src1, s21_decimal src2);
int s21_is_less(s21_decimal src1, s21_decimal src2);
int s21_is_less_or_equal(s21_decimal src1, s21_decimal src2);
int s21_is_greater(s21_decimal src1, s21_decimal src2);
int s21_is_greater_or_equal(s21_decimal src1, s21_decimal src2);
int s21_is_not_equal(s21_decimal src1, s21_decimal src2);
int s21_add(s21_decimal src1, s21_decimal src2, s21_decimal *sum);
int s21_sub(s21_decimal src1, s21_decimal src2, s21_decimal *sub);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
big_decimal decimal_to_big(s21_decimal src1);
int get_not_zero_bit(s21_decimal decimal);
int decimal_equal_zero(s21_decimal decimal);
s21_decimal binary_and(s21_decimal s21_decimal_1, s21_decimal s21_decimal_2);
int is_decimal_set_bit(s21_decimal decimal, int index);
int is_int_set_bit(int number, int index);
int set_bit(int number, int index);
s21_decimal decimal_set_bit(s21_decimal decimal, int index);
s21_decimal binary_shift_left_one(s21_decimal decimal);
big_decimal binary_big_shift_left(big_decimal decimal, int shift);
s21_decimal binary_xor(s21_decimal decimal_1, s21_decimal decimal_2);
big_decimal big_decimal_bin_add(big_decimal decimal_1, big_decimal decimal_2);
big_decimal bin_multi(s21_decimal value_1, s21_decimal value_2);
int decimal_compare(s21_decimal dec1, s21_decimal dec2);
int big_decimal_compare(big_decimal dec1, big_decimal dec2);
s21_decimal decimal_bin_not(s21_decimal dec);
big_decimal big_dec_binar_sub(big_decimal dec_1, big_decimal dec_2);
s21_decimal binary_shift_right_one(s21_decimal dec);
big_decimal binary_big_shift_right(big_decimal dec, int shift);
big_decimal big_decimal_bin_div(big_decimal dec1, big_decimal dec2,
                                big_decimal *ost);
