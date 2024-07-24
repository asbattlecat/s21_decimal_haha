#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_decimal temp_dec = {{0, 0, 0, 0}};
  temp_dec.bits[3] = (src < 0) ? MINUS : 0;  // вычисляем знак числа

  //передаем в decimal наше число, но уже без последнего инта, тк
  //мы уже обработали знак - но значение нужно инвертировать
  //как и ранее в сумме используем метод дополнение до двух
  temp_dec.bits[0] = (src < 0) ? (~src & ~MINUS) + 1 : src & ~MINUS;
  *dst = temp_dec;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  work_decimal dec_work = decimal_to_work(src);
  //проверка на скейл, если он превышает 28 - обрезаем до 28
  //если меньше, ставим тот, что есть.
  int scale =
      (((src.bits[3] & SC) >> 16) > 28) ? 28 : ((src.bits[3] & SC) >> 16);

  //отбрасываем все, что после точки, так как мы хотим получить целое число
  for (int i = 0; i < scale; i++) {
    pointright(&dec_work);
  }
  // проверяем не переполнен ли у нас децимал. должен быть занят
  // только самый младший бит, если больше - мы вылезли
  // за размеры инта, а значит - переполнение.
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
