#include <cmath>
#include <iostream>

#include "include/bitwise-operations/flip_bitmap.h"

int32_t multiply(int32_t a, int32_t b) {
  int32_t result = 0;
  while (a > 0) {
    if (a & 1) {
      result += b;
    }
    a >>= 1;
    b <<= 1;
  }
  return result;
}

void swap_bits(uint8_t* byte1, int bit1, uint8_t* byte2, int bit2) {
  int8_t bit1_to_right = ((*byte1) >> bit1) & 1;
  int8_t bit2_to_right = ((*byte2) >> bit2) & 1;

  int8_t xor_value = bit1_to_right ^ bit2_to_right;

  *byte1 ^= xor_value << bit1;
  *byte2 ^= xor_value << bit2;
}

void reverse_array_bits(uint8_t* array, int bytes) {
  int left = 0;
  int right = bytes - 1;
  constexpr auto MUL4 = [](int v) -> int { return v << 2; };
  constexpr auto DIV8 = [](int v) -> int { return v >> 3; };
  constexpr auto MOD8 = [](int v) -> int { return v & 0x07; };
  constexpr int LAST_BIT = 7;

  for (int i = 0; i < MUL4(bytes); i++) {
    int lf = left + DIV8(i);
    int rt = right - DIV8(i);
    int bit1 = LAST_BIT - MOD8(i);
    int bit2 = MOD8(i);
    swap_bits(&array[lf], bit1, &array[rt], bit2);
  }
}

void flip_horizontaly_bitmap_mtp8bit(uint8_t* flat_bitmap, int width_bytes,
                                     int height_lines) {
  for (int h = 0; h < height_lines; h++) {
    reverse_array_bits(&flat_bitmap[multiply(width_bytes, h)], width_bytes);
  }
}
