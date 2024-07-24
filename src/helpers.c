#include "s21_decimal.h"

// Массив из всех необходимых для вычислений
// степеней 10, в некоторых моментах
// обработка больших чисел при делении на 10 - получалась очень долго
// было принято решение использовать массив со степенями 10^0 до 10^38
static const s21_decimal all_ten_pows[39] = {
    {{0x1, 0x0, 0x0, 0x0}},    // 1
    {{0xA, 0x0, 0x0, 0x0}},    // 10
    {{0x64, 0x0, 0x0, 0x0}},   // 100
    {{0x3E8, 0x0, 0x0, 0x0}},  // и т.д
    {{0x2710, 0x0, 0x0, 0x0}},
    {{0x186A0, 0x0, 0x0, 0x0}},
    {{0xF4240, 0x0, 0x0, 0x0}},
    {{0x989680, 0x0, 0x0, 0x0}},
    {{0x5F5E100, 0x0, 0x0, 0x0}},
    {{0x3B9ACA00, 0x0, 0x0, 0x0}},
    {{0x540BE400, 0x2, 0x0, 0x0}},
    {{0x4876E800, 0x17, 0x0, 0x0}},
    {{(int)0xD4A51000, 0xE8, 0x0, 0x0}},
    {{0x4E72A000, 0x918, 0x0, 0x0}},
    {{0x107A4000, 0x5AF3, 0x0, 0x0}},
    {{(int)0xA4C68000, 0x38D7E, 0x0, 0x0}},
    {{0x6FC10000, 0x2386F2, 0x0, 0x0}},
    {{0x5D8A0000, 0x1634578, 0x0, 0x0}},
    {{(int)0xA7640000, 0xDE0B6B3, 0x0, 0x0}},
    {{(int)0x89E80000, (int)0x8AC72304, 0x0, 0x0}},
    {{0x63100000, 0x6BC75E2D, 0x5, 0x0}},
    {{(int)0xDEA00000, 0x35C9ADC5, 0x36, 0x0}},
    {{(int)0xB2400000, 0x19E0C9BA, 0x21E, 0x0}},
    {{(int)0xF6800000, 0x2C7E14A, 0x152D, 0x0}},
    {{(int)0xA1000000, 0x1BCECCED, 0xD3C2, 0x0}},
    {{0x4A000000, 0x16140148, 0x84595, 0x0}},
    {{(int)0xE4000000, (int)0xDCC80CD2, 0x52B7D2, 0x0}},
    {{(int)0xE8000000, (int)0x9FD0803C, 0x33B2E3C, 0x0}},
    {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}},
    {{(int)0xA0000000, 0x6D7217CA, 0x431E0FAE, 0x1}},
    {{0x40000000, 0x4674EDEA, (int)0x9F2C9CD0, 0xC}},
    {{(int)0x80000000, (int)0xC0914B26, 0x37BE2022, 0x7E}},
    {{0x0, (int)0x85ACEF81, 0x2D6D415B, 0x4EE}},
    {{0x0, 0x38C15B0A, (int)0xC6448D93, 0x314D}},
    {{0x0, 0x378D8E64, (int)0xBEAD87C0, 0x1ED09}},
    {{0x0, 0x2B878FE8, 0x72C74D82, 0x134261}},
    {{0x0, (int)0xB34B9F10, 0x7BC90715, 0xC097CE}},
    {{0x0, 0xF436A0, (int)0xD5DA46D9, 0x785EE10}},
    {{0x0, 0x98A2240, 0x5A86C47A, 0x4B3B4CA8}}};

