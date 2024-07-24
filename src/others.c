#include "s21_decimal.h"

// округление но в сторону минус бесконечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  work_decimal dec_work = decimal_to_work(value);

  int trash = 0;
  int scale =
      (((value.bits[3] & SC) >> 16) > 28) ? 28 : ((value.bits[3] & SC) >> 16);

  // убираем всю вещественную часть, но запоминаем последнюю цифру
  // и весь остаток в сумме
  for (int i = 0; i < scale; i++) {
    int last = pointright(&dec_work);
    trash += last;
  }

  // если общий остаток больше нуля и число отрицательное то
  // прибавляем единичку, чтобы сделать наше отрицательное
  // число ближе к минус бесконечности
  if (trash > 0 && value.bits[3] & MINUS) {
    dec_work.bits[0]++;
    getoverflow(&dec_work);
  }
  *result = work_to_decimal(dec_work);
  result->bits[3] = value.bits[3] & MINUS;
  return 0;
}
// просто делаем s21_floor но без знака. Знак потом
// возвращаем. Так получается что мы в любом случае
// просто отбрасываем вещественную часть
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int sign = value.bits[3] & MINUS;
  value.bits[3] &= ~MINUS;
  s21_floor(value, result);
  result->bits[3] |= sign;
  return 0;
}

// инвертируем знаковый бит в децимал
int s21_negate(s21_decimal value, s21_decimal *result) {
  value.bits[3] =
      (value.bits[3] & MINUS) ? value.bits[3] & ~MINUS : value.bits[3] | MINUS;
  *result = value;
  return 0;
}

// для округления используем банковского округление,
// то есть округление в сторону чётных
int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int scale = (value.bits[3] & SC) >> 16;
  if (!result) {
    // Если указатель на decimal является NULL
    error = 1;
  } else if (scale > 28 || scale < 0 || (value.bits[3] & FIRST) ||
             (value.bits[3] & SECOND)) {
    // Проверяем, что value является корректными decimal
    error = 1;
    *result = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  } else {
    // В остальных случаях округляем
    *result = (s21_decimal){{0, 0, 0, 0}};
    int sign = value.bits[3] & MINUS;
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    // Убираем знак

    s21_decimal value_unsigned = value;
    value_unsigned.bits[3] = value.bits[3] & ~MINUS;
    // Убираем дробную часть числа
    s21_truncate(value_unsigned, &value_unsigned_truncated);

    // Считаем убранную дробную часть числа
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);

    // Производим округление, исходя из дробной части числа
    value_unsigned_truncated =
        s21_round_banking(value_unsigned_truncated, fractional);

    *result = value_unsigned_truncated;
    // Возвращаем знак
    result->bits[3] |= sign;
  }

  return error;
}