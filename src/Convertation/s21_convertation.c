#include "s21_convertation.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  // не работает с INT_MIN
  int result = CONV_OK;
  if (dst) {
    if (src < 0) {
      src = -src;
      set_sign(dst, '-');
    };
    dst->bits[LOW] = src;
  } else {
    result = CONV_ERR;
  }
  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  // обрезаем дробную часть
  int result = CONV_OK;
  if (src.bits[LOW] < INT_MAX && src.bits[LOW] > INT_MAX) {
    int sign = (check_bit(src, 127) == 1) ? -1 : 1;
    *dst = src.bits[LOW] * sign;
  } else {
    result = CONV_ERR;
  }
  return result;
  // ошибка если число выходит за пределы INT
}

void print_dec(s21_decimal dec) {
  printf("\n");
  printf("31%16s%14d 63%15s%15d 95%15s%15d 127%14s%18d\n", "LOW", 0, "MID", 32,
         "HIGH", 64, "SCALE", 96);

  for (int j = 0; j < 4; j++) {
    for (unsigned i = 1 << 31, k = 30; i > 0; i = i / 2, k--) {
      (dec.bits[j] & i) ? printf("1") : printf("0");
      if (j == 3 && (k == 15 || k == 23 || k == 30)) printf(" ");
    }
    j < 3 ? printf(" ") : printf("\n");
  }
}

unsigned int mask(unsigned int index) { return 1 << (index % 32); }

int check_bit(s21_decimal dec, unsigned int index) {
  return (dec.bits[POSITION] & mask(index)) != 0;
}

void unset_bit(s21_decimal *dec, unsigned int index) {
  dec->bits[POSITION] = dec->bits[POSITION] & ~(mask(index));
}

void set_bit(s21_decimal *dec, unsigned int index) {
  dec->bits[POSITION] = dec->bits[POSITION] | mask(index);
}

void switch_bit(s21_decimal *dec, unsigned int index) {
  dec->bits[POSITION] = dec->bits[POSITION] ^ mask(index);
}
void set_sign(s21_decimal *dec, char sign) {
  if (sign == '+') unset_bit(dec, 127);
  if (sign == '-') set_bit(dec, 127);
}

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//   if (src < 0) {
//     set_sign(dst, '-');
//     src = -src;
//   };
//   converter src2 = {src};
// }

int main(void) {
  int a = 100;
  int b = 0;
  printf("%d\n", b);
  char str[100] = "";
  s21_decimal dec = {0};
  print_dec(dec);
  s21_from_int_to_decimal(a, &dec);
  print_dec(dec);
  s21_from_decimal_to_int(dec, &b);
  printf("%d\n", b);
  return 0;
}