// Задача функции - перекидывать лишние биты в более старший int.
int getoverflow(work_decimal *src) {
  int overflow = 0;

  //Проверяем каждый int в нашем рабочем decimal на то,
  // что в нем записано больше, чем 32 бита (наш предел для 32-битного int)
  // если больше - перекидываем все лишнее на int вверх.
  for (int i = 0; i < 7; i++) {
    src->bits[i] += overflow;
    overflow = (src->bits[i] >> 32);
    src->bits[i] &= FULLBITES;
  }
  int result = 0;

  // Если нам не хватило даже наших дополнительных int то это
  // переполнение - возвращаем единицу
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
  //проверка на переполнение так, как мы увеличиваем весь децимал
  if (getoverflow(&temp_src)) {
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
    src->bits[i] +=
        remainder << 32;  // тут мы уже записывает остаток в конец меньшего int
    remainder = src->bits[i] % 10;  // остаток от будущего деления
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
        getoverflow(&temp_src);
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
// создаем расширенный work_decimal с большим количеством int'ов (и
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
  result.scale = (src.bits[3] & SC) >> 16;
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

big_decimal decimal_to_big(s21_decimal value_1) {
  //используем децимал с 7-ю интами
  big_decimal result;
  result.decimals[0] = value_1;
  result.decimals[1] = (s21_decimal){{0, 0, 0, 0}};
  return result;
}

int s21_decimal_get_not_zero_bit(s21_decimal decimal) {
  int result = -1;
  // Проходим по всем 128 битам, начиная с самого старшего (127) к младшему (0)
  for (int i = 128 - 1; i >= 0; i--) {
    if ((!!(decimal.bits[i / 32] & (1U << i % 32)))) {
      // Проверяем, установлен ли текущий бит
      result = i;
      break;
    }
  }

  return result;
}

int s21_int128_binary_equal_zero(s21_decimal decimal) {
  //каждый бит приравниваем 0 и возвращаем
  return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 &&
         decimal.bits[3] == 0;
}

s21_decimal s21_int128_binary_and(s21_decimal decimal1, s21_decimal decimal2) {
  //логическое И между всеми битами
  s21_decimal result = (s21_decimal){{0, 0, 0, 0}};
  result.bits[0] = decimal1.bits[0] & decimal2.bits[0];
  result.bits[1] = decimal1.bits[1] & decimal2.bits[1];
  result.bits[2] = decimal1.bits[2] & decimal2.bits[2];
  result.bits[3] = decimal1.bits[3] & decimal2.bits[3];

  return result;
}

int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
  //ищем какой у нас инт
  unsigned int block = decimal.bits[index / 32];
  // сдвигаем на нужно количество позиций
  unsigned int mask = 1U << (index % 32);
  // Проверяем, установлен ли бит с заданным индексом
  return (block & mask) != 0;
}

int s21_is_set_bit(int number, int index) {
  //такая же функция, но для для целочисленного значения
  unsigned int mask = 1U << index;
  return (number & mask) != 0;
}

// функция, которая устанавливает бит в числе
int s21_set_bit(int number, int index) { return number | (1U << index); }
//функция для сдвига влево на 1 бит в децимале
s21_decimal s21_int128_binary_shift_left_one(s21_decimal decimal) {
  s21_decimal result = (s21_decimal){{0, 0, 0, 0}};
  //обработка первого блока битов 0-31:
  //предварительно проверяем есть ли 31-й бит в первом блоке
  int b0 = s21_is_set_bit(decimal.bits[0], 32 - 1);
  //сдивигаем первый блок на один бит
  unsigned int result0 = decimal.bits[0];
  //сохраняем результат сдвига в первом блоке
  result0 = result0 << 1;
  result.bits[0] = result0;
  //делаем аналогичные действия для остальных блоков децимала
  int b1 = s21_is_set_bit(decimal.bits[1], 32 - 1);
  unsigned int result1 = decimal.bits[1];
  result1 = result1 << 1;
  result.bits[1] = result1;
  int b2 = s21_is_set_bit(decimal.bits[2], 32 - 1);
  unsigned int result2 = decimal.bits[2];
  result2 = result2 << 1;
  result.bits[2] = result2;
  unsigned int result3 = decimal.bits[3];
  result3 = result3 << 1;
  result.bits[3] = result3;
  if (b0) {
    //если 31-ий бит был, то мы переносим его в 0-ой бит второго блока.
    //делаем так же для остальных блоков
    result.bits[1] = s21_set_bit(result.bits[1], 0);
  }
  if (b1) {
    result.bits[2] = s21_set_bit(result.bits[2], 0);
  }
  if (b2) {
    result.bits[3] = s21_set_bit(result.bits[3], 0);
  }
  //возвращаем результат сдвига на 1 бит влево.
  return result;
}

//установка бита в децимале
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index) {
  decimal.bits[index / 32] = s21_set_bit(decimal.bits[index / 32], index % 32);
  return decimal;
}

