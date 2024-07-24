#include "s21_decimal.h"
int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 1;

  // если все биты равны нулю, но знак разный, то
  // -0 == +0
  if ((dec1.bits[3] & MINUS) != (dec2.bits[3] & MINUS) &&
      ((dec1.bits[0] == dec2.bits[0]) && (dec1.bits[1] == dec2.bits[1]) &&
       (dec1.bits[2] == dec2.bits[2]) && (dec1.bits[0] == 0) &&
       (dec1.bits[1] == 0) && (dec1.bits[2] == 0))) {
    res = 1;

    //Если знак разный, тогда не равны
  } else if ((dec1.bits[3] & MINUS) != (dec2.bits[3] & MINUS)) {
    res = 0;

  } else {
    // если два прошлых условия false
    // приводим децималы к общему масштабу и сравниваем
    work_decimal dec1_work, dec2_work;

    //работаем с длинными децималами, чтобы удобно домножить на 10 и сравить
    dec1_work = decimal_to_work(dec1);
    dec2_work = decimal_to_work(dec2);

    // умножаем один из длинных децималов, если есть необходимость
    scale_to_normal(&dec1_work, &dec2_work);
    for (int i = 2; i >= 0; i--) {
      // если различий в трех малых интах нет, значит децималы равны
      if (dec1_work.bits[i] != dec2_work.bits[i]) {
        res = 0;
      }
    }
  }
  return res;
}

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  int res = 1;
  // децималы равны или второй со знаком минус, а первый нет
  //возвращаем - 0, src1 не меньше src2т
  if ((dec1.bits[3] & MINUS) < (dec2.bits[3] & MINUS) ||
      s21_is_equal(dec1, dec2)) {
    res = 0;
    //извлекаю знак и проверяю, если перввый отрицательный, а
    //второй децимал нет - то , sr1 меньше sr2, возвращаю 1;
  } else if ((dec1.bits[3] & MINUS) > (dec2.bits[3] & MINUS)) {
    res = 1;
  } else {
    work_decimal dec1_work, dec2_work;
    dec1_work = decimal_to_work(dec1);
    dec2_work = decimal_to_work(dec2);
    scale_to_normal(&dec1_work, &dec2_work);  //приводим к общему scale
    for (int i = 2; i >= 0; i--) {
      //если старшие биты первого децимала меньше то,
      //значит что весь первый децимал меньше второго
      if (dec1_work.bits[i] < dec2_work.bits[i]) {
        res = 1;
        i = -1;  // заканчиваем цикл
      } else if (dec1_work.bits[i] > dec2_work.bits[i]) {  //наоборт
        res = 0;
        i = -1;
      }
    }

    // если оба числа отрицательные - тогда инвертирем результат
    if (dec1.bits[3] & MINUS) {
      res ? (res = 0) : (res = 1);
    }
  }
  return res;
}

//следующие функции просто комбинации из тех, что выше
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  if (s21_is_equal(dec1, dec2) || s21_is_less(dec1, dec2)) {
    res = 1;
  }
  return res;
}

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int res = 1;
  if (s21_is_less_or_equal(dec1, dec2)) {
    res = 0;
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 1;
  if (s21_is_less(dec1, dec2)) {
    res = 0;
  }
  return res;
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 1;
  if (s21_is_equal(dec1, dec2)) {
    res = 0;
  }
  return res;
}
