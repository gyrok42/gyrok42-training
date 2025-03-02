// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#include "basic-bit-operations.h"

void setBit(uint8_t* byteVar, uint8_t bitNum) {
  *byteVar |= 1 << bitNum;
}

void resetBit(uint8_t* byteVar, uint8_t bitNum) {
  *byteVar &= ~(1 << bitNum);
}

void flipBit(uint8_t* byteVar, uint8_t bitNum) {
  *byteVar ^= (1 << bitNum);
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

void reverseBits(uint8_t* byteVar) {
  *byteVar = (*byteVar & 0xF0) >> 4 | (*byteVar & 0x0F) << 4;
  *byteVar = (*byteVar & 0xCC) >> 2 | (*byteVar & 0x33) << 2;
  *byteVar = (*byteVar & 0xAA) >> 1 | (*byteVar & 0x55) << 1;
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

void swapBits(uint8_t* byte1, uint8_t bit1, uint8_t* byte2, uint8_t bit2) {
  int8_t bit1ToRight = ((*byte1) >> bit1) & 1;
  int8_t bit2ToRight = ((*byte2) >> bit2) & 1;

  int8_t xorValue = bit1ToRight ^ bit2ToRight;

  *byte1 ^= xorValue << bit1;
  *byte2 ^= xorValue << bit2;
}
