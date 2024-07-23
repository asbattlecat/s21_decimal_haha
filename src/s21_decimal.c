#include "s21_decimal.h"

int main() {
    big_decimal decimal = {0};
    big_decimal decimal2 = {0};
    decimal.bits[0] = 0x00000FFF;
    decimal2.bits[0] = 0x000F00FF;
    printf("%d\n", compare_big_decimal(&decimal, &decimal2));
}

void set_scale (s21_decimal *decimal,int scale) {
    decimal->bits[3] &= ~0x00FF000;
    decimal->bits[3] |= (scale << 16);
}

void set_sign (s21_decimal *decimal, int sign) {
    decimal->bits[3] &= ~(1 << 31);
    decimal->bits[3] |= (sign << 31);
}

void get_scale (s21_decimal *decimal,int *scale) {
    *scale = (decimal->bits[3] >> 16) & 0xFF;
}

void get_sign (s21_decimal *value_1, int *sign_value_1, s21_decimal *value_2, int *sign_value_2) {
    *sign_value_1 = (value_1->bits[3] >> 31) & 1;
    *sign_value_2 = (value_2->bits[3] >> 31) & 1;
}

void print_binary (int number) {
    for (int i = 31; i >= 0; i--) {
        int bit = (number >> i) & 1;
        printf ("%d", bit);
        if (i % 4 == 0) printf (" ");
    }
}

void print_decimal (s21_decimal decimal) {
    for (int i = 3; i >=0; i--) {
        print_binary(decimal.bits[i]);
        printf (" ");
    }
}

void print_big_decimal (big_decimal big_decimal) {
    for (int i = 7; i >=0; i--) {
        print_binary(big_decimal.bits[i]);
        printf ("\n");
    }
}

void decimal_to_big_decimal (s21_decimal *decimal, big_decimal *big_decimal) {
    for (int i = 0; i < 4; i++) {
        big_decimal->bits[i] = decimal->bits[i];
    }
}

void shift_left_big_decimal (big_decimal *big_decimal, int shift_value) {
    int mask = ~((1 << (32 - shift_value)) - 1); // Маска для shift_value старших битов, которые потеряются при сдвиге
    int target_mask = (1 << shift_value) - 1; // Маска для shift_value младших битов последующего инта, в которые мы запишем старшие биты прошлого инта
    int lost_bits = 0; // Сюда будем записывать shift_value старших битов, что потеряются при сдвиге
    int temp_lost_bits = 0; // Здесь будет записываться значение lost_bits для предыдущего инта
    for (int i = 0; i < 8; i++) { // Идем по всем интам большого децимала
        temp_lost_bits = lost_bits; 
        lost_bits = big_decimal->bits[i] & mask; // Запоминаем старшие (левые) биты, которые будут утерены после сдвига влево

        big_decimal->bits[i] = big_decimal->bits[i] << shift_value; // Производим сам сдвиг влево на shift_value
        temp_lost_bits >>= 32 - shift_value; // Сдвиг вправо наших сохраненных битов с прошлого инта
        temp_lost_bits &= target_mask; // Очень грубо говоря, обнуляем все биты, что не относятся у сохраненным битам
        big_decimal->bits[i] |= temp_lost_bits; // Аналогично грубо говоря, соединяем текущий инт с остатком прошлого инта

/* Пожалуй, будет лучше объяснить работу этой функции на примере.
У нас есть bits[0]: 1101 0000 1101 0000 1101 0000 1101 0000
           bits[1]: 1100 0011 1100 0011 1100 0011 1100 0011
           bits[2]: 0000 0000 0000 0000 0000 0000 0000 0000 
Мы хотим сделать сдвиг влево на 4 бита (shift_value = 4). После этой операции первый инт будет выглядеть так (Остальные аналогично):
           bits[0]: 0000 1101 0000 1101 0000 1101 0000 0000
Как можно заметить, 4 старших (левых) бита (а именно 1101) были утеряны, а справа 4 бита освободились.
Нам нужно сохранить эти 4 бита, и при обработке следующего инта записать их в 4 правых.
Для этого мы используем маску - int mask = ~((1 << (32 - shift_value)) - 1);
В ней мы указываем, какие биты собираемся сохранить. В бинарной форме она выглядит так:
              mask: 1111 0000 0000 0000 0000 0000 0000 0000 (Нужные нам биты - 1, остальные 0)
Далее используя эту маску мы запишем 4 старших бита в lost_bit - lost_bits = big_decimal->bits[i] & mask; 
Здесь операция И. В lost_bit запишутся единицы только в те биты, в которых есть единица и в mask, и в bits[i]
              mask: 1111 0000 0000 0000 0000 0000 0000 0000
                    &
           bits[0]: 1101 0000 1101 0000 1101 0000 1101 0000
                    =
          lost_bit: 1101 0000 0000 0000 0000 0000 0000 0000
4 старших бита успешно сохранены.
Дальше на первой итерации ничего интересного нет. Сдвиг на 4 бита, 
temp_lost_bits на первой итерации равен нулю, так что там записываются нули в освободившиеся после сдвига биты (ок)

Вторая итерация. Обработка bits[1]. 
           bits[1]: 1100 0011 1100 0011 1100 0011 1100 0011
Мы записываем lost_bit в temp_lost_bits (1101 0000..., биты, что сохранили при обработке bits[0])
Далее записваем в lost_bit 4 левых бита уже с этого инта (аналогично тому, что описано выше).
Сдвиг на 4 бита влево
           bits[1]: 0011 1100 0011 1100 0011 1100 0011 0000
В temp_lost_bits лежат 4 бита с bits[0], которые нам нужно впихнуть сюда.
    temp_lost_bits: 1101 0000 0000 0000 0000 0000 0000 0000
Для начала сдвигаем их вправо, дабы они оказались на нужной позиции - temp_lost_bits >>= 32 - shift_value;
    temp_lost_bits: 1111 1111 1111 1111 1111 1111 1111 1101
Биты сдвинулись, но все остальное заполнилось единицами
(Заполнилось единицами из-за использования int. В нем старший бит отвечает за знак (+ или -), а в этом примере в этом бите 1
При сдвиге отрицательного числа вправо, все слева заполняется единицами. Так называемый аоифметический сдвиг
P.S. Если использовать беззнаковый тип - unsigned int, то освободившиеся биты заполнятся нулями.
Это так, для общего развития)

Теперь нужно обнулить все биты, что нам не нужны (эти самые единицы).
Здесь ипонадобится маска - int target_mask = (1 << shift_value) - 1;
       target_mask: 0000 0000 0000 0000 0000 0000 0000 1111 (Нужные биты - 1)
Обнуляем ненужные биты - temp_lost_bits &= target_mask;
    temp_lost_bits: 1111 1111 1111 1111 1111 1111 1111 1101
                    &
       target_mask: 0000 0000 0000 0000 0000 0000 0000 1111 
                    =
    temp_lost_bits: 0000 0000 0000 0000 0000 0000 0000 1101
Осталось объединить это чудо с нашим сдвинутым интом - big_decimal->bits[i] |= temp_lost_bits; 
 | - Операция ИЛИ. Возвращает 1 - если хотя-бы в одном из битов есть единица.
           bits[1]: 0011 1100 0011 1100 0011 1100 0011 0000
                    |
    temp_lost_bits: 0000 0000 0000 0000 0000 0000 0000 1101
                    =
           bits[1]: 0011 1100 0011 1100 0011 1100 0011 1101
Вот и все. Свдиг инта произведен. 4 утерянных бита записаны в lost_bits. 4 утерянных бита из bits[0] записаны в 4 младших бита
С остальными интами все аналогично.
*/
    }
}

