// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// standard includes

// third-party includes
#include <gtest/gtest.h>

// project includes
#include "basic-bit-operations.h"
#include "reverse-rows.h"

/**
 * @test Test case for reverse_array_bits_swapping function.
 *
 * This test checks if each byte in an array has its bits reversed correctly.
 */
TEST(FlipBitmapTest, ReverseArrayBitsTest) {
  uint8_t arr[] = {0b10100000, 0b01100000};
  reverseArrayBitsSwapping(arr, 2);

  EXPECT_EQ(arr[0], 0b00000110);
  EXPECT_EQ(arr[1], 0b00000101);
}

/**
 * @test Test case for reverse_rows_swapping_bits function.
 *
 * This test verifies that flipping a bitmap horizontally produces
 * the expected mirrored result.
 */
TEST(FlipBitmapTest, FlipHorizontalTestSwappingBits) {
  uint8_t arr[6]{
      0b11010011, 0b01101100, 0b01101100,   // rev: 00110110 00110110 11001011
      0b00110110, 0b00110110, 0b11001011};  // rev: 11010011 01101100 01101100
  std::cout << "ORIGINAL 2D MATRIX" << std::endl;
  std::cout << "==================" << std::endl;
  print2DBitMatrix(arr, 3, 2);
  reverseRowsSwappingBits(arr, 3, 2);
  // Row 0
  EXPECT_EQ(arr[0], 0b00110110);
  EXPECT_EQ(arr[1], 0b00110110);
  EXPECT_EQ(arr[2], 0b11001011);
  // Row 1
  EXPECT_EQ(arr[3], 0b11010011);
  EXPECT_EQ(arr[4], 0b01101100);
  EXPECT_EQ(arr[5], 0b01101100);
  std::cout << "FLIPPED 2D MATRIX (Horizontally)" << std::endl;
  std::cout << "================================" << std::endl;
  print2DBitMatrix(arr, 3, 2);
}

/**
 * @test Test case for reverseArray function.
 *
 * This test verifies that reversing the order of elements
 * in an array produces the expected reversed result.
 */
TEST(FlipBitmapTest, ReverseArrayTest) {
  uint8_t arr[6]{0b11010011, 0b01101100, 0b01101100,
                 0b00110110, 0b00110110, 0b11001011};
  // reverse: 110100110110110001101100001101100011011011001011
  reverseArray(arr, 6);
  // Row 0
  EXPECT_EQ(arr[0], 0b11001011);
  EXPECT_EQ(arr[1], 0b00110110);
  EXPECT_EQ(arr[2], 0b00110110);
  // Row 1
  EXPECT_EQ(arr[3], 0b01101100);
  EXPECT_EQ(arr[4], 0b01101100);
  EXPECT_EQ(arr[5], 0b11010011);
}

/**
 * @test Test case for reverse_rows_reversing function.
 *
 * This test verifies that flipping a bitmap horizontally using
 * bitwise reversal produces the expected mirrored result.
 */
TEST(FlipBitmapTest, FlipHorizontalTestReversing) {
  uint8_t arr[6]{
      0b11010011, 0b01101100, 0b01101100,   // rev: 00110110 00110110 11001011
      0b00110110, 0b00110110, 0b11001011};  // rev: 11010011 01101100 01101100
  std::cout << "ORIGINAL 2D MATRIX" << std::endl;
  std::cout << "==================" << std::endl;
  print2DBitMatrix(arr, 3, 2);
  reverseRows(arr, 3, 2);
  EXPECT_EQ(arr[0], 0b00110110);
  EXPECT_EQ(arr[1], 0b00110110);
  EXPECT_EQ(arr[2], 0b11001011);
  EXPECT_EQ(arr[3], 0b11010011);
  EXPECT_EQ(arr[4], 0b01101100);
  EXPECT_EQ(arr[5], 0b01101100);
  std::cout << "ORIGINAL 2D MATRIX" << std::endl;
  std::cout << "==================" << std::endl;
  print2DBitMatrix(arr, 3, 2);
}

/**
 * @brief Main function to execute all Google Test cases.
 *
 * Initializes the Google Test framework and runs all registered tests.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @return Returns 0 if all tests pass, otherwise returns the number of failed
 * tests.
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
