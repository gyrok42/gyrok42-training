// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @brief Checks if a number is a power of 2.
 *
 * A number is a power of two if it has exactly one bit set.
 * The expression `n & (n - 1)` clears the lowest set bit.
 * If the result is 0, then `n` had only one bit set, making it a power of two.
 *
 * @param n The number to check.
 * @return true if n is a power of two, false otherwise.
 */
bool isPowerOfTwo(int n) {
  return (n > 0) && ((n & (n - 1)) == 0);
}

/**
 * @brief Counts the number of set bits (Hamming weight) in an integer.
 *
 * This method repeatedly removes the lowest set bit, reducing
 * the number of iterations to the count of set bits.
 *
 * @param n The integer to analyze.
 * @return The number of bits set to 1.
 */
int countSetBits(int n) {
  int count = 0;
  while (n) {
    n &= (n - 1);  // Clears the lowest set bit
    count++;
  }
  return count;
}

/**
 * @brief Swaps two integers without using a temporary variable.
 *
 * Uses XOR (`^`) to swap values without requiring extra space.
 *
 * @param a First integer to swap.
 * @param b Second integer to swap.
 */
void swap(int& a, int& b) {
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}

/**
 * @brief Checks if a number is odd.
 *
 * The least significant bit (LSB) of an odd number is always 1.
 *
 * @param n The number to check.
 * @return true if the number is odd, false otherwise.
 */
bool isOdd(int n) {
  return (n & 1);
}

/**
 * @brief Finds the only non-repeating element in an array.
 *
 * XORing all elements cancels out duplicates (`a ⊕ a = 0`),
 * leaving only the unique number.
 *
 * @param arr The input array.
 * @param size The number of elements in the array.
 * @return The unique element.
 */
int findUnique(int arr[], int size) {
  int result = 0;
  for (int i = 0; i < size; i++) {
    result ^= arr[i];
  }
  return result;
}

/**
 * @brief Gets the lowest set bit in a number.
 *
 * The expression `-n` is `~n + 1`, and `n & -n` isolates the lowest set bit.
 *
 * @param n The input number.
 * @return The lowest set bit.
 */
int lowestSetBit(int n) {
  return n & -n;  // Two's complement trick
}

/**
 * @brief Flips all bits of an integer (bitwise NOT).
 *
 * @param n The input number.
 * @return The bitwise negation of n.
 */
int flipBits(int n) {
  return ~n;
}

/**
 * @brief Clears the lowest set bit in a number.
 *
 * The operation `n & (n - 1)` removes the rightmost 1-bit.
 *
 * @param n The input number.
 * @return The number with its lowest set bit cleared.
 */
int clearLowestSetBit(int n) {
  return n & (n - 1);
}

/**
 * @brief Extracts the i-th bit of a number.
 *
 * The expression `1 << i` creates a mask for the i-th bit.
 * AND (`&`) extracts its value.
 *
 * @param n The number to check.
 * @param i The bit position (0-based).
 * @return true if the i-th bit is set, false otherwise.
 */
bool getBit(int n, int i) {
  return (n & (1 << i)) != 0;
}

/**
 * @brief Sets the i-th bit of a number.
 *
 * The OR (`|`) operation sets the i-th bit.
 *
 * @param n The number to modify.
 * @param i The bit position (0-based).
 * @return The number with the i-th bit set.
 */
int setBit(int n, int i) {
  return n | (1 << i);
}

/**
 * @brief Clears the i-th bit of a number.
 *
 * The expression `~(1 << i)` creates a mask with the i-th bit cleared.
 * AND (`&`) applies this mask to the number.
 *
 * @param n The number to modify.
 * @param i The bit position (0-based).
 * @return The number with the i-th bit cleared.
 */
int clearBit(int n, int i) {
  return n & ~(1 << i);
}

/**
 * @brief Toggles the i-th bit of a number.
 *
 * The XOR (`^`) operation flips the i-th bit.
 *
 * @param n The number to modify.
 * @param i The bit position (0-based).
 * @return The number with the i-th bit toggled.
 */
int toggleBit(int n, int i) {
  return n ^ (1 << i);
}

/**
 * @brief Checks if two integers have opposite signs.
 *
 * XOR (`^`) checks the sign bit. If the result is negative, the numbers
 * have opposite signs.
 *
 * @param x First integer.
 * @param y Second integer.
 * @return true if x and y have opposite signs, false otherwise.
 */
bool haveOppositeSigns(int x, int y) {
  return (x ^ y) < 0;
}