//функция сдвига всего big децимал на shift влево
big_decimal big_decimal_binary_shift_left(big_decimal decimal, int shift) {
  big_decimal result = decimal;

  while (shift > 0) {
    //проверка, занят ли 128 бит децимала
    int b0 = s21_decimal_is_set_bit(result.decimals[0], 128 - 1);
    result.decimals[0] = s21_int128_binary_shift_left_one(result.decimals[0]);
    result.decimals[1] = s21_int128_binary_shift_left_one(result.decimals[1]);
    //если бит был занят, переносим его в 0-ой бит второго децимала
    if (b0) {
      result.decimals[1] = s21_decimal_set_bit(result.decimals[1], 0);
    }
    --shift;
  }  // возврат результата сдвига на shift бит влево

  return result;
}

//Побитовая операция - исключающее OR для двух децималов
//если оба бита одинаковы - возвращает 0, если разные 1
s21_decimal s21_int128_binary_xor(s21_decimal decimal1, s21_decimal decimal2) {
  s21_decimal result = (s21_decimal){{0, 0, 0, 0}};
  result.bits[0] = decimal1.bits[0] ^ decimal2.bits[0];
  result.bits[1] = decimal1.bits[1] ^ decimal2.bits[1];
  result.bits[2] = decimal1.bits[2] ^ decimal2.bits[2];
  result.bits[3] = decimal1.bits[3] ^ decimal2.bits[3];

  return result;
}

//функция побитового сложения в биг децимал
big_decimal big_decimal_binary_addition(big_decimal decimal1,
                                        big_decimal decimal2) {
  //результат сложения будет хранится в result
  big_decimal result = decimal1;
  // tmp используем для хранения второго цисла и переносов
  big_decimal tmp = decimal2;
  //результат сложения будет хранится в result
  //цикл продолжается пока оба децимала содержат что-то кроме 0
  while (!s21_int128_binary_equal_zero(tmp.decimals[0]) ||
         !s21_int128_binary_equal_zero(tmp.decimals[1])) {
    // Структуруа для хранения битов переноса
    big_decimal overflow_bits;
    //вычисляем биты переноса для первого и второго
    //децимала, перенос возникает когда
    //оба бита равны 1
    overflow_bits.decimals[0] =
        s21_int128_binary_and(result.decimals[0], tmp.decimals[0]);
    overflow_bits.decimals[1] =
        s21_int128_binary_and(result.decimals[1], tmp.decimals[1]);
    //сдвигаем биты переноса влево на один бит, для того чтобы
    //добавить перенос к следующему разряду числа
    overflow_bits = big_decimal_binary_shift_left(overflow_bits, 1);
    //выполнение XOR для сложения 2 чисел, не учитвая перенос
    result.decimals[0] =
        s21_int128_binary_xor(result.decimals[0], tmp.decimals[0]);
    result.decimals[1] =
        s21_int128_binary_xor(result.decimals[1], tmp.decimals[1]);
    //обновляем temp значением битов переноса, чтобы учесть их
    //в следующей итерации цикла
    tmp = overflow_bits;
  }

  return result;
}

