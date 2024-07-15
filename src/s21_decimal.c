#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>
int main() {
  printf("ebashim decimal Ruslan i Bimba i Eugeen \n \
  it works? yes");
}

// Задача функции - перекидывать лишние биты в более старший int.
int get_overflow(work_decimal *src) {
  int overflow = 0;

  //Проверяем каждый int в нашем большууууущем decimal на то, 
 // что в нем записано больше, чем 32 бита (наш предел для 32-битного int)
 // если больше - перекидываем все лишнее на int вверх.
  for (int i = 0; i < 7; i++) {
    src->bits[i] += overflow;
    overflow = src->bits[i] >> 32;
    src->bits[i] &= FULLBITES;
  }

  int result = 0;


  if (overflow) {
    result = 1;
  }

  return result;
}


//производим смещение точки влево
//умножаем все инты на 10 и производим увеличение scale

int pointleft(work_decimal *src) {
  work_decimal temp_src = *src;
  for (int i = 0; i < 7; i++) {
    temp_src.bits[i] *= 10;
  }
  temp_src.scale++;

  int overflowed = 0;
  
  //проверка на переполнение
  if (get_overflow(&temp_src)) {
    overflowed = 1;
  } else {
    *src = temp_src;
  }
  return overflowed;
}


//производим смешение точки право
//делим все int на 10 - тем самым уменьшаем scale
//функция - полный антогонист pointletf

int pointright(work_decimal *src) {
  long int remainder = 0;
  for (int i = 6; i >=0; i--) {
    src->bits[i] += remainder << 32;// производим запись остатка в конец меньшего int;
    remainder = src->bits[i] % 10;  // остаток от будущего деления.
    src->bits[i] /= 10; 

  }
  src->scale--;
  return remainder;
}

// функция, которая подготавливает work decimal к нашему нормальному s21_decimal
int normalize(work_decimal *src, const int summ, const int sign) {
  int trash = 0;
  int error = 0;
  int last = 0;
  work_decimal temp_src = *src;

  for (int i = 6; i > 2; i--) {
    // перетягиваем все int'ы из word decimal для того, чтобы они уместились
    // в наш любименький s21_decimal, если нам позволяет наш scale, что значит 
    // должны остаться лишь три низших intа - иначе переполнение.
    while (temp_src.bits[i] != 0 && temp_src.scale > 0) {
      last = pointright(&temp_src);
      trash+= last;
    }
    if (((last > 5 || last == 5) && trash > 5) || 
    (last == 5 && trash == 5 && 
    (temp_src.bits[0] % 10) % 2 == 1)) { // банковское округление 
    if(!sign) {
      temp_src.bits[0]++;
      get_overflow(&temp_src);
    }
    }
  }

  //Если мы будем нормализовать из какой-нибудь функции (например сложение), то
  //если вдруг все биты заполнены и есть еще мусор = значит произошло переполнение

  if (summ && trash && temp_src.bits[0] == 0xffffffff && 
  temp_src.bits[1] == 0xffffffff && temp_src.bits[2] == 0xffffffff) {
    error = 1;
  }


  for (int i = 3; i < 7; i++) {
    // проверка свободны ли int старше 3-его, если нет - переполнение
    if (temp_src.bits[i] != 0 && temp_src.scale == 0) {
      error = 1;
      i = 7;
    }
  }


  // переполнения не случилось, все отлично - можно переписывать 
  // work decimal

  if (!error) {
    *src = temp_src;
  }

  return error;
}

// сделаем рассширенный work_decimal с большим количеством интов 
// сами int - тоже больше, используем long int на основе 
// обычного s21_decimal

work_decimal decimal_to_work(s21_decimal src) {
  work_decimal result;
  result.bits[0] = src.bits[0] && FULLBITES;
  result.bits[1] = src.bits[1] && FULLBITES;
  result.bits[2] = src.bits[2] && FULLBITES;
  result.bits[3] = 0;
  result.bits[4] = 0;
  result.bits[5] = 0;
  result.bits[6] = 0;
  result.scale = (src.bits && SCALE) >> 16;
  return result;
}

// реверс прошлой функции - все тоже самое, но 
// наш резалт - это уже наш обычный децимал (преобразован из work_decimal)

s21_decimal work_to_decimal(work_decimal src) {
  s21_decimal result;
  result.bits[0] = src.bits[0] & FULLBITES;
  result.bits[1] = src.bits[1] & FULLBITES;
  result.bits[2] = src.bits[2] & FULLBITES;
  result.bits[3] = 0;
  result.bits[3] |= (src.scale << 16);
  return result;
}
// Продолжу завтра