void addition_big_decimal (big_decimal *big_value_1, big_decimal *big_value_2, big_decimal *result) {
    int carry = 0; // Переменная для сохранения переноса
    /* Т.е. напр., мы складываем биты 1 и 1. В текущий бит результата пойдет 0, 
    А 1 запишется в carry и будет учавствовать в сложении следующей пары битов */
    for (int i = 0; i < 8; i++) {
        for (int bit_position = 0; bit_position < 32; bit_position++) {
            int bit_a = (big_value_1->bits[i] >> bit_position) & 1;
            int bit_b = (big_value_2->bits[i] >> bit_position) & 1;
            int sum = bit_a + bit_b + carry;
            result->bits[i] |= (sum % 2 << bit_position);
            /* При сложении двух битов, результат заивисит от остатка от деления на 2
            0 % 2 = 0
            1 % 2 = 1   (В этом примере '0, 1, 2, 3' - возможные результаты сложения двух битов)
            2 % 2 = 0
            3 % 2 = 1 */
            carry = sum / 2;
            /* Перенос на следующий бит зависит от результата деления на 2.
            Если сумма - 0 или 1, то перенос - 0
            Если сумма - 2 или 3, то перенос - 1 */
        }
    }
}

void normalize_scales_big_decimal (big_decimal *big_value_1, int scale_1, big_decimal *big_value_2, int scale_2, int *result_scale) {
    big_decimal *smaller_scale_big_dec; // Указатель на big_decimal с меньшим скал
    int smaller_scale_value, more_scale_value; // Меньшее значение scale и большее  

    if (scale_1 < scale_2) {
        smaller_scale_big_dec = big_value_1;
        smaller_scale_value = scale_1;
        more_scale_value = scale_2;
    }
    else {
        smaller_scale_big_dec = big_value_2;
        smaller_scale_value = scale_2;
        more_scale_value = scale_1;
    }

    big_decimal temp_1 = *smaller_scale_big_dec; // Первая копия big_decimal с меньшим scale
    while (smaller_scale_value++ != more_scale_value) { // Пока наименьший scale не сравняется с наибольшим
        big_decimal temp_2 = temp_1; // Вторая копия big_decimal с меньшим scale

        shift_left_big_decimal(&temp_1, 3); // Сдвиг влево на 3 бита (эквивалентно умножению на 8)

        shift_left_big_decimal(&temp_2, 1); // Сдвиг влево на 1 бит (эквивалентно умножению на 2)

        big_decimal add_result = {0}; // Для хранения результата сложения
        addition_big_decimal(&temp_1, &temp_2, &add_result); // Cложение двух больших децималов со сдвигами на 1 и 3
        temp_1 = add_result; // Записываем результат для следующей итерации
        
    }
    *result_scale = more_scale_value; // Для scale результата берем больший scale
    *smaller_scale_big_dec = temp_1; // Закидываем измененный

/*
Небольшое пояснение. Scale - степень десятки, на которую нужно разделить мантиссу (или количество цифр после запятой)
Пример с числами с разным scale.
5 (scale = 2) + 4 (scale = 4). Этот пример можно представить как 0.05 + 0.0004
Или же 5/10^2 + 4/10^4. 
Прежде, чем их складывать, нужно привести к общему знаменателю.
Простейший способ - взять число с меньшим scale (5/10^2) и домножить его на 10 в степени разницы между обоими scale:
(5*10^2)/(10^2*10^2) = (5*10^2)/10^4.
-----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----
В этой функции в цикле while реализуется умножение на 10. 
Умножение на 10 можно реализовать с помощью сдвигов: сдвиг на 3 бита влево (умножение на 8) + сдвиг на 1 бит влево (умножение на 2)
На примере нашего числа. 5 в бинарной форме = 101
101 << 3 = 101000 (40), 101 << 1 = 1010 (10), 101000 + 1010 = 110010 (50).

Простыми словами, одна итерация цикла while - умножает мантиссу на 10 и увеличивает scale на 1

-----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----   -----
P.s. Полагаю, функцию можно улучшить. Я пытался реализовать ее, работая напрямую с переданными значениями
Однако, результат искажался по неизвестным мне причинам. Пришлось создать две временные переменные big_decimal
И производить вычисления уже с ними. 

Также мне не очень нравится конструкция if. Мейби, можно передать в эту функцию только один big_decimal (с наименьшим scale)
и разницу между scale двух децимал. Однако в таком случае, придется сравнивать scale, вычислять наименьший и разницу, где-то вне этой функции
Такой расклад мне не понравился еще больше.

В текущем виде, функция принимает два big_decimal числа, их scale и указатель на значение scale результата,
И после ее выполнения, оба числа имеют одинаковый scale и их можно с чистой совестью складывать, вычитать и сравнивать :)

P.s(x2). Не стоит забывать, что scale результата запишется не в decimal число с результатом, а лишь в переменную.
*/
}

