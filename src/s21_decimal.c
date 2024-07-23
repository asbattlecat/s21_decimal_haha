#include "s21_decimal.h"

#include "helpers.c"
// int main() {
//   printf("Is it stll works? ");
// }

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
  for (int i = 6; i >= 0; i--) {
    src->bits[i] += remainder
                    << 32;  // производим запись остатка в конец меньшего int;
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
      trash += last;
    }
    if (((last > 5 || last == 5) && trash > 5) ||
        (last == 5 && trash == 5 &&
         (temp_src.bits[0] % 10) % 2 == 1)) {  // банковское округление
      if (!sign) {
        temp_src.bits[0]++;
        get_overflow(&temp_src);
      }
    }
  }

  //Если мы будем нормализовать из какой-нибудь функции (например сложение), то
  //если вдруг все биты заполнены и есть еще мусор = значит произошло
  //переполнение

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

// создаем расширенный work_decimal с бОльшим количеством int (и
// сами int больше) на основе обычного s21_decimal
work_decimal decimal_to_work(s21_decimal src) {
  work_decimal result;
  result.bits[0] = src.bits[0] & FULLBITES;
  result.bits[1] = src.bits[1] & FULLBITES;
  result.bits[2] = src.bits[2] & FULLBITES;
  result.bits[3] = 0;
  result.bits[4] = 0;
  result.bits[5] = 0;
  result.bits[6] = 0;
  result.scale = (src.bits[3] & SCALE) >> 16;
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
    while (dec1_work->scale != dec2_work->scale && !pointleft(dec1_work))
      ;
  } else if (dec2_work->scale < dec1_work->scale) {
    //умножаем на 10 второй, если он меньше первого
    while (dec1_work->scale != dec2_work->scale && !pointleft(dec2_work))
      ;
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
    scale_to_normal(&src1_work, &src2_work);  //приводим к общему scale
    for (int i = 2; i >= 0; i--) {
      //если старшие биты первого децимала меньше то,
      //значит что весь первый децимал меньше второго
      if (src1_work.bits[i] < src2_work.bits[i]) {
        result = 1;
        i = -1;  // заканчиваем цикл
      } else if (src1_work.bits[i] > src2_work.bits[i]) {
        result = 0;
        i = -1;
      }
    }

    // если оба числа отрицательные - тогда инвертирем результат
    if (src1.bits[3] & MINUS) {
      if (result == 0)
        result = 1;
      else if (result == 1)
        result = 0;
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
  scale_to_normal(&src1_work, &src2_work);  // выравниваем оба децимал по scale
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
      if (src1.bits[3] & MINUS) {
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
  } else {  // если вдруг числа разные по знакам
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
    *sum = work_to_decimal(temp_sum);  //передаем сумму в результат.
    sum->bits[3] |= sign_result;
    sum->bits[3] |= (temp_sum.scale << 16) & SCALE;
  }
  return result;
}

// меняем знак второго децимала и складываем с помощью функции s21_add
int s21_sub(s21_decimal src1, s21_decimal src2, s21_decimal *sub) {
  src2.bits[3] =
      (src1.bits[3] & MINUS) ? src1.bits[3] & ~MINUS : src2.bits[3] | MINUS;
  return s21_add(src1, src2, sub);
}

int s21_from_int_to_decimal(int figure, s21_decimal *src) {
  s21_decimal temp_src = {{0, 0, 0, 0}};
  temp_src.bits[3] = (figure < 0) ? MINUS : 0;  // вычисляем знак числа

  //передаем в decimal наше число, но уже без последнего инта, тк
  //мы уже обработали знак - но значение нужно инвертировать
  //как и ранее в сумме используем метод дополнение до двух
  temp_src.bits[0] = (figure < 0) ? (~figure & ~MINUS) + 1 : figure & ~MINUS;
  *src = temp_src;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *figure) {
  int result = 0;
  work_decimal src_work = decimal_to_work(src);
  //проверка на скейл, если он превышает 28 - обрезаем до 28
  //если меньше, ставим тот, что есть.
  int scale =
      (((src.bits[3] & SCALE) >> 16) > 28) ? 28 : ((src.bits[3] & SCALE) >> 16);

  //отбрасываем все, что после точки, так как мы хотим получить целое число
  for (int i = 0; i < scale; i++) {
    pointright(&src_work);
  }

  // проверяем не переполнен ли у нас децимал. должен быть занят
  // только самый младший бит, если больше - мы вылезли
  // за размеры инта, а значит - переполнение.
  for (int i = 6; i > 0; i--) {
    if (src_work.bits[i] != 0) {
      result = 1;
      i = 0;
    }
  }
  if (!result) {
    // передаем из нашено int в dst int
    *figure = src_work.bits[0];

    // умножаем dst на -1 если децимал отрицательный
    *figure *= (src.bits[3] & MINUS) ? -1 : 1;
  }
  return result;
}

big_decimal decimal_to_big(s21_decimal src1) {
  //попробуем использовать big decimal
  big_decimal res;
  res.decimal[0] = src1;
  res.decimal[1] = (s21_decimal){{0, 0, 0, 0}};
  return res;
}

int get_not_zero_bit(s21_decimal decimal) {
  int res = -1;
  // Проходим по всем 128 битам, начиная с самого старшего (127) к младшему (0)
  for (int i = 127; i >= 0; i--) {
    if (decimal.bits[i / 32] & (1U << (1 % 32)) & (res < 0)) {
      // Проверяем, установлен ли текущий бит
      res = i;
    }
  }
  return res;
}

int decimal_equal_zero(s21_decimal decimal) {
  //каждый бит приравниваем 0 и возвращаем
  return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 &&
         decimal.bits[3] == 0;
}

s21_decimal binary_and(s21_decimal s21_decimal_1, s21_decimal s21_decimal_2) {
  //логическое И между всеми битами
  s21_decimal res = (s21_decimal){{0, 0, 0, 0}};
  res.bits[0] = s21_decimal_1.bits[0] & s21_decimal_2.bits[0];
  res.bits[1] = s21_decimal_1.bits[1] & s21_decimal_2.bits[1];
  res.bits[2] = s21_decimal_1.bits[2] & s21_decimal_2.bits[2];
  res.bits[3] = s21_decimal_1.bits[3] & s21_decimal_2.bits[3];
  return res;
}

int is_decimal_set_bit(s21_decimal decimal, int index) {
  //ищем какой у нас инт
  unsigned int block = decimal.bits[index / 32];
  // сдвигаем на нужно количество позиций
  unsigned int mask = 1U << (index % 32);
  // Проверяем, установлен ли бит с заданным индексом
  return (block & mask) != 0;
}

int is_int_set_bit(int number, int index) {
  //такая же функция, но для для целочисленного значения
  unsigned int mask = 1U << index;
  return (number & mask) != 0;
}

int set_bit(int number, int index) {
  // функция, которая устанавливает бит в числе
  return number | (1U << index);
}

s21_decimal decimal_set_bit(s21_decimal decimal, int index) {
  decimal.bits[index / 32] = set_bit(decimal.bits[index / 32], index % 32);
  return decimal;
}

//функция для сдвига влево на 1 бит в децимале
s21_decimal binary_shift_left_one(s21_decimal decimal) {
  s21_decimal res = (s21_decimal){{0, 0, 0, 0}};
  //обработка первого блока битов 0-31:
  //предварительно проверяем есть ли 31-й бит в первом блоке
  int bit0 = is_int_set_bit(decimal.bits[0], 31);
  //сдивигаем первый блок на один бит
  unsigned int res0 = decimal.bits[0] << 1;
  //сохраняем результат сдвига в первом блоке
  res.bits[0] = res0;
  //делаем аналогичные действия для остальных блоков децимала
  int bit1 = is_int_set_bit(decimal.bits[1], 31);
  unsigned int res1 = decimal.bits[1] << 1;
  res.bits[1] = res1;
  int bit2 = is_int_set_bit(decimal.bits[2], 31);
  unsigned int res2 = decimal.bits[2] << 1;
  res.bits[2] = res2;

  unsigned int res3 = decimal.bits[3] << 1;
  res3 = res3 << 1;
  res.bits[3] = res3;

  if (bit0) {
    //если 31-ий бит был, то мы переносим его в 0-ой бит второго блока.
    //делаем так же для остальных блоков
    res.bits[1] = set_bit(res.bits[1], 0);
  }
  if (bit1) {
    res.bits[2] = set_bit(res.bits[2], 0);
  }
  if (bit2) {
    res.bits[3] = set_bit(res.bits[3], 0);
  }
  //возвращаем результат сдвига на 1 бит влево.
  return res;
}

//функция сдвига всего big децимал на shift влево
big_decimal binary_big_shift_left(big_decimal decimal, int shift) {
  big_decimal res = decimal;
  for (int i = shift; i > 0; i--) {
    //проверка, занят ли 128 бит децимала
    int bit0 = is_decimal_set_bit(res.decimal[0], 127);
    res.decimal[0] = binary_shift_left_one(res.decimal[0]);
    res.decimal[1] = binary_shift_left_one(res.decimal[0]);
    //если бит был занят, переносим его в 0-ой бит второго децимала
    if (bit0) {
      res.decimal[1] = decimal_set_bit(res.decimal[1], 0);
    }
  }  // возврат результата сдвига на shift бит влево
  return res;
}

//Побитовая операция - исключающее OR для двух децималов
//если оба бита одинаковы - возвращает 0, если разные 1
s21_decimal binary_xor(s21_decimal decimal_1, s21_decimal decimal_2) {
  s21_decimal res = (s21_decimal){{0, 0, 0, 0}};
  res.bits[0] = decimal_1.bits[0] ^ decimal_2.bits[0];
  res.bits[1] = decimal_1.bits[1] ^ decimal_2.bits[1];
  res.bits[2] = decimal_1.bits[2] ^ decimal_2.bits[2];
  res.bits[3] = decimal_1.bits[3] ^ decimal_2.bits[3];
  return res;
}

//функция побитового сложения в биг децимал
big_decimal big_decimal_bin_add(big_decimal decimal_1, big_decimal decimal_2) {
  //результат сложения будет хранится в res
  big_decimal res = decimal_1;
  // temp используем для хранения второго цисла и переносов
  big_decimal temp = decimal_2;
  //цикл продолжается пока оба децимала содержат что-то кроме 0
  while (!decimal_equal_zero(temp.decimal[0]) ||
         !decimal_equal_zero(temp.decimal[1])) {
    // Структуруа для хранения битов переноса
    big_decimal overflow_bits;
    //вычисляем биты переноса для первого и второго
    //децимала, перенос возникает когда
    //оба бита равны 1
    overflow_bits.decimal[0] = binary_and(res.decimal[0], temp.decimal[0]);
    overflow_bits.decimal[1] = binary_and(res.decimal[1], temp.decimal[1]);
    //сдвигаем биты переноса влево на один бит, для того чтобы
    //добавить перенос к следующему разряду числа
    overflow_bits = binary_big_shift_left(overflow_bits, 1);
    //выполнение XOR для сложения 2 чисел, не учитвая перенос
    res.decimal[0] = binary_xor(res.decimal[0], temp.decimal[0]);
    res.decimal[1] = binary_xor(res.decimal[1], temp.decimal[1]);
    //обновляем temp значением битов переноса, чтобы учесть их
    //в следующей итерации цикла
    temp = overflow_bits;
  }
  return res;
}

//функция которая складывает побитово 2 числа из обычного децимала
//и возвращает результат в биг децимале
//алгоритм умножения реализован через сложение и сдвиг
big_decimal bin_multi(s21_decimal value_1, s21_decimal value_2) {
  //инициализация результата
  big_decimal res = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  //темп принимает значение первого числа
  big_decimal temp = decimal_to_big(value_1);
  //находим первый не нулевой бит, чтобы сделать цикл короче
  int max_bit = get_not_zero_bit(value_2);

  for (int i = 0; i <= max_bit; i++) {
    //в цикле проверяем, если бит value 2 равен 1
    //мы складываем резалт и темп, если 0 - оставляем без изменения
    //и каждую иттерацию делаем сдвиг temp'a на 1 влево
    if (is_decimal_set_bit(value_2, i) != 0) {
      res = big_decimal_bin_add(res, temp);
    }
    temp = binary_big_shift_left(temp, 1);
  }
  return res;
}

//функция для сравнения битов между обычными децималами

int decimal_compare(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  for (int i = 127; i >= 0; i--) {
    int bit_1 = ((dec1.bits[i / 32] & (1U << i % 32))) != 0;
    int bit_2 = ((dec2.bits[i / 32] & (1U << i % 32))) != 0;
    //проверяем в цикле каждый бит, если вдруг у нас
    //в разряде встретилась единичка, а в другом 0 -
    //децимал больше
    if (bit_1 != bit_2 && res == 0) {
      if (bit_2 > bit_1) {
        res = -1;
      } else {
        res = 1;
      }
    }
  }
  return res;
}

//функция сравнения битов между биг децималами
int big_decimal_compare(big_decimal dec1, big_decimal dec2) {
  int res = decimal_compare(dec1.decimal[1], dec2.decimal[1]);
  //сравниваем сначала старшие части децимала, если они равны,
  //проверяем младшие
  if (res == 0) res = decimal_compare(dec1.decimal[0], dec2.decimal[0]);
  return res;
}

//функция логического отрицания для децимала
s21_decimal decimal_bin_not(s21_decimal dec) {
  s21_decimal res = (s21_decimal){{0, 0, 0, 0}};
  res.bits[0] = ~dec.bits[0];
  res.bits[1] = ~dec.bits[1];
  res.bits[2] = ~dec.bits[2];
  res.bits[3] = ~dec.bits[3];

  return res;
}

//функция бинарного вычитания
big_decimal big_dec_binar_sub(big_decimal dec_1, big_decimal dec_2) {
  big_decimal res;
  dec_2.decimal[0] = decimal_bin_not(dec_2.decimal[0]);
  dec_2.decimal[1] = decimal_bin_not(dec_2.decimal[1]);
  //используем вновь метод дополнение до двух
  //или часто его называет - дополнительный код
  //создаем массив, в который уже положили единицу, для
  //получения отрицательного значения числа
  big_decimal one = decimal_to_big((s21_decimal){{1, 0, 0, 0}});

  dec_2 = big_decimal_bin_add(dec_2, one);
  res = big_decimal_bin_add(dec_1, dec_2);

  return res;
}

//функция аналогична сдвигу влево, теперь сдвиг в право
//разница только в переносах битов, перекидывали из младших
//в старшие, а сейчас из старших в младшие

s21_decimal binary_shift_right_one(s21_decimal dec) {
  s21_decimal res = (s21_decimal){{0, 0, 0, 0}};

  int bit3 = is_int_set_bit(dec.bits[3], 0);
  unsigned res3 = dec.bits[3];
  res3 = res3 >> 1;
  res.bits[3] = res3;

  int bit2 = is_int_set_bit(dec.bits[2], 0);
  unsigned res2 = dec.bits[2];
  res2 = res2 >> 1;
  res.bits[2] = res2;

  int bit1 = is_int_set_bit(dec.bits[1], 0);
  unsigned res1 = dec.bits[1];
  res1 = res1 >> 1;
  res.bits[1] = res1;

  unsigned res0 = dec.bits[0];
  res0 = res0 >> 1;
  res.bits[0] = res0;

  if (bit3) {
    res.bits[2] = set_bit(res.bits[2], 31);
  }
  if (bit2) {
    res.bits[1] = set_bit(res.bits[1], 31);
  }
  if (bit1) {
    res.bits[0] = set_bit(res.bits[0], 31);
  }
  return res;
}
//функция аналогична сдвигу влево на значение shift
big_decimal binary_big_shift_right(big_decimal dec, int shift) {
  big_decimal res = dec;
  for (int i = shift; i > 0; i--) {
    int bit1 = is_decimal_set_bit(res.decimal[1], 0);
    res.decimal[0] = binary_shift_right_one(res.decimal[0]);
    res.decimal[1] = binary_shift_right_one(res.decimal[1]);
    if (bit1) {
      res.decimal[0] = decimal_set_bit(res.decimal[0], 127);
    }
  }
  return res;
}

//бинарное деление через вычитание - метод восстановления остатка
big_decimal big_decimal_bin_div(big_decimal dec1, big_decimal dec2,
                                big_decimal *ost) {
  big_decimal res;
  //частичный остаток при расчетах:
  big_decimal part_ost = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  //частное
  big_decimal quotient = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  //сначала проверяем крайние случаи - делимое равно 0:
  if (decimal_equal_zero(dec1.decimal[0]) &&
      decimal_equal_zero(dec1.decimal[1])) {
    part_ost = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
    quotient = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  } else if (big_decimal_compare(dec1, dec2) == -1) {
    //делимое меньше делителя
    quotient = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
    part_ost = dec1;
  } else {
    //во всех остальных случаях используем метод восстановления остатка
    //для начала рассчитываем предварительных сдвиг делителя
    int left_1 = get_not_zero_bit(dec1.decimal[1]);
    left_1 = (left_1 == -1) ? get_not_zero_bit(dec1.decimal[0]) : 128 + left_1;
    int left_2 = get_not_zero_bit(dec2.decimal[1]);
    left_2 = (left_2 == -1) ? get_not_zero_bit(dec2.decimal[0]) : 128 + left_2;
    int shift = left_1 - left_2;
    //сдвинутый делитель
    big_decimal shifted_divisor = binary_big_shift_left(dec2, shift);
    // div для промежуточных расчетов, изначально равен dec1
    big_decimal div = dec1;
    //флаг для проведения вычитания, на первой итерации вычитаем всегда
    int substr_needy = 1;
    for (int i = shift; i >= 0; i--) {
      //определяем действия = прибавлять или вычитать сдвинутый делитель
      part_ost = (substr_needy == 1)
                     ? big_dec_binar_sub(div, shifted_divisor)
                     : big_decimal_bin_add(div, shifted_divisor);
      //сдвиг влево на 1 частное и записываем в младший бит результата 1
      //если старший бит частичного остатка равен 1
      quotient = binary_big_shift_left(quotient, 1);
      if (is_decimal_set_bit(part_ost.decimal[1], 127) == 0)
        quotient.decimal[0] = decimal_set_bit(quotient.decimal[0], 0);
      //определяем делимое для следующей итерацией
      //(сдвиг влево на 1 частичного остатка)
      div = binary_big_shift_left(part_ost, 1);
      //если старший бит частичного остатка равен 0, то на следующей итерации
      //цикла, необходимо проводить вычитание (не проводим восстановление
      //остатка)
      substr_needy =
          (is_decimal_set_bit(part_ost.decimal[1], 127) == 0) ? 1 : 0;
    }
    //проверяем требуется ли коррекция остатка
    if (is_decimal_set_bit(part_ost.decimal[1], 127)) {
      part_ost = big_decimal_bin_add(part_ost, shifted_divisor);
    }
    //возвращаем на место частичный остаток
    part_ost = binary_big_shift_right(part_ost, left_1 - left_2);
  }
  res = quotient;
  if (ost != NULL) *ost = part_ost;
  return res;
}

//функция поиска насколько разрядов нужно
//уменьшить биг децимал, для перевода в децимал
int big_dec_get_shift_to_default_dec(big_decimal src) {
  int shift = 0;
  if (!(decimal_equal_zero(src.decimal[0]) &&
        decimal_equal_zero(src.decimal[1]))) {
    //максимальное 96 битное число
    big_decimal max =
        decimal_to_big((s21_decimal){{FULLBITES, FULLBITES, FULLBITES, 0}});
    //находим насколько src больше чем максимальное 96-битное число
    big_decimal quotient = big_decimal_bin_div(src, max, NULL);
    //перебираем все степени 10-ки, чтобы найти блишайшую большую степень, чем
    // quotient, перебрать степени гораздо быстрее чем в цикле делить на 10,
    //поэтому as it was
    while (1) {
      int compare = decimal_compare(quotient.decimal[0], all_ten_pows[shift]);
      if (compare == 1 || compare == 0) {
        break;
      }
      shift++;
    }

    //проверка что src сможет записаться в 96-бит, если поделить на 10
    //в найденной степени
    big_decimal temp =
        big_decimal_bin_div(src, decimal_to_big(all_ten_pows[shift]), NULL);
    // Если вдруг не поместилось, тогда берем следующую степени - этого будет
    // достаточно
    if (!decimal_equal_zero(temp.decimal[1]) || temp.decimal[0].bits[3] != 0) {
      shift++;
    }
  }
  return shift;
}

//функция проверки децимала на корректность (все флаги установлены верно)
int is_decimal_correct(s21_decimal dec) {
  int res = 1;
  if ((dec.bits[3] & FIRST) || dec.bits[3] & SECOND) {
    res = 0;
  } else {
    int scale = (dec.bits[3] & SCALE) >> 16;
    if (scale < 0 || scale > 28) res = 1;
  }
  return res;
}
//банковское округление
s21_decimal s21_round_banking(s21_decimal integ, s21_decimal frac) {
  s21_decimal res;  //результат округления
  s21_decimal zero_five = {{5, 0, 0, 0x00010000}};  // 0.5
  if (s21_is_equal(frac, zero_five)) {
    //если дробная часть равна 0.5
    if ((integ.bits[0] & 1) != 1) {
      //если целая часть четная, тогда без измнений
      res = integ;
    } else {
      //если целая часть четная - увеличиваем на 1.
      if (s21_is_equal(integ,
                       (s21_decimal){{FULLBITES, FULLBITES, FULLBITES, 9}})) {
        res.bits[3] = 1;  //обозначаем переполнение
      } else {
        s21_add(integ, (s21_decimal){{1, 0, 0, 0}}, &res);
      }
    }
  } else if (s21_is_greater(frac, zero_five)) {
    //если дробная часть > 0,5 увеличиваем целую часть на 1
    if (s21_is_equal(integ,
                     (s21_decimal){{FULLBITES, FULLBITES, FULLBITES, 9}})) {
      res.bits[3] = 1;  //обозначаем переполнение
    } else {
      s21_add(integ, (s21_decimal){{1, 0, 0, 0}}, &res);
    }
  } else {
    //если дробная часть < 0.5 - оставляем целую без изменения.
    res = integ;
  }
  return res;
}

//функция выравнивания двух децималов и запись в большой децимал
void s21_decimal_leveling(s21_decimal src_1, s21_decimal src_2,
                          big_decimal *val_1, big_decimal *val_2) {
  //получаем scale из обеих децималов
  int scale_1 = (src_1.bits[3] & SCALE) >> 16;
  int scale_2 = (src_2.bits[3] & SCALE) >> 16;

  //временные копии чисел без степеней, обнулим инфу о знаке и степени
  s21_decimal temp_1 = src_1;
  s21_decimal temp_2 = src_2;

  temp_1.bits[3] = 0;
  temp_2.bits[3] = 0;
  if (scale_1 > scale_2) {
    //выравниваем числа по степени:
    //если степень первого числа больше, сохраняем его как есть
    *val_1 = decimal_to_big(temp_1);

    //умножим второго число на 10 в степени scale1 - scale2 чтобы выровнить
    //степени
    *val_2 = bin_multi(temp_2, all_ten_pows[scale_1 - scale_2]);
  } else if (scale_1 < scale_2) {
    *val_1 = bin_multi(temp_1, all_ten_pows[scale_2 - scale_1]);
    *val_2 = decimal_to_big(temp_2);
  } else {
    *val_1 = decimal_to_big(temp_1);
    *val_2 = decimal_to_big(temp_2);
  }
}

//инвертирование знакового бита в децимале
int s21_negate(s21_decimal src, s21_decimal *res) {
  src.bits[3] =
      src.bits[3] & MINUS ? src.bits[3] & ~MINUS : src.bits[3] | MINUS;
  *res = src;
  return 0;
}

//функция преобразует значения из чар и записывает их в децимал
s21_decimal s21_decimal_get_from_char(char c) {
  s21_decimal result;

  switch (c) {
    case '0':
      result = (s21_decimal){{0, 0, 0, 0}};
      break;
    case '1':
      result = (s21_decimal){{1, 0, 0, 0}};
      break;
    case '2':
      s21_from_int_to_decimal(2, &result);
      break;
    case '3':
      s21_from_int_to_decimal(3, &result);
      break;
    case '4':
      s21_from_int_to_decimal(4, &result);
      break;
    case '5':
      s21_from_int_to_decimal(5, &result);
      break;
    case '6':
      s21_from_int_to_decimal(6, &result);
      break;
    case '7':
      s21_from_int_to_decimal(7, &result);
      break;
    case '8':
      s21_from_int_to_decimal(8, &result);
      break;
    case '9':
      s21_from_int_to_decimal(9, &result);
      break;
  }
  return result;
}
//функция извлечения exp из строки в научной нотации
int s21_get_float_exp_from_string(char *str) {
  int result = 0;
  char *ptr = str;
  while (*ptr) {
    if (*ptr == 'E') {
      ++ptr;
      result = strtol(ptr, NULL, 10);
      break;
    }
    ++ptr;
  }

  return result;
}

// Функция округляет число вниз к целому значению в сторону минус бесконечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  // Преобразуем в рабочий децимал
  work_decimal dec_work = decimal_to_work(value);
  // Переменная для хранения остатка дробной части после удаления
  int trash = 0;
  // Определяем скейл
  // Если масштаб больше 28, устанавливаем его в 28
  int scale =
      (((value.bits[3] & SCALE) >> 16) > 28) ? 28 : ((value.bits[3] & SCALE) >> 16);
  // Убираем дробную часть числа, сохраняя остаток в переменной trash
  for (int i = 0; i < scale; i++) {
    // Перемещаем указатель на следующую позицию и получаем значение
    int last = pointright(&dec_work);
    // Суммируем оставшуюся дробную часть
    trash += last;
  }
  // Если есть остаток и число отрицательное
  // Это означает, что мы должны округлить число вниз в сторону минус
  // бесконечности
  if (trash > 0 && value.bits[3] & MINUS) {
    // Округляем число до следующего меньшего целого
    // Это необходимо для корректного округления отрицательного числа
    dec_work.bits[0]++;
    // Обрабатываем возможное переполнение после увеличения мантиссы
    get_overflow(&dec_work);
  }
  // Преобразуем обратно в децимад
  *result = work_to_decimal(dec_work);
  // Устанавливаем знак для результата, исходя из знака входного числа
  result->bits[3] = value.bits[3] & MINUS;
  return 0;  // Возвращаем 0, так как функция выполняется успешно
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


int s21_help_to_multi(s21_decimal src_1, s21_decimal src_2,
                   s21_decimal *res) {
  int err = 0;
  int scale_1 = (src_1.bits[3] & SCALE) >> 16; //извлекаем scale
  int scale_2 = (src_1.bits[3] & SCALE) >> 16;
  
  src_1.bits[3] = 0; //зануляем все кроме мантисы перед вычислениями
  src_2.bits[3] = 0;
  //перемножаем без скейл как два больших числа
  big_decimal big_mult = bin_multi(src_1, src_2);
  //расчитаем насколько нужно поделить результат, чтобы он влез в 96 бит
  int shift = big_dec_get_shift_to_default_dec(big_mult);
  int scale_res = scale_1 + scale_2 - shift;
  if (scale_res < 0)  {
    err = 1;
    //проверяем степень на корректность
  *res = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  } else {
    //если результат надо делить более чем на 10^28 уменьшаем его, т.к
    //вещественная часть у нас максимум 28 знаков
    while ((shift > 28))
    {
      big_mult = big_decimal_bin_div(big_mult, 
      decimal_to_big((s21_decimal){{10, 0, 0, 0}}), NULL);
      shift--;
    }
    // если слишком много цифр после запятой, то корректируем результаты
    if (scale_res > 28) {
      big_decimal temp = big_mult;
      int scale_temp = scale_res;
      while (scale_temp > 28) {
        temp = big_decimal_bin_div(temp, 
        decimal_to_big((s21_decimal){{10, 0, 0, 0}}), NULL);
        scale_temp--;
      }
      shift = scale_res - scale_temp + shift;
      scale_res = scale_temp;
    }
    big_decimal ostatok = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
    big_decimal pow_ten = decimal_to_big(all_ten_pows[shift]);

    big_mult = big_decimal_bin_div(big_mult, pow_ten, &ostatok);

    //уменьшаем результат, чтобы он влез в 96 бит
    //устанавливаем степень для остатка, чтобы выполнить банковское округление
    ostatok.decimal[0].bits[3] += shift << 16;
    //выполняем банковское округление исходя из остатка от деления
    big_mult.decimal[0].bits[3] += scale_res << 16;
    //проверяем на переполнение 
    if (!decimal_equal_zero(big_mult.decimal[1]) ||
    is_decimal_correct(big_mult.decimal[0])) {
      err = 1;
     *res = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    } else {
      *res = big_mult.decimal[0];
    }
    
  }
   return err;
                   }

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  if (!result) {
    err = 4;
  } else if (!is_decimal_correct(value_1) || !is_decimal_correct(value_2)) {
    err = 4;
     *result = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  } else {
    s21_decimal temp_decimal = {{0, 0, 0, 0}};
    err = s21_help_to_multi(value_1, value_2, &temp_decimal);

    if((value_1.bits[3] & MINUS) != (value_2.bits[3] & MINUS)) {
      s21_negate(temp_decimal, &temp_decimal);
    }
    if (err == 1) {
      if (temp_decimal.bits[3] & MINUS) {
        err = 2;
      }
    }
    if (err == 0 && s21_is_not_equal(value_1, (s21_decimal){{0, 0, 0, 0}}) &&
    s21_is_not_equal(value_2, (s21_decimal){{0, 0, 0, 0}}) && 
    s21_is_equal(temp_decimal, (s21_decimal){{0, 0, 0, 0}})) {
    err = 2;
    }
    *result = temp_decimal;
  }
  return err;
}

                  
