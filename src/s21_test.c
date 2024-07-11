#include "s21_decimal.h"
#include <stdio.h>
#include <unistd.h>

void clear_screen(){printf("\e[1;1H\e[2J");}

void s21_shift_test(){
    s21_decimal dec = {123123,1,1,0};

    for(int i = 0; i < 96; i++){
        printf("##SHIFT %d\n", i);
        s21_print_decimal(dec);
        s21_shift_decimal(&dec, -1);
        usleep(1000 * 200);
        clear_screen();
    }
}

int main(void){
    // s21_shift_test();
    s21_decimal l ={2,2,2, 0};
    s21_decimal r = {1,1,1, 0};
    s21_decimal m = s21_sub_handle(l,r);
    s21_print_decimal(l);
    s21_print_decimal(r);
    s21_print_decimal(m);
}