//функция которая складывает побитово 2 числа из обычного децимала
//и возвращает результат в биг децимале
//алгоритм умножения реализован через сложение и сдвиг
big_decimal binary_mul(s21_decimal value_1, s21_decimal value_2) {
  //инициализация результата
  big_decimal result = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  //темп принимает значение первого числа
  big_decimal temp = decimal_to_big(value_1);
  //находим первый не нулевой бит, чтобы сделать цикл короче
  int max_bit = s21_decimal_get_not_zero_bit(value_2);

  for (int i = 0; i <= max_bit; i++) {
    //в цикле проверяем, если бит value 2 равен 1
    //мы складываем резалт и темп, если 0 - оставляем без изменения
    //и каждую иттерацию делаем сдвиг temp'a на 1 влево
    if (s21_decimal_is_set_bit(value_2, i) != 0) {
      result = big_decimal_binary_addition(result, temp);
    }
    temp = big_decimal_binary_shift_left(temp, 1);
  }

  return result;
}

//функция для сравнения битов между обычными децималами
int s21_int128_binary_compare(s21_decimal d1, s21_decimal d2) {
  int result = 0;

  for (int i = 128 - 1; i >= 0; i--) {
    int b1 = !!(d1.bits[i / 32] & (1U << i % 32));
    int b2 = !!(d2.bits[i / 32] & (1U << i % 32));
    //проверяем в цикле каждый бит, если вдруг у нас
    //в разряде встретилась единичка, а в другом 0 -
    //децимал больше
    if (b1 == 0 && b2 != 0) {
      result = -1;
    }

    if (b1 != 0 && b2 == 0) {
      result = 1;
    }

    if (result != 0) {
      break;
    }
  }

  return result;
}

//функция сравнения битов между биг децималами
int big_decimal_binary_compare(big_decimal d1, big_decimal d2) {
  int compare = s21_int128_binary_compare(d1.decimals[1], d2.decimals[1]);
  //сравниваем сначала старшие части децимала, если они равны,
  //проверяем младшие
  if (compare == 0) {
    compare = s21_int128_binary_compare(d1.decimals[0], d2.decimals[0]);
  }

  return compare;
}
//функция логического отрицания для децимала
s21_decimal s21_int128_binary_not(s21_decimal decimal) {
  s21_decimal result = (s21_decimal){{0, 0, 0, 0}};
  result.bits[0] = ~decimal.bits[0];
  result.bits[1] = ~decimal.bits[1];
  result.bits[2] = ~decimal.bits[2];
  result.bits[3] = ~decimal.bits[3];

  return result;
}
//функция бинарного вычитания
big_decimal big_decimal_binary_subtraction(big_decimal decimal1,
                                           big_decimal decimal2) {
  big_decimal result;
  decimal2.decimals[0] = s21_int128_binary_not(decimal2.decimals[0]);
  decimal2.decimals[1] = s21_int128_binary_not(decimal2.decimals[1]);
  //используем вновь метод дополнение до двух
  //или часто его называет - дополнительный код
  //создаем массив, в который уже положили единицу, для
  //получения отрицательного значения числа
  big_decimal one = decimal_to_big((s21_decimal){{1, 0, 0, 0}});

  decimal2 = big_decimal_binary_addition(decimal2, one);
  result = big_decimal_binary_addition(decimal1, decimal2);

  return result;
}

//функция аналогична сдвигу влево, теперь сдвиг в право
//разница только в переносах битов, перекидывали из младших
//в старшие, а сейчас из старших в младшие
s21_decimal s21_int128_binary_shift_right_one(s21_decimal decimal) {
  s21_decimal result = (s21_decimal){{0, 0, 0, 0}};

  int b3 = s21_is_set_bit(decimal.bits[3], 0);
  unsigned int result3 = decimal.bits[3];
  result3 = result3 >> 1;
  result.bits[3] = result3;

  int b2 = s21_is_set_bit(decimal.bits[2], 0);
  unsigned int result2 = decimal.bits[2];
  result2 = result2 >> 1;
  result.bits[2] = result2;

  int b1 = s21_is_set_bit(decimal.bits[1], 0);
  unsigned int result1 = decimal.bits[1];
  result1 = result1 >> 1;
  result.bits[1] = result1;

  unsigned int result0 = decimal.bits[0];
  result0 = result0 >> 1;
  result.bits[0] = result0;

  if (b3) {
    result.bits[2] = s21_set_bit(result.bits[2], 32 - 1);
  }

  if (b2) {
    result.bits[1] = s21_set_bit(result.bits[1], 32 - 1);
  }

  if (b1) {
    result.bits[0] = s21_set_bit(result.bits[0], 32 - 1);
  }

  return result;
}

