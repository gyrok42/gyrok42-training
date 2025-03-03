// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// The goal of this exercise is to explore bitwise operations for training
// purposes. A lot of this may be found on Embedded Systems programming.
//
// The challenge
// =============
// Implement the function void reverseRows(
//                                     uint8_t* flatArray,
//                                     uint16_t widthBytes,
//                                     uint16_t heightLines);
//
// A 2D matrix of bits is provided.
// Note that the 2D array is flatten to a 1D array: flat_array.
// The width is given in bytes, which makes the width in bits multiple of 8.
// The height corresponds to the number of lines of the 2D matrix.
//
// Aditional challenge: Do not use * operator for multiplication.
//
// Note: The `reverse_rows` approach is preferable due to
// its simplicity, clarity, and ease of explanation.

// standard includes
#include <iostream>

// third-party includes
#include "basic-bit-operations.h"
#include "reverse-rows.h"

void reverseArrayBitsSwapping(uint8_t* array, uint16_t bytes) {
  int left = 0;
  int right = bytes - 1;
  constexpr int LAST_BIT = 7;

  // reverse_rows has a simpler algorithm
  // This is a more complex option, not preferable.
  int maxBit = bytes << 2;
  for (int i = 0; i < maxBit; i++) {
    int i_div8 = i >> 3;
    int i_mod8 = i & 7;
    int currentLeft = left + i_div8;
    int currentRight = right - i_div8;
    int bit1 = LAST_BIT - i_mod8;
    int bit2 = i_mod8;
    swapBits(&array[currentLeft], bit1, &array[currentRight], bit2);
  }
}

void reverseRowsSwappingBits(uint8_t* flatArray, uint16_t widthBytes,
                             uint16_t heightRows) {
  for (uint16_t h = 0; h < heightRows; h++) {
    reverseArrayBitsSwapping(&flatArray[multiply(widthBytes, h)], widthBytes);
  }
}

void reverseRows(uint8_t* flatArray, uint16_t widthBytes, uint16_t heightRows) {
  uint32_t totalBytes = multiply(heightRows, widthBytes);
  for (uint16_t rowBytePosition = 0; rowBytePosition < totalBytes;
       rowBytePosition += widthBytes) {
    // How it is reversing each row
    // First reverse the bits of each byte of the line:
    // fedcbazy xwvutsrq ponmlkji hgfedcba (original bits)
    // yzabcdef qrstuvwx ijklmnop abcdefgh (reverse bits of each byte)
    // abcdefgh ijklmnop qrstuvwx yzabcdef (reverse the bytes order)
    for (uint16_t w = 0; w < widthBytes; w++) {
      reverseBits(&flatArray[rowBytePosition + w]);
    }
    reverseArray(&flatArray[rowBytePosition], widthBytes);
  }
}

void print2DBitMatrix(uint8_t* flatArray, uint16_t widthBytes,
                      uint16_t heightRows) {
  uint32_t totalBytes = multiply(heightRows, widthBytes);
  for (uint16_t rowBytePosition = 0; rowBytePosition < totalBytes;
       rowBytePosition += widthBytes) {
    for (uint16_t colBytePosition = 0; colBytePosition < widthBytes;
         colBytePosition++) {
      std::cout << std::format("{:08b}",
                               flatArray[rowBytePosition + colBytePosition]);
    }
    std::cout << std::endl;
  }
}
