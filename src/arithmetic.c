#include "s21_decimal.h"
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  // первым шагом переводим в расширенный децимал
  work_decimal dec1_work = decimal_to_work(value_1),
               dec2_work = decimal_to_work(value_2);
  work_decimal temp_result = {{0, 0, 0, 0, 0, 0, 0}, 0};
  scale_to_normal(&dec1_work, &dec2_work);  // выравниваем оба децимал по scale

  // если числа одинаковые по знакам
  if ((value_1.bits[3] & MINUS) == (value_2.bits[3] & MINUS)) {
    // просто складываем каждый int и переводим лишние
    // биты в более старшие, если нужно.
    for (int i = 0; i < 6; i++) {
      temp_result.bits[i] += dec1_work.bits[i] + dec2_work.bits[i];
      getoverflow(&temp_result);
    }

    // в результат суммы передаем scale
    temp_result.scale = dec1_work.scale;

    //нормализация для последующей концертации в обычный децимал
    // если вдруг есть переполнение, то по знаку определяем
    // в какую сторону
    if (normalize(&temp_result, 1, value_1.bits[3] & MINUS)) {
      if (value_1.bits[3] & MINUS) {
        res = 2;
      } else {
        res = 1;
      }
    } else {
      //складываем все в наш обычный децимал
      *result = work_to_decimal(temp_result);
      //проверка на знак
      if (value_1.bits[3] & MINUS) {
        result->bits[3] |= MINUS;
      }
      result->bits[3] |= (temp_result.scale << 16) & SC;  // устанавливаем скейл
    }
  } else {  // если вдруг числа разные по знакам
    // заранее запоминаем какой знак у децимала + или -

    int first_minus = (value_1.bits[3] & MINUS);
    int second_minus = (value_2.bits[3] & MINUS);

    // делаем оба децимала положительными
    value_1.bits[3] &= ~MINUS;
    value_2.bits[3] &= ~MINUS;
    for (int i = 0; i < 6; i++) {
      // вычитаем из большего децимала меньший
      if (s21_is_less(value_1, value_2)) {
        // вычитаем с помощью метода дополнения до двух
        temp_result.bits[i] += dec2_work.bits[i] + (~dec1_work.bits[i] + 1);
      } else {
        temp_result.bits[i] += dec1_work.bits[i] + (~dec2_work.bits[i] + 1);
      }
      getoverflow(&temp_result);
    }

    // передаем scale в итоговый результат суммы
    temp_result.scale = dec1_work.scale;
    int res_sign = 0x00000000;

    // определяем какой в итоге будет знак у резуьтата
    if ((s21_is_less(value_1, value_2) && second_minus) ||
        (s21_is_greater(value_1, value_2) && first_minus)) {
      res_sign |= MINUS;
    }
    normalize(&temp_result, 0, res_sign);
    *result = work_to_decimal(temp_result);  // передаем все данные результату
    result->bits[3] |= res_sign;
    result->bits[3] |= (temp_result.scale << 16) & SC;
  }
  return res;
}

// просто инвертируем знак для второго децимала и
// складываем с помощью нашего s21_add
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  value_2.bits[3] = (value_2.bits[3] & MINUS) ? value_2.bits[3] & ~MINUS
                                              : value_2.bits[3] | MINUS;
  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  if (!result) {
    error = 4;
  } else if (!s21_is_correct_decimal(value_1) ||
             !s21_is_correct_decimal(value_2)) {
    // Проверяем, что value_1 и value_2 являются корректными decimal
    error = 4;
    *result = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  } else {
    s21_decimal temp_dec = {{0, 0, 0, 0}};

    error = multiplication(value_1, value_2, &temp_dec);

    if ((value_1.bits[3] & MINUS) != (value_2.bits[3] & MINUS)) {
      s21_negate(temp_dec, &temp_dec);
    }

    if (error == 1) {
      if (temp_dec.bits[3] & MINUS) {
        error = 2;
      }
    }

    if (error == 0 && s21_is_not_equal(value_1, (s21_decimal){{0, 0, 0, 0}}) &&
        s21_is_not_equal(value_2, (s21_decimal){{0, 0, 0, 0}}) &&
        s21_is_equal(temp_dec, (s21_decimal){{0, 0, 0, 0}})) {
      error = 2;
    }

    *result = temp_dec;
  }

  return error;
}