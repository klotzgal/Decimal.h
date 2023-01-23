#include <math.h>
#include <stdio.h>

typedef struct {
  int bits[4];
} s21_decimal;

enum n { LOW, MID, HIGH, SCALE };

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void print_bits_s21_decimal(s21_decimal value);
int set_bit();

int main() {
  s21_decimal value = {{22, 22, 22, 22}};
  // value.bits[3] <<= 15;
  // value.bits[3] |= 1 << 22;
  print_bits_s21_decimal(value);
  set_bit(&value, 128);
  print_bits_s21_decimal(value);
  return 0;
}

void print_bits_s21_decimal(s21_decimal value) {
  s21_decimal value_copy = value;
  // for (int i = 0; i < 34; ++i) {
  printf("%11d%11d%11d%11d = ", value_copy.bits[0], value_copy.bits[1],
         value_copy.bits[2], value_copy.bits[3]);

  for (int b = 0; b < 4; ++b) {
    int copy = value_copy.bits[b];

    for (int j = 0; j < 32; ++j) {
      if (b == 3 && (j == 32 - 23 || j == 32 - 15 || j == 1)) {
        printf(" ");
      }
      printf("%c", (copy & 0x100000000) ? '1' : '0');
      copy <<= 1;
    }
    if (b != 3) {
      printf(" ");
    }
  }
  printf("\n");
  //   value_copy.bits[0] <<= 1;
  //   value_copy.bits[1] <<= 1;
  //   value_copy.bits[2] <<= 1;
  //   value_copy.bits[3] <<= 1;
  // }
}  // закоменчен битовый сдвиг числа

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  (void)value_1;
  (void)value_2;
  (void)result;
  return 0;
}

int set_bit(s21_decimal *value, int n) {
  int res = 0;
  if (n < 0 || n > 128) {
    res = 1;
    printf("n_error\n");
  } else {
    value->bits[n / 33] |= (1 << (n % 32));
  }
  return res;
}