void big_decimal_to_decimal (big_decimal *big_result, s21_decimal *result) {
    for (int i = 0; i < 3; i++) {
        result->bits[i] = big_result->bits[i];
    }
}

int compare_big_decimal (big_decimal *big_value_1, big_decimal *big_value_2) { //Сравнение двух децимал
    int return_value = 0; //0 - если равно, 1 - если первое больше, -1 - если второе больше
    for (int i = 7; i >= 0; i--) {
        if (big_value_1->bits[i] > big_value_2->bits[i]) {
            return_value = 1;
            break;
        }
        else if (big_value_1->bits[i] < big_value_2->bits[i]) {
            return_value = -1;
            break;
        }
    }
    return return_value;
    // Эту функцию нужно использовать после приведения к общему знаменателю
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    //int return_value = OK;
    int sign_value_1, sign_value_2;
    int scale_value_1, scale_value_2, scale_result;
    big_decimal big_value_1, big_value_2, big_result;
    get_sign(&value_1, &sign_value_1, &value_2, &sign_value_2);
    get_scale(&value_1, &scale_value_1);
    get_scale(&value_2, &scale_value_2);
    if (sign_value_1 != sign_value_2) {
        // Если у чисел разные знаки, выполняется вычетание.

    }
    else {
        // Если у чисел одинаковые знаки, выполняется сложение.
        // Для знака результата можно взять знак любого из чисел

        decimal_to_big_decimal(&value_1, &big_value_1);
        decimal_to_big_decimal(&value_2, &big_value_2);
        normalize_scales_big_decimal(&big_value_1, sign_value_1, &big_value_2, sign_value_2, &scale_result);
        addition_big_decimal (&big_value_1, &big_value_2, &big_result);
        big_decimal_to_decimal(&big_result, result);
        set_scale(result, scale_result);
        set_sign(result, sign_value_1);
    }
    return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    //Вычетание
}