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

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double temp_result = 0;  // временный результат
  int offset = 0;

  // проверяем каждый наш бит в децимале. Прибавляем к нашему
  // временному double результату бит переведенный из двоичной
  // системы в десятичную
  for (int i = 0; i < 96; i++) {
    if ((src.bits[i / 32] & (1l << i % 32))) {  // добавил буковку l к 1

      double temp_pow = 1;
      for (int j = 0; j < i; j++) {
        temp_pow *= 2;
      }
      temp_result += temp_pow;
    }
  }

  // вычисляем смещение точки, если оно больше нуля то делим наш
  // результат на 10 пока точка не будет в нужном месте
  if ((offset = (src.bits[3] & ~MINUS) >> 16) > 0) {
    for (int i = offset; i > 0; i--) {
      temp_result /= 10.;
    }
  }
  *dst = (float)temp_result;  // переводим double результат в float
  *dst *= (src.bits[3] & MINUS) ? -1 : 1;  // умножаем на -1 если таков знак
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if (!dst) {
    // Если указатель на decimal является NULL
    error = 1;
  } else if (src == 0.0) {
    // Отдельно обрабатываем 0.0, чтобы не выполнять лишних вычислений
    error = 0;
    *dst = (s21_decimal){{0, 0, 0, 0}};
    if (signbit(src) != 0) {
      // Добавляем знак для -0.0
      dst->bits[3] |= MINUS;
    }
  } else if (isinf(src) || isnan(src)) {
    // Отдельно обрабатываем +inf, -inf, +nan, и -nan
    error = 1;
    *dst = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    if (signbit(src) != 0) {
      // Добавляем знак для -nan и -inf
      dst->bits[3] |= MINUS;
    }
  } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
    // MAX_FLOAT_TO_CONVERT - максимальное число, которое можно сконвертировать
    // в decimal
    error = 1;
    *dst = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    if (signbit(src) != 0) {
      // Добавляем знак для для отрицательного числа
      dst->bits[3] |= MINUS;
    }
  } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
    // MIN_FLOAT_TO_CONVERT - минимальное число, которое можно сконвертировать в
    // decimal
    error = 1;
    *dst = (s21_decimal){{0, 0, 0, 0}};
  } else {
    *dst = (s21_decimal){{0, 0, 0, 0}};
    s21_decimal result;
    char flt[64];

    // Приводим float в научную запись - одна цифра до запятой и 6 цифр после
    // запятой В итоге мы получаем 7 значащих цифр, которые нам и нужно
    // перевести по заданию из float в decimal
    sprintf(flt, "%.6E", fabsf(src));
    // Получаем степень float из научной записи.

    int exp = s21_get_float_exp_from_string(flt);

    // Анализируем полученную степень.
    if (exp <= -23) {
      // Если степень слишком маленькая, то не все значащие цифры поместятся в
      // decimal Поэтому корректируем точность и заново приводим float в научную
      // запись уже с новой точностью
      int float_precision = exp + 28;
      sprintf(flt, "%.*E", float_precision, fabsf(src));
    }

    // Переводим строку с научной нотацией в decimal
    result = s21_float_string_to_decimal(flt);

    // Определяем знак результата, исходя из знака числа src (типа float)
    if (signbit(src) != 0) {
      result.bits[3] |= MINUS;
    }

    *dst = result;
  }

  return error;
}