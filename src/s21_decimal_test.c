#include "s21_decimal.h"

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "s21_decimal_test.h"

START_TEST(test_add) {
  {
    int num1, num2, sum_int, res_int;
    s21_decimal a, b, res_dec;

    num1 = 42;
    num2 = 30;
    sum_int = 72;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);
    ck_assert_int_eq(s21_add(a, b, &res_dec), 0);

    num1 = 1000;
    num2 = 2000;
    sum_int = 3000;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = 0;
    num2 = 0;
    sum_int = 0;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = -15;
    num2 = 5;
    sum_int = -10;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = 11115;
    num2 = 5;
    sum_int = 11120;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = -1;
    num2 = -10;
    sum_int = -11;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = -1234;
    num2 = 234;
    sum_int = -1000;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = -9403;
    num2 = 234;
    sum_int = -9169;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = 9403;
    num2 = 202;
    sum_int = 9605;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    num1 = 450;
    num2 = -50;
    sum_int = 400;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);

    int tmp1 = 100;
    int tmp2 = 99999;
    int res_s21 = 0;
    int res = 100099;
    s21_decimal res1;
    s21_from_int_to_decimal(tmp1, &a);
    s21_from_int_to_decimal(tmp2, &b);
    s21_add(a, b, &res1);
    s21_from_decimal_to_int(res1, &res_s21);
    ck_assert_int_eq(res_s21, res);

    tmp1 = -100;
    tmp2 = -99999;
    res_s21 = 0;
    res = -100099;

    s21_from_int_to_decimal(tmp1, &a);
    s21_from_int_to_decimal(tmp2, &b);
    s21_add(a, b, &res1);
    s21_from_decimal_to_int(res1, &res_s21);
    ck_assert_int_eq(res_s21, res);

    tmp1 = 2147483647;
    tmp2 = -2147483647;
    res_s21 = 0;
    res = 0;

    s21_from_int_to_decimal(tmp1, &a);
    s21_from_int_to_decimal(tmp2, &b);
    s21_add(a, b, &res1);
    s21_from_decimal_to_int(res1, &res_s21);
    ck_assert_int_eq(res_s21, res);

    a.bits[3] = 0x300000;
    a.bits[2] = 0;
    a.bits[1] = 0xF;
    a.bits[0] = 0x67E4FEEF;
    b.bits[3] = 0x300000;
    b.bits[2] = 0;
    b.bits[1] = 0xFF;
    b.bits[0] = 0x67E4FFFF;
    s21_decimal dec_res;
    dec_res.bits[3] = 0x300000;
    dec_res.bits[2] = 0;
    dec_res.bits[1] = 0x10E;
    dec_res.bits[0] = 0xCFC9FEEE;

    s21_add(a, b, &res1);
    ck_assert_int_eq(dec_res.bits[3], res1.bits[3]);
    ck_assert_int_eq(dec_res.bits[2], res1.bits[2]);
    ck_assert_int_eq(dec_res.bits[1], res1.bits[1]);
    ck_assert_int_eq(dec_res.bits[0], res1.bits[0]);

    tmp1 = -2147483647;
    tmp2 = 2147483647;
    res_s21 = 0;
    res = 0;

    s21_from_int_to_decimal(tmp1, &a);
    s21_from_int_to_decimal(tmp2, &b);
    s21_add(a, b, &res1);
    s21_from_decimal_to_int(res1, &res_s21);
    ck_assert_int_eq(res_s21, res);

    a.bits[0] = UINT_MAX;
    a.bits[1] = UINT_MAX;
    a.bits[2] = UINT_MAX;
    a.bits[3] = 0;

    b.bits[0] = 1;
    b.bits[1] = 0;
    b.bits[2] = 0;
    b.bits[3] = 0;

    int ret_s21 = s21_add(a, b, &res1);
    ck_assert_int_eq(1, ret_s21);

    a.bits[0] = 0xffffffff;
    a.bits[1] = 0xffffffff;
    a.bits[2] = 0xffffffff;
    a.bits[3] = MINUS;

    b.bits[0] = 1;
    b.bits[1] = 0;
    b.bits[2] = 0;
    b.bits[3] = MINUS;

    ret_s21 = s21_add(a, b, &res1);
    ck_assert_int_eq(2, ret_s21);
  }
  {
    s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{2, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{15, 0, 0, 0}};
    s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{1, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(1, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(2, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{8, 0, 0, 0}};
    s21_decimal val2 = {{2, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{2, 0, 0, 0}};
    s21_decimal val2 = {{8, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{2, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{8, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {0};
    s21_decimal val2 = {0};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{4, 0, 0, 0}};
    s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {0};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{4, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(2, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{4, 0, 0, 0}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_add(val1, val2, &res));
  }
  {
    s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(2, s21_add(val1, val2, &res));
  }
  {
    s21_decimal c = {{5, 0, 0, 0}};
    s21_decimal d = {{5, 0, 0, 0}};
    s21_decimal etalon = {{10, 0, 0, 0}};
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{100, 0, 0, 0}};
    s21_decimal d = {{100, 0, 0, 0}};
    s21_decimal etalon = {{100, 0, 0, 0}};
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    int add = s21_add(c, d, p_res);
    ;
    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(equal, 0);
  }
  {
    s21_decimal c = {{2147483647, 0, 0, 0}};
    s21_decimal d = {{2147483647, 0, 0, 0}};
    s21_decimal etalon = {{0xFFFFFFFE, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_result = &result;

    int add = s21_add(c, d, p_result);
    ck_assert_int_eq(add, 0);
    ;
    int equal = s21_is_equal(result, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1000, 0, 0, 0}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{2000, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_result = &result;

    int add = s21_add(c, d, p_result);
    ck_assert_int_eq(add, 0);
    ;
    int equal = s21_is_equal(result, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1000, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_result = &result;

    int add = s21_add(c, d, p_result);
    ck_assert_int_eq(add, 0);
    ;
    int equal = s21_is_equal(result, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_result = &result;

    int add = s21_add(c, d, p_result);
    ck_assert_int_eq(add, 0);
    ;
    int equal = s21_is_equal(*p_result, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0, 0, 0, 0}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{2, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1000, 0, 0, 0}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{2000, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{INT_MAX, 0, 0, 0}};
    s21_decimal d = {{INT_MAX, 0, 0, 0}};
    s21_decimal etalon = {{0xFFFFFFFE, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{INT_MAX, 0, 0, 0}};
    s21_decimal d = {{INT_MAX, 0, 0, 0}};
    s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{UINT32_MAX, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 1, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[3], etalon.bits[3]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0, UINT_MAX - 1, 0, 0}};
    s21_decimal d = {{0, 1, 0, 0}};
    s21_decimal etalon = {{0, UINT_MAX, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0, 0, UINT_MAX - 1, 0}};
    s21_decimal d = {{0, 0, 1, 0}};
    s21_decimal etalon = {{0, 0, UINT_MAX, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }

  {
    s21_decimal c = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[3], etalon.bits[3]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{11, 0, 0, 65536}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{11, 0, 0, 65536}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{11, 0, 0, 65536}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{21, 0, 0, 65536}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{111, 0, 0, 65536}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{121, 0, 0, 65536}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{111, 0, 0, 196608}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{1111, 0, 0, 196608}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {0};
    c.bits[0] = 0b11111111111111111111111111111110;
    c.bits[1] = 0b00000000000000000000000000000000;
    c.bits[2] = 0b00000000000000000000000000000000;
    c.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {0};
    etalon.bits[0] = 0b11111111111111111111111111111111;
    etalon.bits[1] = 0b00000000000000000000000000000000;
    etalon.bits[2] = 0b00000000000000000000000000000000;
    etalon.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{UINT32_MAX - 1, UINT32_MAX, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{UINT32_MAX, UINT32_MAX, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
    s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
    s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0b10001001111001111111111111111111,
                      0b10001010110001110010001100000100, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0b10001001111010000000000000000000,
                           0b10001010110001110010001100000100, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 1, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }

  {
    s21_decimal c = {{0b10000010111000100101101011101101,
                      0b11111001111010000010010110101101,
                      0b10110000001111101111000010010100,
                      0b10000000000011100000000000000000}};
    s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
    s21_decimal etalon = {{0b01110001001010101101101011101101,
                           0b00101110001111001110000111111000,
                           0b10110000001111101110111101101101,
                           0b10000000000011100000000000000000}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0b10000010111000100101101011101101,
                      0b11111001111010000010010110101101,
                      0b10110000001111101111000010010100,
                      0b10000000000011100000000000000000}};
    s21_decimal d = {{0b01001000000110110001111110011000,
                      0b11111011111111011000100101101101,
                      0b00000000000001000110110101110111,
                      0b10000000000110000000000000000000}};
    s21_decimal etalon = {{0b10110110001010011011010111011010,
                           0b11111001111010100000110001111111,
                           0b10110000001111101111000010010100,
                           0b10000000000011100000000000000000}};
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal a, b, origin;
    a.bits[0] = 0b01001110111001000011100101110110;
    a.bits[1] = 0b01001011001101011010000111011001;
    a.bits[2] = 0b00011001101110010111010010111111;
    a.bits[3] = 0b00000000000011110000000000000000;
    b.bits[0] = 0b00000000000000000000000000000000;
    b.bits[1] = 0b00000000000000000000000000000000;
    b.bits[2] = 0b00000000000000000000000000000000;
    b.bits[3] = 0b00000000000000000000000000000000;
    origin.bits[0] = 0b01001110111001000011100101110110;
    origin.bits[1] = 0b01001011001101011010000111011001;
    origin.bits[2] = 0b00011001101110010111010010111111;
    origin.bits[3] = 0b00000000000011110000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_decimal* p_res = &result;
    int add = s21_add(a, b, p_res);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);

    int equal = s21_is_equal(result, origin);
    ck_assert_int_eq(equal, 1);
  }

  {
    s21_decimal c = {{0, 0, 0, 0}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{2, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1000, 0, 0, 0}};
    s21_decimal d = {{1000, 0, 0, 0}};
    s21_decimal etalon = {{2000, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{INT_MAX, 0, 0, 0}};
    s21_decimal d = {{INT_MAX, 0, 0, 0}};
    s21_decimal etalon = {{0xFFFFFFFE, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{INT_MAX, 0, 0, 0}};
    s21_decimal d = {{INT_MAX, 0, 0, 0}};
    s21_decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{UINT_MAX, 0, 0, 0}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 1, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[3], etalon.bits[3]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0, UINT_MAX - 1, 0, 0}};
    s21_decimal d = {{0, 1, 0, 0}};
    s21_decimal etalon = {{0, UINT_MAX, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0, 0, UINT_MAX - 1, 0}};
    s21_decimal d = {{0, 0, 1, 0}};
    s21_decimal etalon = {{0, 0, UINT_MAX, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{0, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal d = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{11, 0, 0, 65536}};
    s21_decimal d = {{0, 0, 0, 0}};
    s21_decimal etalon = {{11, 0, 0, 65536}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{11, 0, 0, 65536}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{21, 0, 0, 65536}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{111, 0, 0, 65536}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{121, 0, 0, 65536}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{111, 0, 0, 196608}};
    s21_decimal d = {{1, 0, 0, 0}};
    s21_decimal etalon = {{1111, 0, 0, 196608}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
    s21_decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
    s21_decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0b10001001111001111111111111111111,
                      0b10001010110001110010001100000100, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0b10001001111010000000000000000000,
                           0b10001010110001110010001100000100, 0, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
    s21_decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 1, 0}};

    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;

    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);

    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal c = {{0b10000010111000100101101011101101,
                      0b11111001111010000010010110101101,
                      0b10110000001111101111000010010100,
                      0b10000000000011100000000000000000}};
    s21_decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
    s21_decimal etalon = {{0b01110001001010101101101011101101,
                           0b00101110001111001110000111111000,
                           0b10110000001111101110111101101101,
                           0b10000000000011100000000000000000}};
    s21_decimal res = {{0, 0, 0, 0}};
    s21_decimal* p_res = &res;
    int add = s21_add(c, d, p_res);
    ck_assert_int_eq(add, 0);
    ck_assert_int_eq(res.bits[0], etalon.bits[0]);
    ck_assert_int_eq(res.bits[1], etalon.bits[1]);
    ck_assert_int_eq(res.bits[2], etalon.bits[2]);
    ck_assert_int_eq(res.bits[3], etalon.bits[3]);
    int equal = s21_is_equal(res, etalon);
    ck_assert_int_eq(equal, 1);
  }

  {
    s21_decimal a = {0};
    a.bits[0] = 0b11111111111111111111111111111111;
    a.bits[1] = 0b11111111111111111111111111111111;
    a.bits[2] = 0b11111111111111111111111111111111;
    a.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal b = {0};
    b.bits[0] = 0b00000000000000000000000000000010;
    b.bits[1] = 0b00000000000000000000000000000000;
    b.bits[2] = 0b00000000000000000000000000000000;
    b.bits[3] = 0b00000000000000110000000000000000;
    s21_decimal s21_res = {0};
    ck_assert_int_eq(s21_add(a, b, &s21_res), 1);
  }
  {
    s21_decimal a = {0};
    a.bits[0] = 0b11111111111111111111111111111111;
    a.bits[1] = 0b11111111111111111111111111111111;
    a.bits[2] = 0b11111111111111111111111111111111;
    a.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal b = {0};
    b.bits[0] = 0b00000000000000000000000000000101;
    b.bits[1] = 0b00000000000000000000000000000000;
    b.bits[2] = 0b00000000000000000000000000000000;
    b.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal s21_res = {0};
    ck_assert_int_eq(s21_add(a, b, &s21_res), 1);
  }
  {
    s21_decimal a = {0};
    a.bits[0] = 0b11111111111111111111111111111111;
    a.bits[1] = 0b11111111111111111111111111111111;
    a.bits[2] = 0b11111111111111111111111111111111;
    a.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal b = {0};
    b.bits[0] = 0b00000000000000000000000000000001;
    b.bits[1] = 0b00000000000000000000000000000000;
    b.bits[2] = 0b00000000000000000000000000000000;
    b.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal s21_res = {0};
    ck_assert_int_eq(s21_add(a, b, &s21_res), 1);
  }
  {
    s21_decimal src1 = {0};
    src1.bits[0] = 0xffffffff;
    src1.bits[1] = 0xffffffff;
    src1.bits[2] = 0xffffffff;
    src1.bits[3] = 0x80000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0x00000002;  // 0.002
    src2.bits[1] = 0x00000000;
    src2.bits[2] = 0x00000000;
    src2.bits[3] = 0x00030000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0xfffffffe;
    original_res.bits[1] = 0xffffffff;
    original_res.bits[2] = 0xffffffff;
    original_res.bits[3] = 0x80000000;
    s21_decimal s21_res = {0};
    // s21_add(src1, src2, &s21_res);
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
  }
  {
    s21_decimal a = {0};
    a.bits[0] = 0b11111111111111111111111111111111;
    a.bits[1] = 0b11111111111111111111111111111111;
    a.bits[2] = 0b11111111111111111111111111111111;
    a.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal b = {0};
    b.bits[0] = 0b00000000000000000000000000000101;
    b.bits[1] = 0b00000000000000000000000000000000;
    b.bits[2] = 0b00000000000000000000000000000000;
    b.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0b11111111111111111111111111111110;
    original_res.bits[1] = 0b11111111111111111111111111111111;
    original_res.bits[2] = 0b11111111111111111111111111111111;
    original_res.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal s21_res = {0};
    s21_add(a, b, &s21_res);
    ck_assert_int_eq(s21_add(a, b, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
  }
  {
    s21_decimal a = {0};
    a.bits[0] = 0b11111111111111111111111111111111;
    a.bits[1] = 0b11111111111111111111111111111111;
    a.bits[2] = 0b11111111111111111111111111111111;
    a.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal b = {0};
    b.bits[0] = 0b00000000000000000000000000000001;
    b.bits[1] = 0b00000000000000000000000000000000;
    b.bits[2] = 0b00000000000000000000000000000000;
    b.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0b11111111111111111111111111111110;
    original_res.bits[1] = 0b11111111111111111111111111111111;
    original_res.bits[2] = 0b11111111111111111111111111111111;
    original_res.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal s21_res = {0};
    s21_add(a, b, &s21_res);
    ck_assert_int_eq(s21_add(a, b, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
  }
  {
    s21_decimal a = {0};
    a.bits[0] = 0b00000000000000000000001111111111;
    a.bits[1] = 0b00000000000000000000000000000000;
    a.bits[2] = 0b00000000000000000000000000000000;
    a.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal b = {0};
    b.bits[0] = 0b00000000000000000000001111111111;
    b.bits[1] = 0b00000000000000000000000000000000;
    b.bits[2] = 0b00000000000000000000000000000000;
    b.bits[3] = 0b00000000000000100000000000000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0b00000000000000000010101111110101;
    original_res.bits[1] = 0b00000000000000000000000000000000;
    original_res.bits[2] = 0b00000000000000000000000000000000;
    original_res.bits[3] = 0b00000000000000100000000000000000;
    s21_decimal s21_res = {0};
    s21_add(a, b, &s21_res);
    ck_assert_int_eq(s21_add(a, b, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
  }

  {
    s21_decimal src1 = {0};
    src1.bits[0] = 0x00000000;
    src1.bits[1] = 0x0000000f;
    src1.bits[2] = 0x00000000;
    src1.bits[3] = 0x00000000;
    s21_decimal src2 = {0};
    src2.bits[0] = 0x00000001;
    src2.bits[1] = 0x00000000;
    src2.bits[2] = 0x00000000;
    src2.bits[3] = 0x80000000;
    s21_decimal original_res = {0};
    original_res.bits[0] = 0xffffffff;
    original_res.bits[1] = 0x0000000e;
    original_res.bits[2] = 0x00000000;
    original_res.bits[3] = 0x00000000;
    s21_decimal s21_res = {0};
    ck_assert_int_eq(s21_add(src1, src2, &s21_res), 0);
    ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
    ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
    ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
    ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
  }
}
END_TEST

START_TEST(test_from_decimal_to_int) {
  s21_decimal src;
  int result = 0, number = 0;

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 2147483647;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = MINUS;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483647);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = MINUS;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = MINUS;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);

  number = 0;

  src.bits[0] = 0xffffffff;
  src.bits[1] = 0xffffffff;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 1);

  result = 0;

  src.bits[0] = 0x1fffffff;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 536870911);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 100;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 100);
  ck_assert_int_eq(result, 0);

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, INT_MAX);
  ck_assert_int_eq(result, 0);

  src.bits[0] = INT_MAX;
  src.bits[1] = INT_MAX;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 1);

  src.bits[0] = INT_MAX;
  src.bits[1] = INT_MAX;
  src.bits[2] = INT_MAX;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 1);

  src.bits[0] = INT_MAX;
  src.bits[1] = INT_MAX;
  src.bits[2] = INT_MAX;
  src.bits[3] = INT_MAX;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 3);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b11111111111111111111111111111111;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -1);
  ck_assert_int_eq(result, 0);

  src.bits[0] = UINT_MAX;
  src.bits[1] = UINT_MAX;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 1);

  src.bits[0] = UINT_MAX;
  src.bits[1] = UINT_MAX;
  src.bits[2] = UINT_MAX;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 1);

  src.bits[0] = UINT_MAX;
  src.bits[1] = UINT_MAX;
  src.bits[2] = UINT_MAX;
  src.bits[3] = UINT_MAX;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -7);
  ck_assert_int_eq(result, 0);

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = MINUS;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -INT_MAX);
  ck_assert_int_eq(result, 0);

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0x00010000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 214748364);
  ck_assert_int_eq(result, 0);

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0x801C0000;  // MINUS + exp 28
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 0);

  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0x001C0000;  // exp 28
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b10000000000000000000000000000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000001;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483648);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b00000000000000000000000000000001;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 1);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b10000000000000000000000000000001;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483647);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b00000000000000000000000000000010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 2);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b00000000000000000000000000100011;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 3);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b00000000000000000000000000101101;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000010000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -4);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b10110011000011000010101010010001;
  src.bits[1] = 0b00000000000000000000000000001100;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000001110000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -5454);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b00000111100110110001111110011000;
  src.bits[1] = 0b01100110010010001001000110100011;
  src.bits[2] = 0b00000000000001001000101100011101;
  src.bits[3] = 0b10000000000110000000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -5);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b00011011110101100011100010001010;
  src.bits[1] = 0b00000000000000101101010000010100;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000001100000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 796132784);
  ck_assert_int_eq(result, 0);

  src.bits[0] = 0b01111000100010101111010011001010;
  src.bits[1] = 0b01100010000010101110010010000111;
  src.bits[2] = 0b00100111111001000001101011010101;
  src.bits[3] = 0b10000000000101010000000000000000;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -12345677);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_int_to_decimal) {
  s21_decimal val;

  s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-128, &val);
  ck_assert_int_eq(val.bits[0], 128);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);

  s21_from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-2147483648, &val);
  ck_assert_int_eq(val.bits[0], -2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);

  s21_from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_mul1) {
  {
    int num1 = -10;
    int num2 = -10;
    int prod_int = 100;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_mul(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, prod_int);
  }
  {
    int num1 = 10;
    int num2 = 20;
    int prod_int = 200;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_mul(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, prod_int);
  }
  {
    int num1 = -10;
    int num2 = 20;
    int prod_int = -200;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_mul(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, prod_int);
  }
  {
    int num1 = 9403;
    int num2 = 202;
    int res_origin = 1899406;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_mul(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    int num1 = -32768;
    int num2 = 2;
    int res_origin = -65536;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_mul(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    int num1 = -32768;
    int num2 = 32768;
    int res_origin = -1073741824;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_mul(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, res_origin);
  }
  {
    s21_decimal dec1 = {{4, 0, 0, 0}};
    s21_decimal dec2 = {{10, 0, 0, 0}};

    s21_decimal d22;
    s21_mul(dec1, dec2, &d22);

    int qqqq = 0;
    s21_from_decimal_to_int(d22, &qqqq);
    ck_assert_int_eq(qqqq, 40);
  }

  {
    s21_decimal dst1;
    dst1.bits[0] = 0b01110000000000000000000000000000;
    dst1.bits[1] = 0b10110011000000110001000010100111;
    dst1.bits[2] = 0b11100010001011101010010010010011;
    dst1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal dst2;
    dst2.bits[0] = 0b00000000000000000000000000000001;
    dst2.bits[1] = 0b10000000000000100000000000000000;
    dst2.bits[2] = 0b00000000000000000000000000000000;
    dst2.bits[3] = 0b00000000000000000000000000000000;

    s21_decimal d22;
    int error = s21_mul(dst1, dst2, &d22);

    // int qqqq = 0;
    // s21_from_decimal_to_int(d22, &qqqq);
    ck_assert_int_eq(error, 1);
  }

  {
    s21_decimal dst1;
    dst1.bits[0] = 0b01110000000000000000000000000000;
    dst1.bits[1] = 0b10110011000000110001000010100111;
    dst1.bits[2] = 0b11100010001011101010010010010011;
    dst1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal dst2;
    dst2.bits[0] = 0b00000000000000000000000000000001;
    dst2.bits[1] = 0b10000000000000100000000000000000;
    dst2.bits[2] = 0b00000000000000000000000000000000;
    dst2.bits[3] = 0b10000000000000000000000000000000;

    s21_decimal d22;
    int error = s21_mul(dst1, dst2, &d22);

    // int qqqq = 0;
    // s21_from_decimal_to_int(d22, &qqqq);
    ck_assert_int_eq(error, 2);
  }

  {
    // 792281625.14264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int code = s21_mul(decimal1, decimal2, NULL);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // Просто все единицы
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  {
    // Просто все единицы
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_mul(decimal1, decimal2, &result);

    ck_assert_int_ne(code, 0);
  }

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * * * * * * * * * * * * * * * Тесты на все типы данных (ручные)
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * * * * * * * * * * * * * * */

  {
    // 7.9228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7.8228162514264337593543950335
    s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x1C0000}};
    // 61.978735728724164262422454727
    s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x1B0000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // 7.9228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // -0.8228162514264337593543950335
    s21_decimal decimal2 = {{0x4F63FFFF, 0xBB0D25CF, 0x1A962D2F, 0x801C0000}};
    // -6.5190219687391279469416894926
    s21_decimal check = {{0x23B23CAE, 0xEC60363A, 0xD2A415FA, 0x801C0000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // -7.000000000000025
    s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
    // -0.00000000000005
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800E0000}};
    // 0.0000000000003500000000000012
    s21_decimal check = {{0x40B6C00C, 0xC6F3B, 0x0, 0x1C0000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // -7922816251426.4337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // 78228162514264.337593543950335
    s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xF0000}};
    // -619787357287241642624224547.27
    s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80020000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // -79228162514264.337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // 782281625142643.37593543950335
    s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
    // -61978735728724164262422454727
    s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80000000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // 79228162514264.1
    s21_decimal decimal1 = {{0x70D42571, 0x2D093, 0x0, 0x10000}};
    // 78228162514264.5
    s21_decimal decimal2 = {{0x22618575, 0x2C77B, 0x0, 0x10000}};
    // 6197873572872410706900970254.4
    s21_decimal check = {{0x7F6C2E90, 0x3FD777DD, 0xC8439BCC, 0x10000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // 79228162514265.1
    s21_decimal decimal1 = {{0x70D4257B, 0x2D093, 0x0, 0x10000}};
    // 78228162514264.5
    s21_decimal decimal2 = {{0x22618575, 0x2C77B, 0x0, 0x10000}};
    // 6197873572872488935063484519.0
    s21_decimal check = {{0xA1CDB406, 0x3FDA3F58, 0xC8439BCC, 0x10000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // 5.0
    s21_decimal decimal1 = {{0x32, 0x0, 0x0, 0x10000}};
    // 4.5
    s21_decimal decimal2 = {{0x2D, 0x0, 0x0, 0x10000}};
    // 22.50
    s21_decimal check = {{0x8CA, 0x0, 0x0, 0x20000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // 79228162.5
    s21_decimal decimal1 = {{0x2F394219, 0x0, 0x0, 0x10000}};
    // 78228162.5555555555555
    s21_decimal decimal2 = {{0xB20798E3, 0x6856A1BC, 0x2A, 0xD0000}};
    // 6197873575027970.8333289317688
    s21_decimal check = {{0x34C52538, 0x6AFC5902, 0xC8439BCD, 0xD0000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // -7.000000000000025
    s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
    // -2.00000000000005
    s21_decimal decimal2 = {{0x20F48005, 0xB5E6, 0x0, 0x800E0000}};
    // 14.000000000000400000000000001
    s21_decimal check = {{0xF1E90001, 0xBD686F20, 0x2D3C8750, 0x1B0000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // -7.000000000000025
    s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
    // -0.0000000000005
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800D0000}};
    // 0.0000000000035000000000000125
    s21_decimal check = {{0x8723807D, 0x7C5850, 0x0, 0x1C0000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // -7.000000000000025
    s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
    // -0.000000000000005
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800F0000}};
    // 0.0000000000000350000000000001
    s21_decimal check = {{0xB9ABE001, 0x13E52, 0x0, 0x1C0000}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // 7.9228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 0.00000
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x50000}};
    // 0
    s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

    test_mul(decimal1, decimal2, check);
  }

  {
    // 7922816251426433759354395032.8
    s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 10.000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 7922816251426433759354395032.8
    s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // -10.000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -7922816251426433759354395032.7
    s21_decimal decimal1 = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // 10.000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {
        {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -7922816251426433759354395032.7
    s21_decimal decimal1 = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -10.000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -0.0000000000000025
    s21_decimal decimal1 = {{0x19, 0x0, 0x0, 0x80100000}};
    // -0.0000000000000005
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
    // too small
    // 0.0000000000000000000000000000
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1C0000}};
    int code_check = 2;

    test_mul_fail2(decimal1, decimal2, decimal_check, code_check);
  }

  {
    // 792281625142643.37593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // -782281625142643.37593543950335
    s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x800E0000}};
    // overflow
    int code_check = 2;

    // test_mul(decimal1, decimal2, decimal_check);
    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 792281625142643.37593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 782281625142643.37593543950335
    s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
    // overflow
    int code_check = 1;

    // test_mul(decimal1, decimal2, decimal_check);
    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -26409387504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -26409387498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 6148914691236517205
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -6148914691236517205
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 6148914689804861440
    s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -6148914689804861440
    s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 1431655765
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -1431655765
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387.504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -26409387.504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387.498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -26409387.498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387
    s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -26409387
    s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 1.9999999999999999999999999000
    s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
    // 52818775009509558395695964249
    s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -1.9999999999999999999999999000
    s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
    // -52818775009509558395695964249
    s21_decimal decimal_check = {
        {0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 1
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
    // 26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -1
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
    // -26409387504754779197847983445
    s21_decimal decimal_check = {
        {0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.5
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
    // 13204693752377389598923991722
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.5
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
    // -13204693752377389598923991722
    s21_decimal decimal_check = {
        {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.4999999999999999999999999999
    s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // 13204693752377389598923991720
    s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.4999999999999999999999999999
    s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // -13204693752377389598923991720
    s21_decimal decimal_check = {
        {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.5000000000000000000000000001
    s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // 13204693752377389598923991725
    s21_decimal decimal_check = {{0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.5000000000000000000000000001
    s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // -13204693752377389598923991725
    s21_decimal decimal_check = {
        {0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 1.0000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 26409387504754779197847983448
    s21_decimal decimal_check = {{0x55555558, 0x55555555, 0x55555555, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -1.0000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -26409387504754779197847983448
    s21_decimal decimal_check = {
        {0x55555558, 0x55555555, 0x55555555, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 8
    s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -8
    s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.9999999999999999999999999999
    s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 26409387504754779197847983442
    s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x55555555, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.9999999999999999999999999999
    s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -26409387504754779197847983442
    s21_decimal decimal_check = {
        {0x55555552, 0x55555555, 0x55555555, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.7922816251426433759354395034
    s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
    // 20923672451288935879452631411
    s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.7922816251426433759354395034
    s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
    // -20923672451288935879452631411
    s21_decimal decimal_check = {
        {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 792281625142643.37593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -792281625142643.37593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.0000000000000025
    s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
    // 66023468761886.947994619958612
    s21_decimal decimal_check = {{0x55555554, 0x55555555, 0xD5555555, 0xF0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.0000000000000025
    s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
    // -66023468761886.947994619958612
    s21_decimal decimal_check = {
        {0x55555554, 0x55555555, 0xD5555555, 0x800F0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.0000000000000005
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
    // 13204693752377.389598923991722
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0xF0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.0000000000000005
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
    // -13204693752377.389598923991722
    s21_decimal decimal_check = {
        {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x800F0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.0000000000000000000000000000
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.0000000000000000000000000000
    s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.0000000000000000000000000001
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
    // 2.6409387504754779197847983445
    s21_decimal decimal_check = {
        {0x55555555, 0x55555555, 0x55555555, 0x1C0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.0000000000000000000000000001
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
    // -2.6409387504754779197847983445
    s21_decimal decimal_check = {
        {0x55555555, 0x55555555, 0x55555555, 0x801C0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 0.0000000000000000000000000010
    s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
    // 26.409387504754779197847983445
    s21_decimal decimal_check = {
        {0x55555555, 0x55555555, 0x55555555, 0x1B0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -0.0000000000000000000000000010
    s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
    // -26.409387504754779197847983445
    s21_decimal decimal_check = {
        {0x55555555, 0x55555555, 0x55555555, 0x801B0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 400435217312910.10886274103770
    s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -400435217312910.10886274103770
    s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -57476540395758265626.742442133
    s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 57476540395758265626.742442133
    s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -7055.820576069728775806815669
    s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // 26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 7055.820576069728775806815669
    s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 26409387504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 26409387498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 6148914691236517205
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -6148914691236517205
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 6148914689804861440
    s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -6148914689804861440
    s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 1431655765
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -1431655765
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 26409387.504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387.504754779197847983445
    s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 26409387.498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387.498605864508043122005
    s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 26409387
    s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387
    s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 1.9999999999999999999999999000
    s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
    // -52818775009509558395695964249
    s21_decimal decimal_check = {
        {0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -1.9999999999999999999999999000
    s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
    // 52818775009509558395695964249
    s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 1
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
    // -26409387504754779197847983445
    s21_decimal decimal_check = {
        {0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -1
    s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
    // 26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 0.5
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
    // -13204693752377389598923991722
    s21_decimal decimal_check = {
        {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -0.5
    s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
    // 13204693752377389598923991722
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 0.4999999999999999999999999999
    s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // -13204693752377389598923991720
    s21_decimal decimal_check = {
        {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -0.4999999999999999999999999999
    s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // 13204693752377389598923991720
    s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 0.5000000000000000000000000001
    s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // -13204693752377389598923991725
    s21_decimal decimal_check = {
        {0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -0.5000000000000000000000000001
    s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // 13204693752377389598923991725
    s21_decimal decimal_check = {{0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 1.0000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // -26409387504754779197847983448
    s21_decimal decimal_check = {
        {0x55555558, 0x55555555, 0x55555555, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -1.0000000000000000000000000001
    s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // 26409387504754779197847983448
    s21_decimal decimal_check = {{0x55555558, 0x55555555, 0x55555555, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 8
    s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -8
    s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 0.9999999999999999999999999999
    s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // -26409387504754779197847983442
    s21_decimal decimal_check = {
        {0x55555552, 0x55555555, 0x55555555, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -0.9999999999999999999999999999
    s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // 26409387504754779197847983442
    s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x55555555, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -7.9228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 0.7922816251426433759354395034
    s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
    // -20923672451288935879452631411
    s21_decimal decimal_check = {
        {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -0.7922816251426433759354395034
    s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
    // 20923672451288935879452631411
    s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};

    test_mul(decimal1, decimal2, decimal_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 792281625142643.37593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // overflow
    int code_check = 2;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -792281625142643.37593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // overflow
    int code_check = 1;

    test_mul_fail1(decimal1, decimal2, code_check);
  }

  {
    // -26409387504754779197847983445
    s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 0.0000000000000025
    s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
    // -66023468761886.947994619958612
    s21_decimal decimal_check = {
        {0x55555554, 0x55555555, 0xD5555555, 0x800F0000}};

    test_mul(decimal1, decimal2, decimal_check);
  }
}
END_TEST

START_TEST(test_sub) {
  {
    int num1 = -10;
    int num2 = -10;
    int dif_int = 0;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_sub(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, dif_int);
  }

  {
    int num1 = 10;
    int num2 = 20;
    int dif_int = -10;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_sub(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, dif_int);
  }
  {
    int num1 = -10;
    int num2 = 20;
    int dif_int = -30;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_sub(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, dif_int);
  }
  {  // 1045
    s21_decimal src1, src2, origin;
    // src1 = 4;
    // src2 = 97623323;

    src1.bits[0] = 0b00000000000000000000000000000100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;

    src2.bits[0] = 0b00000101110100011001110100011011;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_sub(src1, src2, &result);

    origin.bits[0] = 0b00000101110100011001110100010111;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 1331
    s21_decimal src1, src2, origin;
    // src1 = 12345677.987654345678987654346;
    // 12345677.987654345678987654346
    // src2 = 87654323456.9876545678987653;
    // 87654323456.9876545678987653
    // printf("\ns21_subTest19 s21_subTest19 s21_subTest19\n\n");

    src1.bits[0] = 0b10010001000010101111010011001010;
    src1.bits[1] = 0b11000000010001011101010111110010;
    src1.bits[2] = 0b00100111111001000001101100000000;
    src1.bits[3] = 0b00000000000101010000000000000000;

    src2.bits[0] = 0b00010001110011011101000110000101;
    src2.bits[1] = 0b11110101101111000110111111000000;
    src2.bits[2] = 0b00000010110101010000111100111111;
    src2.bits[3] = 0b00000000000100000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_sub(src1, src2, &result);
    // 87641977779.00000022221977764 exp 17

    origin.bits[0] = 0b10010010000001100111100010100100;
    origin.bits[1] = 0b10001011011010100100100011011111;
    origin.bits[2] = 0b00011100010100011001001100010001;
    origin.bits[3] = 0b10000000000100010000000000000000;
    // print_2(&src1);
    // print_2(&src2);
    // print_2(&result);
    // print_2(&origin);
    // 87641977779.00000022221977765 exp 17
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
}
END_TEST

START_TEST(test_is_equal) {
  {
    int num1 = 0;
    int num2 = 0;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
  {
    int num1 = -3;
    int num2 = -3;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
  {
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(0, &dec1);
    s21_from_int_to_decimal(0, &dec2);
    dec1.bits[3] = 0;
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
  }

  {
    s21_decimal dec1 = {{0, 0, 0, 0x80000000}}, dec2 = {{0, 0, 0, 0}};
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
  }
}
END_TEST

START_TEST(test_is_less) {
  {
    int num1 = 3;
    int num2 = 9;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_less(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
  {
    int num1 = -3;
    int num2 = -3;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_less(dec1, dec2);
    ck_assert_int_eq(res, 0);
  }

  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2
  ck_assert_int_eq(s21_is_less(dec5, dec6), 0);
  ck_assert_int_eq(s21_is_less(dec6, dec5), 1);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(dec7, dec8), 1);
  ck_assert_int_eq(s21_is_less(dec8, dec7), 0);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less(dec2, dec1), 1);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(s21_is_less(dec3, dec4), 1);
  ck_assert_int_eq(s21_is_less(dec4, dec3), 0);

  s21_decimal dec9 = {{12345, 0, 0, 0}};
  s21_decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec9, dec10), 0);
  ck_assert_int_eq(s21_is_less(dec10, dec9), 0);

  s21_decimal dec11 = {{0, 0, 0, 0}};
  s21_decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec11, dec12), 0);
  ck_assert_int_eq(s21_is_less(dec12, dec11), 0);
}
END_TEST

START_TEST(test_is_greater_or_equal) {
  {
    int num1 = 2;
    int num2 = 1;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_greater_or_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
  {
    int num1 = 0;
    int num2 = 0;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_greater_or_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
  {
    int num1 = 3;
    int num2 = 9;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_greater_or_equal(dec1, dec2);
    ck_assert_int_eq(res, 0);
  }
  {
    int num1 = -3;
    int num2 = -3;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_greater_or_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
  {
    int num1 = 10;
    int num2 = 3;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_greater_or_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
}
END_TEST

START_TEST(test_is_not_equal) {
  {
    int num1 = 0;
    int num2 = 0;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_not_equal(dec1, dec2);
    ck_assert_int_eq(res, 0);
  }
  {
    int num1 = 3;
    int num2 = 9;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_not_equal(dec1, dec2);
    ck_assert_int_eq(res, 1);
  }
  {
    int num1 = -3;
    int num2 = -3;
    s21_decimal dec1, dec2;
    s21_from_int_to_decimal(num1, &dec1);
    s21_from_int_to_decimal(num2, &dec2);
    int res = s21_is_not_equal(dec1, dec2);
    ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(test_floor) {
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b10010011111100000001110001010010;
    dec1.bits[1] = 0b00000000000000000000000100100000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111011;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b00000000000000000000000010100101;
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000010000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0x93FFFC52;  // 2483027.026
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000000110000000000000000;  // 3
    s21_decimal result;
    result.bits[0] = 0x25E353;  // 2483027
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }

  {
    s21_decimal dec1;
    dec1.bits[0] = 0x93FFFC53;  // 2483027.027
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0x80030000;  // 3
    s21_decimal result;
    result.bits[0] = 0x25E354;  // 2483028
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0x80000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }

  {
    s21_decimal dec1;

    dec1.bits[0] = 0b00001111111111111111111111111111;
    dec1.bits[1] = 0b00111110001001010000001001100001;
    dec1.bits[2] = 0b00100000010011111100111001011110;
    dec1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b10100111011000111111111111111111;
    result.bits[1] = 0b00001101111000001011011010110011;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b00001111111111111111111111111111;
    dec1.bits[1] = 0b00111110001001010000001001100001;
    dec1.bits[2] = 0b00100000010011111100111001011110;
    dec1.bits[3] = 0b10000000000010100000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b10100111011001000000000000000000;
    result.bits[1] = 0b00001101111000001011011010110011;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0xBD278452;  // 3173483602
    dec1.bits[1] = 0x1C;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b10000000000010010000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111100;  // 124
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b10010011111100000001110001010010;
    dec1.bits[1] = 0b00000000000000000000000100100000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111011;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b01010101001110101110101110110001;
    dec1.bits[1] = 0b00001101101101001101101001011111;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b10000000000100100000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000001;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b01010101001110101110101110110001;
    dec1.bits[1] = 0b00001101101101001101101001011111;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000100100000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b10010111011100111001111111111111;
    dec1.bits[1] = 0b00111100000010000011000110001101;
    dec1.bits[2] = 0b00000000000000000000000000000001;
    dec1.bits[3] = 0b00000000000001110000000000000000;
    s21_decimal result;
    s21_floor(dec1, &result);
    s21_decimal result_origin;
    result_origin.bits[3] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0b00000000000000000000001000010010;
    result_origin.bits[0] = 0b00110110101101101000110000111111;
    ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
  }

  {  // 7130
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = 2;

    src1.bits[0] = 0b00000000000000000000000000000010;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000010;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7151
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = 3.5;

    src1.bits[0] = 0b00000000000000000000000000100011;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000010000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000011;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7172
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = -3.5;

    src1.bits[0] = 0b00000000000000000000000000100011;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000010000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000100;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7193
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = 0;

    src1.bits[0] = 0b00000000000000000000000000000000;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000000;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7214
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = -1.2;

    src1.bits[0] = 0b00000000000000000000000000001100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000010000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000010;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7235
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = -545454512454545.35265454545645;

    src1.bits[0] = 0b10000010111000100101101011101101;
    src1.bits[1] = 0b11111001111010000010010110101101;
    src1.bits[2] = 0b10110000001111101111000010010100;
    src1.bits[3] = 0b10000000000011100000000000000000;
    origin.bits[0] = 0b10000110011101001011101110010010;
    origin.bits[1] = 0b00000000000000011111000000010110;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7256
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = -5.492654545456454545645464;

    src1.bits[0] = 0b00000111100110110001111110011000;
    src1.bits[1] = 0b01100110010010001001000110100011;
    src1.bits[2] = 0b00000000000001001000101100011101;
    src1.bits[3] = 0b10000000000110000000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000110;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7277
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = 7961327845421.879754123131254;

    src1.bits[0] = 0b01001110111001000011100101110110;
    src1.bits[1] = 0b01001011001101011010000111011001;
    src1.bits[2] = 0b00011001101110010111010010111111;
    src1.bits[3] = 0b00000000000011110000000000000000;
    origin.bits[0] = 0b10100100000111100100000000101101;
    origin.bits[1] = 0b00000000000000000000011100111101;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7298
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = -12345677.187654345678987654346;

    src1.bits[0] = 0b01111000100010101111010011001010;
    src1.bits[1] = 0b01100010000010101110010010000111;
    src1.bits[2] = 0b00100111111001000001101011010101;
    src1.bits[3] = 0b10000000000101010000000000000000;

    origin.bits[0] = 0b00000000101111000110000101001110;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7319
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = 2.1986531268974139743;

    src1.bits[0] = 0b00010010001110001101100101011111;
    src1.bits[1] = 0b00110001000111111101100110110011;
    src1.bits[2] = 0b00000000000000000000000000000001;
    src1.bits[3] = 0b00000000000100110000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000010;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 7340
    s21_decimal src1, origin, result = {{0, 0, 0, 0}};
    // src1 = 1;

    src1.bits[0] = 0b00000000000000000000000000000001;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    origin.bits[0] = 0b00000000000000000000000000000001;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    s21_floor(src1, &result);
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
}
END_TEST

START_TEST(test_round1) {
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b10010011111100000001110001010010;
    dec1.bits[1] = 0b00000000000000000000000100100000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111100;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b00000000000000000000000010100101;  // -16.5
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b10000000000000010000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000010000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b11111111111111111111111111111111;  // 18014398509481.983
    dec1.bits[1] = 0b00000000001111111111111111111111;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000000110000000000000000;
    s21_decimal result;

    result.bits[0] = 0b01001101110100101111000110101001;  // 18014398509481
    result.bits[1] = 0b00000000000000000001000001100010;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b00000000000011110111001001110100;  // -10123.40
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b10000000000000110000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000001111110100;  // -1012
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b10000000000000000000001111110100;  // 112590205.4327284
    dec1.bits[1] = 0b00000000000001000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b10000000000001110000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000110101101011111110101111101;  // 112590205
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result;
    result.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b01100011000011111111111111111111;
    dec1.bits[1] = 0b01101011110001110101111000101101;
    dec1.bits[2] = 0b00000000000000000000000000000101;
    dec1.bits[3] = 0b10000000000010100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b01010100000010111110010000000000;
    result.bits[1] = 0b00000000000000000000000000000010;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b01010101001110101110101110110001;
    dec1.bits[1] = 0b00001101101101001101101001011111;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b10000000000100100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000001;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b10010011111100000001110001010010;
    dec1.bits[1] = 0b00000000000000000000000100100000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111100;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b11001101110001110111110001000000;
    dec1.bits[1] = 0b00111110001001010000001001100000;
    dec1.bits[2] = 0b00100000010011111100111001011110;
    dec1.bits[3] = 0b10000000000001000000000000000000;
    s21_decimal result;
    result.bits[0] = 0b10100000111111100100111000000100;
    result.bits[1] = 0b00011011110011101100110011101101;
    result.bits[2] = 0b00000000000000001101001111000010;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b10100000111111100100111000000100;
    dec1.bits[1] = 0b00011011110011101100110011101101;
    dec1.bits[2] = 0b00000000000000001101001111000010;
    dec1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b10100000111111100100111000000100;
    result.bits[1] = 0b00011011110011101100110011101101;
    result.bits[2] = 0b00000000000000001101001111000010;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b10010111011100111001111111111111;
    dec1.bits[1] = 0b00111100000010000011000110001101;
    dec1.bits[2] = 0b00000000000000000000000000000001;
    dec1.bits[3] = 0b00000000000001110000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b00110110101101101000110001000000;
    result.bits[1] = 0b00000000000000000000001000010010;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b10010111011100111001111111111111;
    dec1.bits[1] = 0b00111100000010000011000110001101;
    dec1.bits[2] = 0b00000000000000000000000000000001;
    dec1.bits[3] = 0b10000000000001110000000000000000;
    s21_decimal res1;
    s21_round(dec1, &res1);
    s21_decimal result;
    result.bits[0] = 0b00110110101101101000110001000000;
    result.bits[1] = 0b00000000000000000000001000010010;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;

    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {  // 8053
    s21_decimal src1, origin;
    // src1 = 2;

    src1.bits[0] = 2;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 2;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8074
    s21_decimal src1, origin;
    // src1 = 3.5;

    src1.bits[0] = 0b00000000000000000000000000100011;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000100;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8095
    s21_decimal src1, origin;
    // src1 = -3.5;

    src1.bits[0] = 0b00000000000000000000000000100011;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000100;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8116
    s21_decimal src1, origin;
    // src1 = 0;

    src1.bits[0] = 0b00000000000000000000000000000000;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000000;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8137
    s21_decimal src1, origin;
    // src1 = -9878798789;

    src1.bits[0] = 0b01001100110100101000000111000101;
    src1.bits[1] = 0b00000000000000000000000000000010;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b01001100110100101000000111000101;
    origin.bits[1] = 0b00000000000000000000000000000010;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8158
    s21_decimal src1, origin;
    // src1 = -545454512454545.35265;

    src1.bits[0] = 0b11011110101101001010101001100001;
    src1.bits[1] = 0b11110100111110000101111011101001;
    src1.bits[2] = 0b00000000000000000000000000000010;
    src1.bits[3] = 0b10000000000001010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b10000110011101001011101110010001;
    origin.bits[1] = 0b00000000000000011111000000010110;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8179
    s21_decimal src1, origin;
    // src1 = -5.492654545456454545645464;

    src1.bits[0] = 0b00000111100110110001111110011000;
    src1.bits[1] = 0b01100110010010001001000110100011;
    src1.bits[2] = 0b00000000000001001000101100011101;
    src1.bits[3] = 0b10000000000110000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000101;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8200
    s21_decimal src1, origin;
    // src1 = 7961327845421.879754123131254;

    src1.bits[0] = 0b01001110111001000011100101110110;
    src1.bits[1] = 0b01001011001101011010000111011001;
    src1.bits[2] = 0b00011001101110010111010010111111;
    src1.bits[3] = 0b00000000000011110000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b10100100000111100100000000101110;
    origin.bits[1] = 0b00000000000000000000011100111101;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8221
    s21_decimal src1, origin;
    // src1 = -12345677.187654345678987654346;

    src1.bits[0] = 0b01111000100010101111010011001010;
    src1.bits[1] = 0b01100010000010101110010010000111;
    src1.bits[2] = 0b00100111111001000001101011010101;
    src1.bits[3] = 0b10000000000101010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000101111000110000101001101;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8242
    s21_decimal src1, origin;
    // src1 = 2.5986531268974139743;

    src1.bits[0] = 0xAFC8D95F;
    src1.bits[1] = 0x68A2B481;
    src1.bits[2] = 0x1;
    src1.bits[3] = 0b00000000000100110000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000011;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8263
    s21_decimal src1, origin;
    // src1 = 1;

    src1.bits[0] = 0b00000000000000000000000000000001;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000001;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8284
    s21_decimal src1, origin;
    // src1 = 1.1;

    src1.bits[0] = 0b00000000000000000000000000001011;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000001;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8305
    s21_decimal src1, origin;
    // src1 = -1.1;

    src1.bits[0] = 0b00000000000000000000000000001011;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000001;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8326
    s21_decimal src1, origin;
    // src1 = 24.56;

    src1.bits[0] = 0b00000000000000000000100110011000;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000100000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000011001;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 8347
    s21_decimal src1, origin;
    // src1 = -2.124;

    src1.bits[0] = 0b00000000000000000000100001001100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000110000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 0b00000000000000000000000000000010;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }

  {
    s21_decimal src1, origin;

    src1.bits[0] = 25;
    src1.bits[1] = 0x0;
    src1.bits[2] = 0x0;
    src1.bits[3] = 0x00010000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 2;
    origin.bits[1] = 0x0;
    origin.bits[2] = 0x0;
    origin.bits[3] = 0x0;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {
    s21_decimal src1, origin;

    src1.bits[0] = 29;
    src1.bits[1] = 0x0;
    src1.bits[2] = 0x0;
    src1.bits[3] = 0x00010000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 3;
    origin.bits[1] = 0x0;
    origin.bits[2] = 0x0;
    origin.bits[3] = 0x0;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {
    s21_decimal src1, origin;

    src1.bits[0] = 21;
    src1.bits[1] = 0x0;
    src1.bits[2] = 0x0;
    src1.bits[3] = 0x00010000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 2;
    origin.bits[1] = 0x0;
    origin.bits[2] = 0x0;
    origin.bits[3] = 0x0;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {
    s21_decimal src1, origin;

    src1.bits[0] = 19;
    src1.bits[1] = 0x0;
    src1.bits[2] = 0x0;
    src1.bits[3] = 0x00010000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 2;
    origin.bits[1] = 0x0;
    origin.bits[2] = 0x0;
    origin.bits[3] = 0x0;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {
    s21_decimal src1, origin;

    src1.bits[0] = 15;
    src1.bits[1] = 0x0;
    src1.bits[2] = 0x0;
    src1.bits[3] = 0x00010000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 2;
    origin.bits[1] = 0x0;
    origin.bits[2] = 0x0;
    origin.bits[3] = 0x0;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {
    s21_decimal src1, origin;

    src1.bits[0] = 25;
    src1.bits[1] = 0x0;
    src1.bits[2] = 0x0;
    src1.bits[3] = 0x80010000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_round(src1, &result);
    origin.bits[0] = 2;
    origin.bits[1] = 0x0;
    origin.bits[2] = 0x0;
    origin.bits[3] = 0x80000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }

  {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

    int code = s21_round(decimal, NULL);

    ck_assert_int_eq(code, 1);
  }

  {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }

  {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }

  {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }

  {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }

  {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal result;

    int code = s21_round(decimal, &result);

    ck_assert_int_eq(code, 1);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {
        {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395034
    s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395034
    s21_decimal decimal_check = {
        {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439503
    s21_decimal decimal_check = {
        {0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543950
    s21_decimal decimal_check = {
        {0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935440
    s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935440
    s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593544
    s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593544
    s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337594
    s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337594
    s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643376
    s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643376
    s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264338
    s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264338
    s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426434
    s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426434
    s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228163
    s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228163
    s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792282
    s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792282
    s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7923
    s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7923
    s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950334
    s21_decimal decimal_check = {
        {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395033
    s21_decimal decimal_check = {
        {0x99999999, 0x99999999, 0x19999999, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439503
    s21_decimal decimal_check = {
        {0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543950
    s21_decimal decimal_check = {
        {0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935440
    s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935440
    s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593544
    s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593544
    s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337594
    s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337594
    s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643376
    s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643376
    s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264338
    s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264338
    s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426434
    s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426434
    s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }

  {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }

  {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228163
    s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228163
    s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792282
    s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792282
    s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7923
    s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7923
    s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558395695966890
    s21_decimal decimal_check = {
        {0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839569596689
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x11111111, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839569596689
    s21_decimal decimal_check = {
        {0x11111111, 0x11111111, 0x11111111, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950956
    s21_decimal decimal_check = {{0xF030F9AC, 0x12C3D6, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950956
    s21_decimal decimal_check = {{0xF030F9AC, 0x12C3D6, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950956
    s21_decimal decimal_check = {{0xF030F9AC, 0x12C3D6, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950956
    s21_decimal decimal_check = {{0xF030F9AC, 0x12C3D6, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721173
    s21_decimal decimal_check = {{0xF01E35D5, 0x12C3D6, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721173
    s21_decimal decimal_check = {{0xF01E35D5, 0x12C3D6, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721173
    s21_decimal decimal_check = {{0xF01E35D5, 0x12C3D6, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721173
    s21_decimal decimal_check = {{0xF01E35D5, 0x12C3D6, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978294
    s21_decimal decimal_check = {{0x7547FF6, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978294
    s21_decimal decimal_check = {{0x7547FF6, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978294
    s21_decimal decimal_check = {{0x7547FF6, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978294
    s21_decimal decimal_check = {{0x7547FF6, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    // 2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};
    // -2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    // 286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    // -286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    // 286331
    s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    // -286331
    s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779197847983445
    s21_decimal decimal_check = {
        {0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919784798344
    s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919784798344
    s21_decimal decimal_check = {
        {0x88888888, 0x88888888, 0x8888888, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475478
    s21_decimal decimal_check = {{0x78187CD6, 0x961EB, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475478
    s21_decimal decimal_check = {{0x78187CD6, 0x961EB, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919641632768
    s21_decimal decimal_check = {{0x80000000, 0x88888888, 0x8888888, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919641632768
    s21_decimal decimal_check = {
        {0x80000000, 0x88888888, 0x8888888, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475478
    s21_decimal decimal_check = {{0x78187CD6, 0x961EB, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475478
    s21_decimal decimal_check = {{0x78187CD6, 0x961EB, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};
    // 26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450804312200
    s21_decimal decimal_check = {{0x8888888, 0x80000000, 0x8888888, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450804312200
    s21_decimal decimal_check = {
        {0x8888888, 0x80000000, 0x8888888, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};
    // 26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
    // 6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    // -6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};
    // 614891469123651720
    s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};
    // -614891469123651720
    s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    // 6148915
    s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    // -6148915
    s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
    // 6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
    // -6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
    // 614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
    // -614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    // 6148915
    s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    // -6148915
    s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    // 1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    // -1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    // 143165576
    s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    // -143165576
    s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    // 143166
    s21_decimal decimal_check = {{0x22F3E, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    // -143166
    s21_decimal decimal_check = {{0x22F3E, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
    // 18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
    // -18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
    // -1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000}};
    // 184467440780
    s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80080000}};
    // -184467440780
    s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
    // 18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
    // -18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
    // -1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x90000}};
    // 18446744078
    s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80090000}};
    // -18446744078
    s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
    // 18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
    // -18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
    // 1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
    // -1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xA0000}};
    // 1844674407
    s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800A0000}};
    // -1844674407
    s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
    // 18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
    // -18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
    // 1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
    // -1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xB0000}};
    // 184467441
    s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800B0000}};
    // -184467441
    s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
    // 4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
    // -4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    // 429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    // -429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    // 42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    // -42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    // 429497
    s21_decimal decimal_check = {{0x68DB9, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    // -429497
    s21_decimal decimal_check = {{0x68DB9, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    // 43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    // -43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
    // 4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
    // -4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    // 429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    // -429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    // 42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    // -42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    // 4294967
    s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    // -4294967
    s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    // 43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    // -43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540835774234624
    s21_decimal decimal_check = {
        {0x80000000, 0x80000000, 0x80000000, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083577423462
    s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083577423462
    s21_decimal decimal_check = {
        {0xA6666666, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
    // 39614081266356
    s21_decimal decimal_check = {{0x5F3DF2B4, 0x2407, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
    // -39614081266356
    s21_decimal decimal_check = {{0x5F3DF2B4, 0x2407, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083362675098
    s21_decimal decimal_check = {{0x9999999A, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083362675098
    s21_decimal decimal_check = {
        {0x9999999A, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0xD0000}};
    // 3961408126635554
    s21_decimal decimal_check = {{0x3432CE22, 0xE12E1, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x800D0000}};
    // -3961408126635554
    s21_decimal decimal_check = {{0x3432CE22, 0xE12E1, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};
    // 39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879891945882
    s21_decimal decimal_check = {{0xD999999A, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879891945882
    s21_decimal decimal_check = {
        {0xD999999A, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0xC0000}};
    // 39614081257132169
    s21_decimal decimal_check = {{0x96F5089, 0x8CBCCC, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x800C0000}};
    // -39614081257132169
    s21_decimal decimal_check = {{0x96F5089, 0x8CBCCC, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};
    // 39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879677197517
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879677197517
    s21_decimal decimal_check = {
        {0xCCCCCCCD, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0xB0000}};
    // 396140812571321688
    s21_decimal decimal_check = {{0x5E592558, 0x57F5FF8, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x800B0000}};
    // -396140812571321688
    s21_decimal decimal_check = {{0x5E592558, 0x57F5FF8, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};
    // 9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};
    // -9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};
    // 922337203900225946
    s21_decimal decimal_check = {{0xD999999A, 0xCCCCCCC, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};
    // -922337203900225946
    s21_decimal decimal_check = {{0xD999999A, 0xCCCCCCC, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x70000}};
    // 922337203900
    s21_decimal decimal_check = {{0xBF94D6BC, 0xD6, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80070000}};
    // -922337203900
    s21_decimal decimal_check = {{0xBF94D6BC, 0xD6, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};
    // 9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};
    // -9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};
    // 922337203685477581
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCC, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};
    // -922337203685477581
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCC, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000}};
    // 92233720369
    s21_decimal decimal_check = {{0x798EE231, 0x15, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80080000}};
    // -92233720369
    s21_decimal decimal_check = {{0x798EE231, 0x15, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    // 2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    // -2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    // 214748365
    s21_decimal decimal_check = {{0xCCCCCCD, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    // -214748365
    s21_decimal decimal_check = {{0xCCCCCCD, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    // 21474836
    s21_decimal decimal_check = {{0x147AE14, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    // -21474836
    s21_decimal decimal_check = {{0x147AE14, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    // 214748
    s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    // -214748
    s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    // 21
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    // -21
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};
    // 156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269530542694
    s21_decimal decimal_check = {{0x99A68266, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269530542694
    s21_decimal decimal_check = {{0x99A68266, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    // 1560648
    s21_decimal decimal_check = {{0x17D048, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    // -1560648
    s21_decimal decimal_check = {{0x17D048, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};
    // 156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269529696666
    s21_decimal decimal_check = {{0x9999999A, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269529696666
    s21_decimal decimal_check = {{0x9999999A, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x40000}};
    // 15606476756221269529697
    s21_decimal decimal_check = {{0x27525461, 0x75F7320, 0x34E, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80040000}};
    // -15606476756221269529697
    s21_decimal decimal_check = {{0x27525461, 0x75F7320, 0x34E, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};
    // 156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};
    // 15606476752587603503068570
    s21_decimal decimal_check = {{0xCCD9B59A, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603503068570
    s21_decimal decimal_check = {{0xCCD9B59A, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0xB0000}};
    // 1560647675258760
    s21_decimal decimal_check = {{0x9A4DA788, 0x58B66, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x800B0000}};
    // -1560647675258760
    s21_decimal decimal_check = {{0x9A4DA788, 0x58B66, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};
    // 156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};
    // 15606476752587603502222541
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603502222541
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x130000}};
    // 15606477
    s21_decimal decimal_check = {{0xEE22CD, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80130000}};
    // -15606477
    s21_decimal decimal_check = {{0xEE22CD, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};
    // 36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};
    // -36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};
    // 3633666028320154
    s21_decimal decimal_check = {{0xCCD9B59A, 0xCE8CC, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};
    // -3633666028320154
    s21_decimal decimal_check = {{0xCCD9B59A, 0xCE8CC, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    // 363366603
    s21_decimal decimal_check = {{0x15A888CB, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    // -363366603
    s21_decimal decimal_check = {{0x15A888CB, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};
    // 36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};
    // -36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};
    // 3633666027474125
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCE8CC, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};
    // -3633666027474125
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCE8CC, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x20000}};
    // 363366602747412
    s21_decimal decimal_check = {{0xE147AE14, 0x14A7A, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80020000}};
    // -363366602747412
    s21_decimal decimal_check = {{0xE147AE14, 0x14A7A, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    // 363366603
    s21_decimal decimal_check = {{0x15A888CB, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    // -363366603
    s21_decimal decimal_check = {{0x15A888CB, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    // 36
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    // -36
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    // 8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    // -8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    // 846029
    s21_decimal decimal_check = {{0xCE8CD, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    // -846029
    s21_decimal decimal_check = {{0xCE8CD, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    // 84603
    s21_decimal decimal_check = {{0x14A7B, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    // -84603
    s21_decimal decimal_check = {{0x14A7B, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    // 8460
    s21_decimal decimal_check = {{0x210C, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    // -8460
    s21_decimal decimal_check = {{0x210C, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    // 85
    s21_decimal decimal_check = {{0x55, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    // -85
    s21_decimal decimal_check = {{0x55, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {
        {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395034
    s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395034
    s21_decimal decimal_check = {
        {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433758924898304
    s21_decimal decimal_check = {{0x80000000, 0x99999999, 0x19999999, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433758924898304
    s21_decimal decimal_check = {
        {0x80000000, 0x99999999, 0x19999999, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759352412936602
    s21_decimal decimal_check = {{0x1999999A, 0x80000000, 0x19999999, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759352412936602
    s21_decimal decimal_check = {
        {0x1999999A, 0x80000000, 0x19999999, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x110000}};
    // 792281624958
    s21_decimal decimal_check = {{0x77AA317E, 0xB8, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80110000}};
    // -792281624958
    s21_decimal decimal_check = {{0x77AA317E, 0xB8, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x120000}};
    // 79228162496
    s21_decimal decimal_check = {{0x725DD1C0, 0x12, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80120000}};
    // -79228162496
    s21_decimal decimal_check = {{0x725DD1C0, 0x12, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744073709552
    s21_decimal decimal_check = {{0x4BC6A7F0, 0x418937, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744073709552
    s21_decimal decimal_check = {{0x4BC6A7F0, 0x418937, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    // 184467441
    s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    // -184467441
    s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744069414584
    s21_decimal decimal_check = {{0x4B851EB8, 0x418937, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744069414584
    s21_decimal decimal_check = {{0x4B851EB8, 0x418937, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x90000}};
    // 18446744069
    s21_decimal decimal_check = {{0x4B82FA05, 0x4, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80090000}};
    // -18446744069
    s21_decimal decimal_check = {{0x4B82FA05, 0x4, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
    // 4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
    // -4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    // 429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    // -429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    // 42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    // -42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    // 42950
    s21_decimal decimal_check = {{0xA7C6, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    // -42950
    s21_decimal decimal_check = {{0xA7C6, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    // 43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    // -43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    // 12
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    // -12
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    // 123
    s21_decimal decimal_check = {{0x7B, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    // -123
    s21_decimal decimal_check = {{0x7B, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    // 1234
    s21_decimal decimal_check = {{0x4D2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    // -1234
    s21_decimal decimal_check = {{0x4D2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    // 12345
    s21_decimal decimal_check = {{0x3039, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    // -12345
    s21_decimal decimal_check = {{0x3039, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    // 123456
    s21_decimal decimal_check = {{0x1E240, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    // -123456
    s21_decimal decimal_check = {{0x1E240, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    // 1234567
    s21_decimal decimal_check = {{0x12D687, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    // -1234567
    s21_decimal decimal_check = {{0x12D687, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    // 1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    // -1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
    // 12345678901234
    s21_decimal decimal_check = {{0x73CE2FF2, 0xB3A, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
    // -12345678901234
    s21_decimal decimal_check = {{0x73CE2FF2, 0xB3A, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    // -99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    // 10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    // -10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    // 100
    s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    // -100
    s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    // 1000
    s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    // -1000
    s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    // 10000
    s21_decimal decimal_check = {{0x2710, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    // -10000
    s21_decimal decimal_check = {{0x2710, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    // 100000
    s21_decimal decimal_check = {{0x186A0, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    // -100000
    s21_decimal decimal_check = {{0x186A0, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    // 1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    // -1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    // 10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    // -10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    // 100000000
    s21_decimal decimal_check = {{0x5F5E100, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    // -100000000
    s21_decimal decimal_check = {{0x5F5E100, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    // 1000000000
    s21_decimal decimal_check = {{0x3B9ACA00, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    // -1000000000
    s21_decimal decimal_check = {{0x3B9ACA00, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
    // 10000000000
    s21_decimal decimal_check = {{0x540BE400, 0x2, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
    // -10000000000
    s21_decimal decimal_check = {{0x540BE400, 0x2, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
  {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_round(decimal, decimal_check);
  }
  {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_round(decimal, decimal_check);
  }
}
END_TEST

START_TEST(test_truncate) {
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b00000000000000000000000011010011;  // 21.1
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000010101;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_int_eq(res1.bits[0], result.bits[0]);
    ck_assert_int_eq(res1.bits[1], result.bits[1]);
    ck_assert_int_eq(res1.bits[2], result.bits[2]);
    ck_assert_int_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] = 0b00000000000000000000000010100101;
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000010000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;
    dec1.bits[0] =
        0b11111111111111111111111111111111;  // 7922816251426433759354395033.5
    dec1.bits[1] = 0b11111111111111111111111111111111;
    dec1.bits[2] = 0b11111111111111111111111111111111;
    dec1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal result;
    result.bits[0] = 0b10011001100110011001100110011001;
    result.bits[1] = 0b10011001100110011001100110011001;
    result.bits[2] = 0b00011001100110011001100110011001;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_int_eq(res1.bits[0], result.bits[0]);
    ck_assert_int_eq(res1.bits[1], result.bits[1]);
    ck_assert_int_eq(res1.bits[2], result.bits[2]);
    ck_assert_int_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[3] = 0x000A0000;
    dec1.bits[2] = 0x0;
    dec1.bits[1] = 0xFFFFFFFF;
    dec1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x0;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x6DF37F67;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[3] = 0b10000000000011000000000000000000;
    dec1.bits[2] = 0x0;
    dec1.bits[1] = 0xFFFFFFFF;
    dec1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0b10000000000000000000000000000000;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x1197998;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[3] = 0x80000000;
    dec1.bits[2] = 0x0;
    dec1.bits[1] = 0xFFFFFFFF;
    dec1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x80000000;
    result.bits[2] = 0x0;
    result.bits[1] = 0xFFFFFFFF;
    result.bits[0] = 0xFFFFFFFF;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b00000000000000000000000001101101;
    dec1.bits[1] = 0b00000000000011000110010101011011;
    dec1.bits[2] = 0b00000000000000000011000000111001;
    dec1.bits[3] = 0b00000000000011100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b10000111101111000001011000011110;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b11011110101001001000000010110110;
    dec1.bits[1] = 0b01011111101001011101111110100000;
    dec1.bits[2] = 0b00011111111010011010111101100000;
    dec1.bits[3] = 0b00000000000010010000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00110100101011011100000100111110;
    result.bits[1] = 0b10001001000100001000011110111001;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {
    s21_decimal dec1;

    dec1.bits[3] = 0x80090000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0xFFFFEA34;
    dec1.bits[0] = 0xFF837E4F;
    s21_decimal result;
    s21_truncate(dec1, &result);
    s21_decimal res1;

    res1.bits[3] = 0x80000000;
    res1.bits[2] = 0;
    res1.bits[1] = 0x4;
    res1.bits[0] = 0x4B829C70;
    ck_assert_int_eq(res1.bits[3], result.bits[3]);
    ck_assert_int_eq(res1.bits[2], result.bits[2]);
    ck_assert_int_eq(res1.bits[1], result.bits[1]);
    ck_assert_int_eq(res1.bits[0], result.bits[0]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b11010000101000110011000001101101;
    dec1.bits[1] = 0b00011111100110100110101101011000;
    dec1.bits[2] = 0;
    dec1.bits[3] = 0b00000000000010010000000000000000;
    s21_decimal result;
    s21_truncate(dec1, &result);
    s21_decimal result_origin;
    result_origin.bits[3] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b10000111101111000001011000011110;
    ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
  }
  {
    s21_decimal dec1;

    dec1.bits[0] = 0b01111000101001111011110011000110;
    dec1.bits[1] = 0b10011111111111001111101010000100;
    dec1.bits[2] = 0b00011111111010011010111101101101;
    dec1.bits[3] = 0b00000000000111000000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_truncate(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
  }
  {  // 6766
    s21_decimal src1, origin;
    // src1 = 2;

    src1.bits[0] = 0b00000000000000000000000000000010;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000000000000000000000000010;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6787
    s21_decimal src1, origin;
    // src1 = 3.5;

    src1.bits[0] = 0b00000000000000000000000000100011;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000000000000000000000000011;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6808
    s21_decimal src1, origin;
    // src1 = 0;

    src1.bits[0] = 0b00000000000000000000000000000000;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000000000000000000000000000;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6829
    s21_decimal src1, origin;
    // src1 = 0;

    src1.bits[0] = 0b00000000000000000000000000000000;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000000000000000000000000000;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6850
    s21_decimal src1, origin;
    // src1 = -9878798789;

    src1.bits[0] = 0b01001100110100101000000111000101;
    src1.bits[1] = 0b00000000000000000000000000000010;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b01001100110100101000000111000101;
    origin.bits[1] = 0b00000000000000000000000000000010;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6871
    s21_decimal src1, origin;
    // src1 = -545454512454545.35265454545645;

    src1.bits[0] = 0b10000010111000100101101011101101;
    src1.bits[1] = 0b11111001111010000010010110101101;
    src1.bits[2] = 0b10110000001111101111000010010100;
    src1.bits[3] = 0b10000000000011100000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b10000110011101001011101110010001;
    origin.bits[1] = 0b00000000000000011111000000010110;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6892
    s21_decimal src1, origin;
    // src1 = -5.492654545456454545645464;

    src1.bits[0] = 0b00000111100110110001111110011000;
    src1.bits[1] = 0b01100110010010001001000110100011;
    src1.bits[2] = 0b00000000000001001000101100011101;
    src1.bits[3] = 0b10000000000110000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000000000000000000000000101;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6913
    s21_decimal src1, origin;
    // src1 = 7961327845421.879754123131254;

    src1.bits[0] = 0b01001110111001000011100101110110;
    src1.bits[1] = 0b01001011001101011010000111011001;
    src1.bits[2] = 0b00011001101110010111010010111111;
    src1.bits[3] = 0b00000000000011110000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b10100100000111100100000000101101;
    origin.bits[1] = 0b00000000000000000000011100111101;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6934
    s21_decimal src1, origin;
    // src1 = -12345677.187654345678987654346;

    src1.bits[0] = 0b01111000100010101111010011001010;
    src1.bits[1] = 0b01100010000010101110010010000111;
    src1.bits[2] = 0b00100111111001000001101011010101;
    src1.bits[3] = 0b10000000000101010000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000101111000110000101001101;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6955
    s21_decimal src1, origin;
    // src1 = 2.5086531268974139743;

    src1.bits[0] = 0b01100101111011101101100101011111;
    src1.bits[1] = 0b01011100001001010100001101000110;
    src1.bits[2] = 0b00000000000000000000000000000001;
    src1.bits[3] = 0b00000000000100110000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000000000000000000000000010;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
  {  // 6976
    s21_decimal src1, origin;
    // src1 = 1;

    src1.bits[0] = 0b00000000000000000000000000000001;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result = {{0, 0, 0, 0}};
    s21_truncate(src1, &result);

    origin.bits[0] = 0b00000000000000000000000000000001;
    origin.bits[1] = 0b00000000000000000000000000000000;
    origin.bits[2] = 0b00000000000000000000000000000000;
    origin.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(origin.bits[3], result.bits[3]);
    ck_assert_int_eq(origin.bits[2], result.bits[2]);
    ck_assert_int_eq(origin.bits[1], result.bits[1]);
    ck_assert_int_eq(origin.bits[0], result.bits[0]);
  }
}
END_TEST

START_TEST(test_negate) {
  {
    int a = 15;
    int res_a = 0;
    s21_decimal src;
    s21_decimal res;
    s21_from_int_to_decimal(a, &src);
    s21_negate(src, &res);
    s21_from_decimal_to_int(res, &res_a);
    ck_assert_int_eq(-15, res_a);
  }
  {
    int a = -15;
    int res_a = 0;
    s21_decimal src;
    s21_decimal res;
    s21_from_int_to_decimal(a, &src);
    s21_negate(src, &res);
    s21_from_decimal_to_int(res, &res_a);
    ck_assert_int_eq(15, res_a);
  }
  {
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal etalon = {{0, 0, 0, ~(INT_MAX)}};
    int negate = s21_negate(b, &etalon);
    ck_assert_int_eq(negate, 0);
  }
  {
    s21_decimal a = {{1, 0, 0, 0}};
    s21_decimal etalon = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal a = {{1, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{1, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal etalon = {{100, 0, 0, ~(INT_MAX)}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal a = {{100, 0, 0, ~(INT_MAX)}};
    s21_decimal etalon = {{100, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal a = {{UINT_MAX, 0, 0, 0}};
    s21_decimal etalon = {{UINT_MAX, 0, 0, ~(INT_MAX)}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal etalon = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 0);
  }
  {
    s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal etalon = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(INT_MAX)}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(INT_MAX)}};
    s21_decimal etalon = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal* ptr_b = &b;
    int add = s21_negate(a, ptr_b);
    ck_assert_int_eq(add, 0);
    int equal = s21_is_equal(b, etalon);
    ck_assert_int_eq(equal, 1);
  }
  {
    s21_decimal val = {{2, 0, 0, 0}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_negate(val, &res));
  }
  {
    s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_negate(val, &res));
  }
  {
    s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_negate(val, &res));
  }
  {
    s21_decimal val = {0};
    s21_decimal res = {0};
    ck_assert_int_eq(0, s21_negate(val, &res));
  }
}
END_TEST

Suite* suite_s21_decimal(void) {
  Suite* s;
  TCase* tc_tests;

  s = suite_create("test_s21_decimal_suite");
  tc_tests = tcase_create("s21_decimal");

  tcase_add_test(tc_tests, test_add);
  tcase_add_test(tc_tests, test_from_decimal_to_int);
  tcase_add_test(tc_tests, test_from_int_to_decimal);
  tcase_add_test(tc_tests, test_mul1);
  tcase_add_test(tc_tests, test_sub);
  tcase_add_test(tc_tests, test_is_equal);
  tcase_add_test(tc_tests, test_is_less);
  tcase_add_test(tc_tests, test_is_greater_or_equal);
  tcase_add_test(tc_tests, test_is_not_equal);
  tcase_add_test(tc_tests, test_floor);
  tcase_add_test(tc_tests, test_round1);
  tcase_add_test(tc_tests, test_truncate);
  tcase_add_test(tc_tests, test_negate);

  suite_add_tcase(s, tc_tests);
  return s;
}

int main(void) {
  Suite* s = suite_s21_decimal();
  SRunner* runner = srunner_create(s);

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? 0 : 1;
}

void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
}

void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

void test_round(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_round(decimal, &result);
  int sign_check = decimal_check.bits[3] & MINUS;
  int sign_result = decimal.bits[3] & MINUS;

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}
