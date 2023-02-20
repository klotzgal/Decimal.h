#include "s21_convertation.h"

/* функции, которые печатают*/
void print_bytes(unsigned char num) {
  for (unsigned char i = 1 << 7; i > 0; i = i / 2)
    (num & i) ? printf("1") : printf("0");
  printf("\n");
}

void print_32(unsigned int a) {
  printf("check bit\n");
  printf("%3s|%21s|%68s|\n", "sign", "exp", "mantiss");
  for (int i = 31; i >= 0; i--) {
    printf("%3d", i);
  }
  printf("\n");
  for (int i = 31; i >= 0; i--) {
    printf("%3d", checkbit32(a, i));
    if (i == 23) printf(" ");
  }
  printf("\n");
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

/* вспомогательные функции*/
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

// void switch_bit(s21_decimal *dec, unsigned int index) {
//   dec->bits[POSITION] = dec->bits[POSITION] ^ mask(index);
// }

void set_sign(s21_decimal *dec, char sign) {
  if (sign == '+') unset_bit(dec, 127);
  if (sign == '-') set_bit(dec, 127);
}

int checkbit32(const int value, const int position) {
  return ((value & (1 << position)) != 0);
}

void init_decimal(s21_decimal *dec) {
  dec->bits[LOW] = 0u;
  dec->bits[MID] = 0u;
  dec->bits[HIGH] = 0u;
  dec->bits[SCALE] = 0u;
}

/*целое в децимал*/
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
/*из децимал в целое*/
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

/* число с плавающей точкой в децимал */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  init_decimal(dst);
  int result = CONV_OK;
  char scale = 0;
  printf("my num1 = %f\n", src);
  if (src < 0) {
    set_sign(dst, '-');
    src = -src;
  };

  int exp = get_exp(src);
  double tmp = (double)src;
  // достали экспоненту

  if (exp >= 95 || exp <= -96) {
    result = CONV_ERR;
  } else {
    for (; (int)tmp == 0 && scale < 29; scale++) tmp *= 10;
    // нормализовали число
    for (int prec = 0; scale < 29 && prec < 6; scale++, prec++) tmp *= 10;
    // работаем с точностью
    // сейчас мы получили нужное нам целое число, от остальных чисел можем
    // избавляться. Нам нужно только 7 значящих цифр, 1 значящую цифру мы
    // получили после нормализации

    tmp = round(tmp);
    // округляем до ближайшего целого
    for (; fmod(tmp, 10) == 0 && scale > 0; scale--) tmp /= 10;
    // если число и до этого не нуждалось в увиличении точности, то мы его
    // урезаем. При этом помним, что scale не может быть меньше 0
    // теперь число у нас целое и только со значимыми числами
    // так как цифр значимых только 7 оно должно поместиться в unsigned int
    set_scale(dst, scale);
    // устанавливаем степень 10 в decimal
    s21_from_int_to_decimal((unsigned int)tmp, dst);
  };
  return result;
}

void set_scale(s21_decimal *dec, char power) {
  converter scale = {dec->bits[SCALE]};
  scale.bytes[2] = power;
  dec->bits[SCALE] = scale.number;
}

int get_exp(float num) {
  converter_float num_int = {num};
  converter exp = {num_int.conv_fl << 1};
  return (int)exp.bytes[3] - 127;
}

int main(void) {
  float s = 0.00123456789;
  printf("%d", get_exp(s));
  converter_float num_int = {s};
  print_32(num_int.conv_fl);
  printf("get exp %d\n", get_exp(s));
  printf("%.12f", s);
  // unsigned char a = 123;
  s21_decimal dec = {0};
  s21_from_float_to_decimal(s, &dec);
  print_dec(dec);
  return 0;
}