//функция аналогична сдвигу влево на значение shift
big_decimal big_decimal_binary_shift_right(big_decimal decimal, int shift) {
  big_decimal result = decimal;
  while (shift > 0) {
    int b1 = s21_decimal_is_set_bit(result.decimals[1], 0);
    result.decimals[0] = s21_int128_binary_shift_right_one(result.decimals[0]);
    result.decimals[1] = s21_int128_binary_shift_right_one(result.decimals[1]);
    if (b1) {
      result.decimals[0] = s21_decimal_set_bit(result.decimals[0], 128 - 1);
    }
    --shift;
  }

  return result;
}

//бинарное деление через вычитание - метод восстановления остатка
big_decimal big_decimal_binary_division(big_decimal decimal1,
                                        big_decimal decimal2,
                                        big_decimal *remainder) {
  big_decimal result;

  //частичный остаток при расчетах:
  big_decimal partial_remainder = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  //частное
  big_decimal quotient = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  //сначала проверяем крайние случаи - делимое равно 0:
  if (s21_int128_binary_equal_zero(decimal1.decimals[0]) &&
      s21_int128_binary_equal_zero(decimal1.decimals[1])) {
    // Сначала заполняем результаты для частного случая, когда делимое равно 0
    partial_remainder = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
    quotient = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
  } else if (big_decimal_binary_compare(decimal1, decimal2) == -1) {
    //делимое меньше делителя
    quotient = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
    partial_remainder = decimal1;
  } else {
    //во всех остальных случаях используем метод восстановления остатка
    //для начала рассчитываем предварительных сдвиг делителя

    int left1 = s21_decimal_get_not_zero_bit(decimal1.decimals[1]);
    left1 = (left1 == -1) ? s21_decimal_get_not_zero_bit(decimal1.decimals[0])
                          : 128 + left1;
    int left2 = s21_decimal_get_not_zero_bit(decimal2.decimals[1]);
    left2 = (left2 == -1) ? s21_decimal_get_not_zero_bit(decimal2.decimals[0])
                          : 128 + left2;
    int shift = left1 - left2;
    //сдвинутый делитель
    big_decimal shifted_divisor =
        big_decimal_binary_shift_left(decimal2, shift);
    // Делимое для промежуточных расчетов, на первом этапе равно decimal1
    big_decimal dividend = decimal1;

    //флаг для проведения вычитания, на первой итерации вычитаем всегда
    int need_subtraction = 1;
    for (int i = shift; i >= 0; i--) {
      // Определяем необходимое действие (Прибавлять или вычитать Сдвинутый
      // делитель)
      partial_remainder =
          (need_subtraction == 1)
              ? big_decimal_binary_subtraction(dividend, shifted_divisor)
              : big_decimal_binary_addition(dividend, shifted_divisor);
      // Сдвигаем влево на 1 частное и записываем в младший бит результата 1,
      // если старший бит частичного остатка равен 1
      quotient = big_decimal_binary_shift_left(quotient, 1);
      if (s21_decimal_is_set_bit(partial_remainder.decimals[1], 128 - 1) == 0)
        quotient.decimals[0] = s21_decimal_set_bit(quotient.decimals[0], 0);

      // Рассчитываем делимое для следующей итерации цикла (сдвиг влево на 1
      // частичного остатка)
      dividend = big_decimal_binary_shift_left(partial_remainder, 1);

      // Если старший бит частичного остатка равен 0, то на следующей итерации
      // необходимо проводить вычитание (Шаг 5 алгоритма)
      if (s21_decimal_is_set_bit(partial_remainder.decimals[1], 128 - 1) == 0) {
        need_subtraction = 1;
      } else {
        need_subtraction = 0;
      }
    }
    // Определяем, требуется ли коррекция остатка
    if (s21_decimal_is_set_bit(partial_remainder.decimals[1], 128 - 1)) {
      partial_remainder =
          big_decimal_binary_addition(partial_remainder, shifted_divisor);
    }
    // Возвращаем на место частичный остаток
    partial_remainder =
        big_decimal_binary_shift_right(partial_remainder, left1 - left2);
  }

  // Заполняем переменные результата (частное и остаток)
  result = quotient;
  if (remainder != NULL) {
    *remainder = partial_remainder;
  }

  return result;
}

