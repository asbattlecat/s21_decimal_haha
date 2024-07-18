#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>


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
//Совершаем преобразование обоих децималов в один scale
//для удобства вычислений. 
// 
//после проверки входим в цикл и увеличиваем масштаб децимала пока он не станет
//равен масштабу второго децимала, или не произойдет переполнение.

void scale_to_normal(work_decimal *dec1_work, work_decimal *dec2_work) {
  if (dec1_work->scale < dec2_work->scale) {
    //умножаем на 10 первый, если он меньше второго
    while(dec1_work->scale != dec2_work->scale && !pointleft(dec1_work));
  } else if (dec2_work->scale < dec1_work->scale) {
    //умножаем на 10 второй, если он меньше первого
    while(dec1_work->scale != dec2_work->scale && !pointleft(dec2_work));
  }
}


int s21_is_equal(s21_decimal src1, s21_decimal src2) {
  int result = 1;

  // если все биты равны нулю, но знак разный, то 
  // -0 == +0 
  if ((src1.bits[3] & MINUS) != (src2.bits[3] & MINUS) &&
  ((src1.bits[0] == src2.bits[0]) && (src1.bits[1] == src2.bits[1]) &&
  (src1.bits[2] == src2.bits[2]) && (src1.bits[0] == 0) &&
  (src1.bits[1] == 0) && (src1.bits[2] == 0))) {
  result = 1;
  //Если знак разный, тогда не равны
  } else if ((src1.bits[3] & MINUS) != (src2.bits[3] & MINUS)) {
    result = 0;
  } else {
    // если два прошлых условия false 
    // приводим децималы к общему масштабу и сравниваем
    work_decimal src1_work, src2_work;
    //работаем с длинными децималами, чтобы удобно домножить на 10 и сравить
    src1_work = decimal_to_work(src1);
    src2_work = decimal_to_work(src2);


  // умножаем один из длинных децималов, если есть необходимость
    scale_to_normal(&src1_work, &src2_work);
    for (int i = 2; i >= 0; i--) {
      // если различий в трех малых интах нет, значит децималы равны
      if (src1_work.bits[i] != src2_work.bits[i]) {
        result = 0;
      }
    }
  }
  return result;
}

int s21_is_less(s21_decimal src1, s21_decimal src2) {
  int result = 1;
  // децималы равны или второй со знаком минус, а первый нет
  //возвращаем - 0, src1 не меньше src2
  if ((src1.bits[3] & MINUS) < (src2.bits[3] & MINUS) || 
  s21_is_equal(src1, src2)) {
    result = 0;
  } else if 
    //извлекаю знак и проверяю, если перввый отрицательный, а 
    //второй децимал нет - то , sr1 меньше sr2, возвращаю 1;
    ((src1.bits[3] & MINUS) > (src2.bits[3] & MINUS)) {
      result = 1;
    } else {
    work_decimal src1_work, src2_work;
    src1_work = decimal_to_work(src1);
    src2_work = decimal_to_work(src2);
    scale_to_normal(&src1_work, &src2_work); //приводим к общему scale
    for (int i = 2; i >= 0; i--) {
      //если старшие биты первого децимала меньше то,
      //значит что весь первый децимал меньше второго
      if(src1_work.bits[i] < src2_work.bits[i]) {
      result = 1;
      i = -1; // заканчиваем цикл
    } else if (src1_work.bits[i] > src2_work.bits[i]) {
      result = 0;
      i = -1;
    }
  }

  // если оба числа отрицательные - тогда инвертирем результат
  if (src1.bits[3] & MINUS) {
    if (result == 0) result = 1;
    else if (result == 1) result = 0;
  }
}
  return result;
}


//следующие функции просто комбинации из тех, что выше

int s21_is_less_or_equal(s21_decimal src1, s21_decimal src2) {
  int result = 0;
  if (s21_is_equal(src1, src2) || s21_is_less(src1, src2)) {
    result = 1;
  }
  return result;
}

