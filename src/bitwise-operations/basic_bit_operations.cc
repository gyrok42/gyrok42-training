// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#include "include/bitwise-operations/basic_bit_operations.h"

void set_bit(uint8_t* byte_var, uint8_t bit_num) {
  *byte_var |= 1 << bit_num;
}

void reset_bit(uint8_t* byte_var, uint8_t bit_num) {
  *byte_var &= ~(1 << bit_num);
}

void flip_bit(uint8_t* byte_var, uint8_t bit_num) {
  *byte_var ^= (1 << bit_num);
}

int32_t multiply(int32_t a, int32_t b) {
  int32_t result = 0;
  int negative = (a < 0) ^ (b < 0);

  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  while (b > 0) {
    if (b & 1) {
      result += a;
    }
    a <<= 1;
    b >>= 1;
  }

  return negative ? -result : result;
}

void reverse_bits(uint8_t* byte_var) {
  *byte_var = (*byte_var & 0xF0) >> 4 | (*byte_var & 0x0F) << 4;
  *byte_var = (*byte_var & 0xCC) >> 2 | (*byte_var & 0x33) << 2;
  *byte_var = (*byte_var & 0xAA) >> 1 | (*byte_var & 0x55) << 1;
}

void reverseArray(uint8_t* arr, int size) {
  int left = 0, right = size - 1;

  while (left < right) {
    arr[left] ^= arr[right];
    arr[right] ^= arr[left];
    arr[left] ^= arr[right];

    left++;
    right--;
  }
}

void swap_bits(uint8_t* byte1, uint8_t bit1, uint8_t* byte2, uint8_t bit2) {
  int8_t bit1_to_right = ((*byte1) >> bit1) & 1;
  int8_t bit2_to_right = ((*byte2) >> bit2) & 1;

  int8_t xor_value = bit1_to_right ^ bit2_to_right;

  *byte1 ^= xor_value << bit1;
  *byte2 ^= xor_value << bit2;
}
