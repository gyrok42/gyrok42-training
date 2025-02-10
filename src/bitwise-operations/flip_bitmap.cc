// author: Jairo Borba
// contact: @gyrok42, gyrok42.com
//
// The goal of this exercise is to explore bitwise operations for training
// purposes. A lot of this may be found on Embedded Systems programming.
//
// The challenge
// =============
// Implement the function void flip_horizontaly_bitmap(
//                                     uint8_t* flat_bitmap,
//                                     uint16_t width_bytes,
//                                     uint16_t height_lines);
//
// A 2D bitmap (flat_bitmap) is provided such that each bit represents a pixel.
// The width is given in bytes, which makes the width in bits multiple of 8.
// The height corresponds to the number of lines of the 2D bitmap.
//
// Aditional challenge: Do not use * operator for multiplication.
// The `flip_horizontaly_bitmap_reversing` approach is preferable due to its
// simplicity, clarity, and ease of explanation.
//
// Note: A lot of comments in the code since the purpose is training.

#include "include/bitwise-operations/flip_bitmap.h"

#include <cmath>
#include <iostream>

int32_t multiply(int32_t a, int32_t b) {
  int32_t result = 0;
  // XOR for sign: it will be negative if we have a positive and a negative
  // number in the multiplication.
  int negative = (a < 0) ^ (b < 0);
  // Make the negative numbers into positive to multiply.
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;

  // a X b = SUM_from_i0_to_n(b_k(2^i * a))
  // Each term b_i decides whether we add 2^i * a to our sum.
  // each b_i{0,1} is a binary digit ob b.
  // n is the highest position where b_n is non-zero.
  // In the algorithm, this corresponds exactly to the
  // "if b is odd, add a" step, then "double a" and "halve b" to
  // move on the next bit.
  while (b > 0) {
    if (b & 1) {
      result += a;
    }
    a <<= 1;
    b >>= 1;
  }
  // Restore the sign and return
  return negative ? -result : result;
}

void swap_bits(uint8_t* byte1, uint8_t bit1, uint8_t* byte2, uint8_t bit2) {
  int8_t bit1_to_right = ((*byte1) >> bit1) & 1;
  int8_t bit2_to_right = ((*byte2) >> bit2) & 1;

  // I am avoinding "if"
  int8_t xor_value = bit1_to_right ^ bit2_to_right;

  *byte1 ^= xor_value << bit1;
  *byte2 ^= xor_value << bit2;
}

void reverse_array_bits_swapping(uint8_t* array, uint16_t bytes) {
  int left = 0;
  int right = bytes - 1;
  constexpr int LAST_BIT = 7;

  // flip_horizontaly_bitmap_reversing has a simpler algorithm
  // This is a more complex option, not preferable.

  // Total of bits: 8 * bytes
  // When swapping, we walk half way: 4 * bytes, hence bytes << 2
  int max_bit = bytes << 2;
  for (int i = 0; i < max_bit; i++) {
    int i_div8 = i >> 3;
    int i_mod8 = i & 7;
    int current_left = left + i_div8;
    int current_right = right - i_div8;
    int bit1 = LAST_BIT - i_mod8;
    int bit2 = i_mod8;
    swap_bits(&array[current_left], bit1, &array[current_right], bit2);
  }
}

void flip_horizontaly_bitmap_swapping_bits(uint8_t* flat_bitmap,
                                           uint16_t width_bytes,
                                           uint16_t height_rows) {
  for (uint16_t h = 0; h < height_rows; h++) {
    reverse_array_bits_swapping(&flat_bitmap[multiply(width_bytes, h)],
                                width_bytes);
  }
}

void reverse_bits(uint8_t* byte_var) {
  *byte_var = (*byte_var & 0xF0) >> 4 | (*byte_var & 0x0F) << 4;
  *byte_var = (*byte_var & 0xCC) >> 2 | (*byte_var & 0x33) << 2;
  *byte_var = (*byte_var & 0xAA) >> 1 | (*byte_var & 0x55) << 1;
}
void reverseArray(uint8_t* arr, int size) {
  int left = 0, right = size - 1;

  while (left < right) {
    // XOR swapping
    arr[left] ^= arr[right];
    arr[right] ^= arr[left];
    arr[left] ^= arr[right];
    // Move pointers
    left++;
    right--;
  }
}

void flip_horizontaly_bitmap_reversing(uint8_t* flat_bitmap,
                                       uint16_t width_bytes,
                                       uint16_t height_rows) {
  uint32_t total_bytes = multiply(height_rows, width_bytes);
  for (uint16_t row_byte_position = 0; row_byte_position < total_bytes;
       row_byte_position += width_bytes) {
    for (uint16_t w = 0; w < width_bytes; w++) {
      reverse_bits(&flat_bitmap[row_byte_position + w]);
    }
    reverseArray(&flat_bitmap[row_byte_position], width_bytes);
  }
}

void print_bitmap(uint8_t* flat_bitmap, uint16_t width_bytes,
                  uint16_t height_rows) {
  for (uint16_t h = 0; h < height_rows; h++) {
    for (uint16_t b = 0; b < width_bytes; b++) {
      std::cout << std::format("{:08b}",
                               flat_bitmap[multiply(h, width_bytes) + b]);
    }
    std::cout << std::endl;
  }
}