//функция поиска насколько разрядов нужно
//уменьшить биг децимал, для перевода в децимал
int big_decimal_get_shift_to_decimal(big_decimal value) {
  int cnt = 0;

  // Если value содержит только нули, то расчет не производим, резльтат - 0
  if (!(s21_int128_binary_equal_zero(value.decimals[0]) &&
        s21_int128_binary_equal_zero(value.decimals[1]))) {
    //максимальное 96 битное число
    big_decimal max =
        decimal_to_big((s21_decimal){{0xffffffff, 0xffffffff, 0xffffffff, 0}});
    //находим насколько src больше чем максимальное 96-битное число
    big_decimal quotient = big_decimal_binary_division(value, max, NULL);

    //перебираем все степени 10-ки, чтобы найти блишайшую большую степень, чем
    // quotient, перебрать степени гораздо быстрее чем в цикле делить на 10,
    //поэтому as it was
    while (1) {
      int compare =
          s21_int128_binary_compare(quotient.decimals[0], all_ten_pows[cnt]);
      if (compare == -1 || compare == 0) {
        break;
      }
      cnt++;
    }

    //проверка что src сможет записаться в 96-бит, если поделить на 10
    //в найденной степени
    big_decimal tmp = big_decimal_binary_division(
        value, decimal_to_big(all_ten_pows[cnt]), NULL);
    // Если вдруг не поместилось, тогда берем следующую степени - этого будет
    // достаточно
    if (!s21_int128_binary_equal_zero(tmp.decimals[1]) ||
        tmp.decimals[0].bits[3] != 0) {
      cnt++;
    }
  }

  return cnt;
}
//функция проверки децимала на корректность (все флаги установлены верно)
int s21_is_correct_decimal(s21_decimal decimal) {
  int code = 1;

  if ((decimal.bits[3] & FIRST) || (decimal.bits[3] & SECOND)) {
    code = 0;
  } else {
    int scale = (decimal.bits[3] & SC) >> 16;
    if (scale < 0 || scale > 28) {
      code = 0;
    }
  }

  return code;
}

int multiplication(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int error = 0;
  int scale1 = (value_1.bits[3] & SC) >> 16;  // Вычисляем степени
  int scale2 = (value_2.bits[3] & SC) >> 16;

  value_1.bits[3] = 0;  // Зануляем всё кроме мантиссы
  value_2.bits[3] = 0;
  // Перемножаем множители без степеней как два огромных целых числа
  big_decimal big_dec = binary_mul(value_1, value_2);
  // Рассчитываем, на сколько необходимо поделить результат, чтобы вписать его в
  // 96бит числа decimal
  int shift = big_decimal_get_shift_to_decimal(big_dec);

  int res_scale = scale1 + scale2 - shift;

  if (res_scale < 0) {
    // Анализируем степень результата на корректность
    error = 1;
    *result = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  } else {
    // Если результат надо делить более, чем на 10^28, то уменьшаем его, чтобы
    // далее делить на 10^28
    while (shift > 28) {
      big_dec = big_decimal_binary_division(
          big_dec, decimal_to_big((s21_decimal){{10, 0, 0, 0}}), NULL);
      --shift;
    }

    // Если слишком много цифр после запятой получается в результате, то
    // корректируем результат
    if (res_scale > 28) {
      big_decimal tmp = big_dec;
      int tmp_scale = res_scale;
      while (tmp_scale > 28) {
        tmp = big_decimal_binary_division(
            tmp, decimal_to_big((s21_decimal){{10, 0, 0, 0}}), NULL);
        --tmp_scale;
      }
      shift = res_scale - tmp_scale + shift;
      res_scale = tmp_scale;
    }

    big_decimal remainder = decimal_to_big((s21_decimal){{0, 0, 0, 0}});
    big_decimal powerten = decimal_to_big(all_ten_pows[shift]);

    // Уменьшаем результат, чтобы он поместился в 96бит числа decimal
    // remainder - остаток от деления при этом
    big_dec = big_decimal_binary_division(big_dec, powerten, &remainder);
    // Устанавливаем для остатка степень, чтобы выполнить банковское округление
    // чисел decimal
    // s21_decimal_set_power(&remainder.decimals[0], shift);
    remainder.decimals[0].bits[3] += shift << 16;
    // Выполняем банковское округления результата, исходя из остатка от деления
    // remainder
    big_dec.decimals[0] =
        s21_round_banking(big_dec.decimals[0], remainder.decimals[0]);
    // Устанавливаем степень результата
    // s21_decimal_set_power(&big_dec.decimals[0], res_scale);
    big_dec.decimals[0].bits[3] += res_scale << 16;
    // Анализируем результат на корректность (переполнение)
    if (!s21_int128_binary_equal_zero(big_dec.decimals[1]) ||
        !s21_is_correct_decimal(big_dec.decimals[0])) {
      error = 1;
      *result = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    } else {
      *result = big_dec.decimals[0];
    }
  }

  return error;
}

