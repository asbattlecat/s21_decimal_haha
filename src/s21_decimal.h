#define MINUS 0x80000000 //sing of minus 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000 // thats scaaale 00000000 11111111 00000000 00000000
#define MAX4BITE 0xffffffff // 4 bits are full 11111111 11111111 11111111 11111111


//наш классический децимал
typedef struct {
    int bits[4];
}s21_decimal;

//децимал для вычислений, жирненький слегка
typedef struct {
    long int bits[7]; // будем использоваться бит x2 
    short int scale; // для scale достаточно маленького инта
} work_decimal;

//мне подсказал Бимба, когда курили у горячего Цеха что можно сделать бигдецимал
//из двух обычных - и я решил что это просто отличная идея.
typedef struct {
    s21_decimal decimal[2];
} big_decimal;