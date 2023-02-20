#ifndef S21_CONVARTATION_H
#define S21_CONVARTATION_H

#include <limits.h>
#include <math.h>
#include <stdio.h>

#define MAX_DEC 79228162514264337593543950335
#define MIN_DEC -79228162514264337593543950335
#define POSITION (index / 32)

#define CONV_OK 0
#define CONV_ERR 1

typedef enum { NORM, INF, N_INF, NANa, DOP_CODE } value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} s21_decimal;

typedef union {
  unsigned int number;
  unsigned char bytes[4];
} converter;
// так как бы нельзя делать, но я делаю....

typedef union {
  float fl;
  unsigned int conv_fl;
} converter_float;

enum bit { LOW, MID, HIGH, SCALE };

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

void init_decimal(s21_decimal *dec);
unsigned int mask(unsigned int index);
int check_bit(s21_decimal dec, unsigned int index);
void unset_bit(s21_decimal *dec, unsigned int index);
void set_bit(s21_decimal *dec, unsigned int index);
// void switch_bit(s21_decimal *dec, unsigned int index);
void set_sign(s21_decimal *dec, char sign);
int get_exp(float num);
void set_scale(s21_decimal *dec, char power);

void print_bytes(unsigned char num);
void print_32(unsigned int a);
void print_dec(s21_decimal dec);

#endif  // S21_CONVARTATION_H
