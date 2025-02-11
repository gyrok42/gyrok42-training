// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// The goal of this exercise is to explore bitwise operations for training
// purposes. A lot of this may be found on Embedded Systems programming.
//
// The challenge
// =============
// Implement the function void flip_horizontaly_bitmap(
//                                     uint8_t* flat_array,
//                                     uint16_t width_bytes,
//                                     uint16_t height_lines);
//
// A 2D bitmap is provided such that each bit represents a pixel.
// Note that the 2D array is flatten to a 1D array: flat_array.
// The width is given in bytes, which makes the width in bits multiple of 8.
// The height corresponds to the number of lines of the 2D bitmap.
//
// Aditional challenge: Do not use * operator for multiplication.
//
// Note: The `flip_horizontaly_bitmap_reversing` approach is preferable due to
// its simplicity, clarity, and ease of explanation.

// standard includes
#include <iostream>

// third-party includes
#include "include/bitwise-operations/basic_bit_operations.h"
#include "include/bitwise-operations/flip_bitmap.h"

void reverse_array_bits_swapping(uint8_t* array, uint16_t bytes) {
  int left = 0;
  int right = bytes - 1;
  constexpr int LAST_BIT = 7;

  // flip_horizontaly_bitmap_reversing has a simpler algorithm
  // This is a more complex option, not preferable.
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

void flip_horizontaly_bitmap_swapping_bits(uint8_t* flat_array,
                                           uint16_t width_bytes,
                                           uint16_t height_rows) {
  for (uint16_t h = 0; h < height_rows; h++) {
    reverse_array_bits_swapping(&flat_array[multiply(width_bytes, h)],
                                width_bytes);
  }
}

void flip_horizontaly_bitmap_reversing(uint8_t* flat_array,
                                       uint16_t width_bytes,
                                       uint16_t height_rows) {
  uint32_t total_bytes = multiply(height_rows, width_bytes);
  for (uint16_t row_byte_position = 0; row_byte_position < total_bytes;
       row_byte_position += width_bytes) {
    // How it is reversing each row
    // First flip the bits of each byte of the line:
    // fedcbazy xwvutsrq ponmlkji hgfedcba (original bits)
    // yzabcdef qrstuvwx ijklmnop abcdefgh (reverse bits of each byte)
    // abcdefgh ijklmnop qrstuvwx yzabcdef (reverse the bytes order)
    for (uint16_t w = 0; w < width_bytes; w++) {
      reverse_bits(&flat_array[row_byte_position + w]);
    }
    reverseArray(&flat_array[row_byte_position], width_bytes);
  }
}

void print_bitmap(uint8_t* flat_array, uint16_t width_bytes,
                  uint16_t height_rows) {
  uint32_t total_bytes = multiply(height_rows, width_bytes);
  for (uint16_t row_byte_position = 0; row_byte_position < total_bytes;
       row_byte_position += width_bytes) {
    for (uint16_t col_byte_position = 0; col_byte_position < width_bytes;
         col_byte_position++) {
      std::cout << std::format(
          "{:08b}", flat_array[row_byte_position + col_byte_position]);
    }
    std::cout << std::endl;
  }
}
