#include "s21_decimal.h"

int main() {
  s21_decimal value_1, value_2, result;
 // nulling(&value_1, &value_2, &result);
  value_1.bits[0] = 0b00000000000000000000000001011111;
  value_1.bits[1] = 0b10000000000000000000000000001111;
  value_1.bits[2] = 0b00000000000000000000000011111111;
  value_1.bits[3] = 0b11111111111111111111111111111111;
 // set_1_bit(&value_2.bits[3], 0);
  int wow = -213452512;
  int wow2 = 0;
  //s21_from_int_to_decimal(wow, &value_1);
  s21_from_decimal_to_int(value_1, &wow2);
  //set_0_bit(&value_1.bits[3], 30);
  //print_binary(value_1.bits[3]);
  int scale =  get_scale(value_1);
 // printf("%d", scale);
  //printf("%d\n", wow2);
  //print_bits(&value_1);
  int currently = find_bit(value_1, 95);
  printf("%d", currently);
}

void set_1_bit(unsigned int *src, unsigned int index) {
   *src |= (1u << index);
}

void set_0_bit(unsigned int *src, unsigned int index) {
  *src &= ~(1u << index); 
}

void print_binary(int num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
}

void print_bits(s21_decimal *val) {
  for (int i = 3; i >= 0; i--) {
    print_binary(val->bits[i]);
    printf(" ");
  }
  printf("\n");
}

int get_bit(unsigned int src, unsigned int index) {
  return (src >> index) & 1; 
}
int get_sign(s21_decimal src) {
  if (get_bit(src.bits[3], 31)) {
    return 1;  
  }
  return 0;  
}

int get_scale(s21_decimal dst) {
  int mask = 127 << 16; // 01111                  
  int scale = (mask & dst.bits[3]) >> 16; 
  return scale;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  *dst = (s21_decimal){0};  
  if (src < 0) {
    set_1_bit(&dst->bits[3], 31);  
    src = -src;   
  }
  dst->bits[0] = src; 
  return 0; 
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int ret = 1;           
  if (*dst == 0) {      
    *dst = src.bits[0]; 
    *dst = *dst * (get_bit(src.bits[3], 31) ? -1 : 1);
    ret = 0;                
  }
  return ret; 
}

int find_bit(s21_decimal dst, int index) {
    int mask = 1u << (index % 32);
    return (dst.bits[index/32] & mask) != 0;
}

s21_big_decimal norm_to_big(s21_decimal src) {
  s21_big_decimal res = {0};
  unsigned int exp = get_exp(src);
  for (int i = 0; i < 3; i++)
    res.bits[i] = src.bits[i];
    res.exp = exp;                          
  return res;
}

int get_exp(s21_decimal src) {
  return (src.bits[3] & EXP) >> 16; 
}