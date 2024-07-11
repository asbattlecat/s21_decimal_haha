#include "s21_strdec.h"

void s21_shift_strdec(char *dh, int l, char s){
    if(l == 0) return;

    int dh_s = (int)strlen(dh) - 1;

    if(l > 0){
        for(int i = dh_s; i >= 0; i--){
            dh[i + l] = dh[i];
        }
        for(int i = 0; i < l; i++){
            dh[i] = s;
        }
    }else{
        l = -l;
        for(int i = 0; i < dh_s; i++){
            dh[i] = dh[i + l];
        }
        dh[dh_s - l + 1] = '\0';
    }
}
void s21_add_strdec(const char *lh, const char *rh, char *result){
    size_t lh_s = strlen(lh);
    size_t rh_s = strlen(rh);

    char lh_c[BUFFER_SIZE] = "\0";
    char rh_c[BUFFER_SIZE] = "\0";
    char buffer[BUFFER_SIZE] = "\0";

    strcpy(lh_c, lh);
    strcpy(rh_c, rh);


    if(lh_s > rh_s) s21_shift_strdec(rh_c, lh_s - rh_s, '0');
    else s21_shift_strdec(lh_c, rh_s - lh_s, '0');


    char extra = '0';

    for(int i = strlen(lh_c) - 1; i >= 0; i--){
        char d = lh_c[i] + rh_c[i] - '0';
        d += extra - '0';
        extra = '0';
        if(d > '9'){
            extra = '1';
            d = d - ('9' - '0' + 1);
        }
        buffer[i] = d;
    }
    if(extra == '1'){
        s21_shift_strdec(buffer, 1, extra);
    }
    memset(result, 0, BUFFER_SIZE);
    strcpy(result, buffer);

    #ifdef LOG
    printf("\033[31mADD\033[0m\n");
    printf(" INPUT: %s %s\n", lh_c, rh_c);
    printf("OUTPUT: %s\n\n", result);
    #endif
}
void s21_pow_strdec(const char *rh, int p, char *result){
    if(p == 0){
        strcpy(result, "1\0");
    }else{
        strcpy(result, rh);

        for(int i = 1; i < p; i++){
            s21_mult_strdec(rh, result, result);
        }
    }
    #ifdef LOG
    printf("\033[31mPOW\033[0m\n");
    printf(" INPUT: %s %d\n", rh, p);
    printf("OUTPUT: %s\n\n", result);
    #endif
}
void s21_mult_strdec(const char *lh, const char *rh, char *result){
    size_t lh_s = strlen(lh);
    size_t rh_s = strlen(rh);

    char lh_c[BUFFER_SIZE] = "\0";
    char rh_c[BUFFER_SIZE] = "\0";
    char buffer[BUFFER_SIZE] = "\0";

    strcpy(lh_c, lh);
    strcpy(rh_c, rh);

    while(strcmp(rh_c ,"0")){
        s21_add_strdec(lh_c, buffer, buffer);
        s21_sub_strdec(rh_c, "1", rh_c);
    }

    memset(result, 0, BUFFER_SIZE);
    strcpy(result, buffer);
    #ifdef LOG
    printf("\033[31mMULT\033[0m\n");
    printf(" INPUT: %s %s\n", lh_c, rh);
    printf("OUTPUT: %s\n\n", result);
    #endif
}
void s21_sub_strdec(const char *lh, const char *rh, char *result){
    size_t lh_s = strlen(lh);
    size_t rh_s = strlen(rh);

    char lh_c[BUFFER_SIZE] = "\0";
    char rh_c[BUFFER_SIZE] = "\0";
    char buffer[BUFFER_SIZE] = "\0";

    strcpy(lh_c, lh);
    strcpy(rh_c, rh);

    if(lh_s > rh_s) s21_shift_strdec(rh_c, lh_s - rh_s, '0');
    else s21_shift_strdec(lh_c, rh_s - lh_s, '0');

    char extra = '0';

    for(int i = strlen(lh_c) - 1; i >= 0; i--){
        char d = lh_c[i] - rh_c[i] + '0';
        d = d - extra + '0';
        extra = '0';
        if(d < '0'){
            extra = '1';
            d = d + ('9' - '0' + 1);
        }
        buffer[i] = d;
    }

    if (strcmp(buffer, "0")) s21_shift_strdec(buffer, -1 * strcspn(buffer, "123456789"), 0);

    memset(result, 0, BUFFER_SIZE);
    strcpy(result, buffer);
}
