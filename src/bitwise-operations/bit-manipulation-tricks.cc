// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "bit-manipulation-tricks.h"

bool isPowerOfTwo(int n) {
  return (n > 0) && ((n & (n - 1)) == 0);
}

int countSetBits(int n) {
  int count = 0;
  while (n) {
    n &= (n - 1);  // Clears the lowest set bit
    count++;
  }
  return count;
}

void swap(int& a, int& b) {
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}

bool isOdd(int n) {
  return (n & 1);
}

int findUnique(int arr[], int size) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    result ^= arr[i];
  }
  return result;
}

int lowestSetBit(int n) {
  return n & -n;  // Two's complement trick
}

int flipBits(int n) {
  return ~n;
}

int clearLowestSetBit(int n) {
  return n & (n - 1);
}

bool getBit(int n, int i) {
  return (n & (1 << i)) != 0;
}

int setBit(int n, int i) {
  return n | (1 << i);
}

int clearBit(int n, int i) {
  return n & ~(1 << i);
}

int toggleBit(int n, int i) {
  return n ^ (1 << i);
}

bool haveOppositeSigns(int x, int y) {
  return (x ^ y) < 0;
}
