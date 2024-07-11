#include "s21_decimal.h"
#include <unistd.h>

int s21_get_scale_decimal(const s21_decimal value){
    return (value.bits[3] >> 16) & (0xFF);
}
int s21_get_sign_decimal(s21_decimal value){
    return ((value.bits[3] >> 31) & 0x01) ? 1 : -1;
}
// void s21_set_scale_decimal(s21_decimal *value, int mantissa){
//     if(mantissa < 0 || mantissa > 28) return;
    
//     value->bits[3] = (value->bits[3] & 0xFF00FFFF) | (mantissa << 16);
// }
void s21_set_sign_decimal(s21_decimal *value, int sign){
    if(sign >= 0){
        value->bits[3] |= 0x80000000;
    }else{
        value->bits[3] &= 0x7FFFFFFF;
    }
}
int s21_is_even_decimal(s21_decimal value){
    return ((value.bits[0] & 0x01) == 0x01 ? 0 : 1);
}
int s21_is_less(s21_decimal lh, s21_decimal rh){
    int rval = FALSE;
    if(s21_get_sign_decimal(lh) > s21_get_sign_decimal(rh)) rval = FALSE;
    else if(s21_get_sign_decimal(lh) < s21_get_sign_decimal(rh)) rval = TRUE;
    else{
        s21_decimal lh_n = {0};
        s21_decimal rh_n = {0};

        s21_normalize_decimal(lh,rh, &lh_n, &rh_n);

        for(int i = 2; i >= 0; i--){
            if(lh.bits[i] != rh.bits[i]){
                rval = lh.bits[i] > rh.bits[i] ? FALSE : TRUE;
                break;
            }
        }
    }

    return rval;
}

int s21_is_less_or_equal(s21_decimal lh, s21_decimal rh){
    return s21_is_less(lh, rh) || s21_is_equal(lh,rh);
}


int s21_is_equal(s21_decimal lh, s21_decimal rh){
    return (s21_get_scale_decimal(lh) == s21_get_scale_decimal(rh) && 
            s21_get_sign_decimal(lh) == s21_get_sign_decimal(rh) && 
            rh.bits[0] == lh.bits[0] && 
            rh.bits[1] == lh.bits[1] && 
            rh.bits[2] == lh.bits[2]);
}
int s21_is_not_equal(s21_decimal lh, s21_decimal rh){
    return !s21_is_equal(lh,rh);
}

int s21_is_greater(s21_decimal lh, s21_decimal rh){
    return s21_is_less(rh,lh);
}
int s21_is_greater_or_equal(s21_decimal lh, s21_decimal rh){
    return s21_is_greater_or_equal(lh, rh) || s21_is_greater_or_equal(lh,rh);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){


    return 1;
}

void s21_print_decimal(s21_decimal value){
    int prop_width = 7;

    printf("\033[36m[%*s]\33[0m: %d\n", prop_width,"Scale",s21_get_scale_decimal(value));
    printf("\033[36m[%*s]\33[0m: %s\n", prop_width,"Sign", s21_get_sign_decimal(value) > 0 ? "POSITIVE" : "NEGATIVE");

    for(int bit = 95; bit >= 0; bit--){
        printf("%d", s21_getb_decimal(value, bit));
        if(bit % 32 == 0) printf(" ");

    }
    printf("\n");

    char res[BUFFER_SIZE] = "0\0";
    char buff[BUFFER_SIZE] = "0\0";

    
}
int s21_getb_decimal(s21_decimal value, int bit){
    return value.bits[bit / 32] >> (bit % 32) & 0x01;
}
s21_decimal s21_setb_decimal(s21_decimal *value, int val,int bit){
    value->bits[bit / 32] = val == 0 ? value->bits[bit / 32] &  ~(0x01 << (bit % 32)) : value->bits[bit / 32] | 0x01 << (bit % 32);
    return *value;
}

void s21_normalize_decimal(s21_decimal lh, s21_decimal rh, s21_decimal *lh_n, s21_decimal *rh_n){
    if(s21_get_scale_decimal(lh) == s21_get_scale_decimal(rh)){
        *lh_n = lh;
        *rh_n = rh;
    }else{
        if(s21_get_scale_decimal(lh) > s21_get_scale_decimal(rh)){
            
        }
    }
}
void s21_normalize_handle(s21_decimal *dh, int scale){

}

s21_decimal s21_add_handle(s21_decimal lh, s21_decimal rh){
    s21_decimal sum = {0};
    int extra_bit = 0, sum_bit = 0;

    for(int bit = 0; bit < 96; bit++){
        sum_bit = s21_getb_decimal(lh, bit) + s21_getb_decimal(rh, bit) + extra_bit;
        extra_bit = sum_bit > 1 ? 1 : 0;
        s21_setb_decimal(&sum, sum_bit % 2, bit);
    }

    return sum;
}

s21_decimal s21_sub_handle(s21_decimal lh, s21_decimal rh){
    s21_decimal sum = {0};
    int borrowed_bit = 0, sum_bit = 0;

    for(int bit = 0; bit < 96; bit++){
        sum_bit = s21_getb_decimal(lh,bit) - s21_getb_decimal(rh,bit) - borrowed_bit;
        borrowed_bit = sum_bit < 0 ? 1 : 0;
        s21_setb_decimal(&sum, abs(sum_bit), bit);
    }
    return sum;
}

void s21_set_scale_decimal(s21_decimal *dec, int scale){
    if(s21_get_scale_decimal(*dec) < scale){
        s21_decimal lh = *dec;
        s21_decimal rh = *dec;

        s21_shift_decimal(&lh, 1);
        s21_shift_decimal(&rh, 3);

        *dec = s21_add_handle(lh, rh);
    }

}

void s21_mult_handle(s21_decimal lh, s21_decimal rh){
    
}   

size_t s21_getfb_decimal(s21_decimal dec){
    size_t fb = 95;
    for(;fb > 0 && s21_getb_decimal(dec, fb) == 0;fb--);
    return fb;
}
void s21_shift_decimal(s21_decimal *dec, int l){
    if(l > 0){
        for(int k = 95; k >= l; k--){
            s21_setb_decimal(dec, s21_getb_decimal(*dec, k - l), k);
        }
        for(int k = 0; k < l; k++){
            s21_setb_decimal(dec, 0, k);
        }
    }else if(l < 0){
        l = -l;
        int fb = s21_getb_decimal(*dec, 95);
        for(int k = 0; k < 96 - l;k++){
            s21_setb_decimal(dec, s21_getb_decimal(*dec, k + l), k);
        }
        for(int k = 95; k >= 96 - l; k--){
            s21_setb_decimal(dec, fb, k);
        }
    }
}