int s21_is_greater(s21_decimal src1, s21_decimal src2) {
  int result = 1;
  if (s21_is_less_or_equal(src1, src2)) {
    result = 0;
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal src1, s21_decimal src2) {
  int result = 1;
  if (s21_is_less(src1, src2)) {
    result = 0;
  }
  return result;
}

int s21_is_not_equal(s21_decimal src1, s21_decimal src2) {
  int result = 1;
  if (s21_is_equal(src1, src2)) {
    result = 0;
  }
  return result;
}

int s21_add(s21_decimal src1, s21_decimal src2, s21_decimal *sum) {
  int result = 0;
  // первым шагом переводим в расширенный децимал
  work_decimal src1_work = decimal_to_work(src1),
               src2_work = decimal_to_work(src2);
  work_decimal temp_sum = {{0, 0, 0, 0, 0, 0, 0}, 0};
  scale_to_normal(&src1_work, &src2_work); // выравниваем оба децимал по scale
  // если числа одинаковые по знакам
  if ((src1.bits[3] & MINUS) == (src2.bits[3] & MINUS)) {
    // просто складываем каждый int и переводим лишние
    // биты в более старшие, если нужно.
    for (int i = 0; i < 6; i++) {
      temp_sum.bits[i] += src1_work.bits[i] + src2_work.bits[i];
      get_overflow(&temp_sum);
    }
    // в результат суммы передаем scale
  temp_sum.scale = src1_work.scale;


  //нормализация для последующей концертации в обычный децимал
  // если вдруг есть переполнение, то по знаку определяем
  // в какую сторону
  if (normalize(&temp_sum, 1, src1.bits[3] & MINUS)) {
    if(src1.bits[3] & MINUS) {
      result = 2;
    } else {
      result = 1;
    }
  } else {
    //складываем все в наш обычный децимал
    *sum = work_to_decimal(temp_sum);
    if (src1.bits[3] & MINUS) {
      sum->bits[3] |= MINUS;
    }
    sum->bits[3] |= (temp_sum.scale << 16) & SCALE;
  }
  } else { // если вдруг числа разные по знакам
  // заранее запоминаем какой знак у децимала + или -
    int first_min = (src1.bits[3] & MINUS);
    int second_min = (src2.bits[3] & MINUS);
    // делаем оба децимала положительными
    src1.bits[3] &= ~MINUS;
    src2.bits[3] &= ~MINUS;
    for (int i = 0; i < 6; i++) {
      // вычитаем из большего децимала меньший
      if (s21_is_less(src1, src2)) {
        // вычитаем с помощью метода дополнения до двух
        temp_sum.bits[i] += src2_work.bits[i] + (~src1_work.bits[i] + 1);
      } else {
        temp_sum.bits[i] += src1_work.bits[i] + (~src2_work.bits[i] + 1);
      }
      get_overflow(&temp_sum);
    }
    // передаем scale в итоговый результат суммы
    temp_sum.scale = src1_work.scale;
    int sign_result = 0x00000000;
    // определяем какой в итоге будет знак у резуьтата 
    if ((s21_is_less(src1, src2) && second_min) || 
    (s21_is_greater(src1, src2) && first_min)) {
      sign_result |= MINUS;
    }
    normalize(&temp_sum, 0, sign_result);
    *sum = work_to_decimal(temp_sum); //передаем сумму в результат.
    sum->bits[3] |= sign_result;
    sum->bits[3] |= (temp_sum.scale << 16) & SCALE;
}
  return result;
}

// меняем знакм второго децимала и складываем с помощью функции s21_add
int s21_sub(s21_decimal src1, s21_decimal src2, s21_decimal *sub) {
  src2.bits[3] = (src1.bits[3] & MINUS) ? src1.bits[3] & ~MINUS :
  src2.bits[3] | MINUS;
  return s21_add(src1, src2, sub);
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_decimal temp_dec = {{0, 0, 0, 0}};
  temp_dec.bits[3] = (src < 0) ? MINUS : 0;  // вычисляем знак src

  // просто передаем src нашему int, но уже без
  // последнего бита, так как мы его отдельно записали
  // в наш 4 int, если же src отрицательное число, то
  // нам нужно его инвертировать (что поделать, так
  // устроен signed int)
  temp_dec.bits[0] = (src < 0) ? (~src & ~MINUS) + 1 : src & ~MINUS;
  *dst = temp_dec;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  work_decimal dec_work = decimal_to_work(src);
  int scale =
      (((src.bits[3] & SCALE) >> 16) > 28) ? 28 : ((src.bits[3] & SCALE) >> 16);

  // отбрасываем все цифры после точки, всю
  // вещественную часть децимал
  for (int i = 0; i < scale; i++) {
    pointright(&dec_work);
  }

  // проверяем не переполнен ли у нас децимал. должен быть занят
  // только самый низший int, чтобы небыло переполнения
  for (int i = 6; i > 0; i--) {
    if (dec_work.bits[i] != 0) {
      res = 1;
      i = 0;
    }
  }
  if (!res) {
    // передаем из нашено int в dst int
    *dst = dec_work.bits[0];

    // умножаем dst на -1 если децимал отрицательный
    *dst *= (src.bits[3] & MINUS) ? -1 : 1;
  }
  return res;
}