//функция выравнивания двух децималов и запись в большой децимал
void s21_decimal_leveling(s21_decimal value_1, s21_decimal value_2,
                          big_decimal *value_1l, big_decimal *value_2l) {
  //получаем scale из обеих децималов
  int scale1 = (value_1.bits[3] & SC) >> 16;
  int scale2 = (value_2.bits[3] & SC) >> 16;
  //временные копии чисел без степеней, обнулим инфу о знаке и степени
  s21_decimal tmp1 = value_1;
  s21_decimal tmp2 = value_2;

  tmp1.bits[3] = 0;
  tmp2.bits[3] = 0;

  if (scale1 > scale2) {
    //выравниваем числа по степени:
    //если степень первого числа больше, сохраняем его как есть
    *value_1l = decimal_to_big(tmp1);

    //умножим второго число на 10 в степени scale1 - scale2 чтобы выравнить
    //степени
    *value_2l = binary_mul(tmp2, all_ten_pows[scale1 - scale2]);
  } else if (scale1 < scale2) {
    *value_1l = binary_mul(tmp1, all_ten_pows[scale2 - scale1]);
    *value_2l = decimal_to_big(tmp2);
  } else {
    *value_1l = decimal_to_big(tmp1);
    *value_2l = decimal_to_big(tmp2);
  }
}
//банковское округление
s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional) {
  s21_decimal zerofive = {{5, 0, 0, 0x00010000}};  // 0.5
  s21_decimal result;  //результат округления

  if (s21_is_equal(fractional, zerofive)) {
    // Если дробная часть ровно 0.5
    if ((integral.bits[0] & 1) != 1) {
      // Если целая часть четная, то оставляем её
      result = integral;
    } else {
      // Если целая часть нечетная, то увеличиваем её на 1
      if (s21_is_equal(integral, (s21_decimal){{0xffffffff, 0xffffffff,
                                                0xffffffff, 0}})) {
        result.bits[3] = 1;  // Обозначаем переполнение
      } else {
        s21_add(integral, (s21_decimal){{1, 0, 0, 0}}, &result);
      }
    }
  } else if (s21_is_greater(fractional, zerofive)) {
    // Если дробная часть > 0.5, то увеличиваем целую часть на 1
    if (s21_is_equal(integral,
                     (s21_decimal){{0xffffffff, 0xffffffff, 0xffffffff, 0}})) {
      result.bits[3] = 1;  // Обозначаем переполнение
    } else {
      s21_add(integral, (s21_decimal){{1, 0, 0, 0}}, &result);
    }
  } else {
    // Если дробная часть < 0.5, то оставляем целую часть без изменений
    result = integral;
  }

  return result;
}
