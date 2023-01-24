#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>

enum n { LOW, MID, HIGH, SCALE };

typedef struct {
  int bits[4];
} s21_decimal;

typedef union {
  float f;
  int i;
} convert_f;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// вспомогательные функции
void print_bits_s21_decimal(s21_decimal value);
void set_bit(s21_decimal *value, int n);
int get_bit(s21_decimal value, int n);

#endif  // S21_DECIMAL_H_