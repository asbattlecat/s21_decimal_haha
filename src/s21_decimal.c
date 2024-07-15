#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>
int main() {
  printf("ebashim decimal Ruslan i Bimba i Eugeen \n \
  it works? yes");
}

// Задача функции - перекидывать лишние биты в более старший int.
int get_overflow(work_decimal *dec) {
  int overflow = 0;

  //Проверяем каждый int в нашем большууууущем decimal на то, 
 // что в нем записано больше, чем 32 бита (наш предел для 32-битного int)
 // если больше - перекидываем все лишнее на int вверх.
  for (int i = 0; i < 7; i++) {
    dec->bits[i] += overflow;
    overflow = dec->bits[i] >> 32;
    dec->bits[i] &= MAX4BITE;
  }

  int result = 0;


  if (overflow) {
    result = 1;
  }

  return result;
}


//производим смещение точки влево
//умножаем все инты на 10 и производим увеличение scale

int pointleft(work_decimal *dec) {
  work_decimal temp_dec = *dec;
  for (int i = 0; i < 7; i++) {
    temp_dec.bits[i] *= 10;
  }
  temp_dec.scale++;

  int overflowed = 0;
  
  //проверка на переполнение
  if (get_overflow(&temp_dec)) {
    overflowed = 1;
  } else {
    *dec = temp_dec;
  }
  return overflowed;
}


//производим смешение точки право
//делим все int на 10 - тем самым уменьшаем scale
//функция - полный антогонист pointletf

int pointright(work_decimal *dec) {
  long int remainder = 0;
  for (int i = 6; i >=0; i--) {
    dec->bits[i] += remainder << 32;// производим запись остатка в конец меньшего int;
    remainder = dec->bits[i] % 10;  // остаток от будущего деления.
    dec->bits[i] /= 10; 

  }
  dec->scale--;
  return remainder;
}

// функция, которая подготавливает work decimal к нашему нормальному s21_decimal
int normalize(work_decimal *dec, const int summ, const int sign) {
  int trash = 0;
  int error = 0;
  int last = 0;
  work_decimal temp_dec = *dec;

  for (int i = 6; i > 2; i--) {
    // перетягиваем все int'ы из word decimal для того, чтобы они уместились
    // в наш любименький s21_decimal, если нам позволяет наш scale, что значит 
    // должны остаться лишь три низших intа - иначе переполнение.
    while (temp_dec.bits[i] != 0 && temp_dec.scale > 0) {
      last = pointright(&temp_dec);
      trash+= last;
    }
    if (((last > 5 || last == 5) && trash > 5) || 
    (last == 5 && trash == 5 && 
    (temp_dec.bits[0] % 10) % 2 == 1)) { // банковское округление 
    if(!sign) {
      temp_dec.bits[0]++;
      get_overflow(&temp_dec);
    }
    }
  }

  //Если мы будем нормализовать из какой-нибудь функции (например сложение), то
  //если вдруг все биты заполнены и есть еще мусор = значит произошло переполнение

  if (summ && trash && temp_dec.bits[0] == 0xffffffff && 
  temp_dec.bits[1] == 0xffffffff && temp_dec.bits[2] == 0xffffffff) {
    error = 1;
  }


  for (int i = 3; i < 7; i++) {
    // проверка свободны ли int старше 3-его, если нет - переполнение
    if (temp_dec.bits[i] != 0 && temp_dec.scale == 0) {
      error = 1;
      i = 7;
    }
  }


  // переполнения не случилось, все отлично - можно переписывать 
  // work decimal

  if (!error) {
    *dec = temp_dec;
  }

  return error;
}