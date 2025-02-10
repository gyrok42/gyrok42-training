#include "include/bitwise-operations/flip_bitmap.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

/**
 * @test Test case for the multiply function.
 *
 * This test verifies that the multiply function correctly computes
 * the product of two numbers, including edge cases.
 */
TEST(FlipBitmapTest, MultiplyTest) {
  EXPECT_EQ(multiply(3, 4), 12);
  EXPECT_EQ(multiply(0, 5), 0);
  EXPECT_EQ(multiply(7, 1), 7);
}

/**
 * @test Test case for swap_bits function.
 *
 * This test ensures that swapping bits between two bytes produces
 * the expected result.
 */
TEST(FlipBitmapTest, SwapBitsTest) {
  uint8_t byte1 = 0b10101010;
  uint8_t byte2 = 0b01010100;
  swap_bits(&byte1, 7, &byte2, 0);

  EXPECT_EQ(byte1, 0b00101010);
  EXPECT_EQ(byte2, 0b01010101);
}

/**
 * @test Test case for reverse_array_bits_swapping function.
 *
 * This test checks if each byte in an array has its bits reversed correctly.
 */
TEST(FlipBitmapTest, ReverseArrayBitsTest) {
  uint8_t arr[] = {0b10100000, 0b01100000};
  reverse_array_bits_swapping(arr, 2);

  EXPECT_EQ(arr[0], 0b00000110);
  EXPECT_EQ(arr[1], 0b00000101);
}

/**
 * @test Test case for flip_horizontaly_bitmap_swapping_bits function.
 *
 * This test verifies that flipping a bitmap horizontally produces
 * the expected mirrored result.
 */
TEST(FlipBitmapTest, FlipHorizontalTestSwappingBits) {
  uint8_t arr[6]{
      0b11010011, 0b01101100, 0b01101100,   // reverse: 001101100011011011001011
      0b00110110, 0b00110110, 0b11001011};  // reverse: 110100110110110001101100
  std::cout << "ORIGINAL BITMAP" << std::endl;
  std::cout << "==============" << std::endl;
  print_bitmap(arr, 3, 2);
  flip_horizontaly_bitmap_swapping_bits(arr, 3, 2);
  // Row 0
  EXPECT_EQ(arr[0], 0b00110110);
  EXPECT_EQ(arr[1], 0b00110110);
  EXPECT_EQ(arr[2], 0b11001011);
  // Row 1
  EXPECT_EQ(arr[3], 0b11010011);
  EXPECT_EQ(arr[4], 0b01101100);
  EXPECT_EQ(arr[5], 0b01101100);
  std::cout << "FLIPPED BITMAP" << std::endl;
  std::cout << "==============" << std::endl;
  print_bitmap(arr, 3, 2);
}

TEST(FlipBitmapTest, ReverseBitsTest) {
  uint8_t byte_var = 0b11001010;
  reverse_bits(&byte_var);
  EXPECT_EQ(byte_var, 0b01010011);
}

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

TEST(FlipBitmapTest, FlipHorizontalTestReversing) {
  uint8_t arr[6]{0b11010011, 0b01101100,
                 0b01101100,  // reverse: 00110110 00110110 11001011
                 0b00110110, 0b00110110,
                 0b11001011};  // reverse: 11010011 01101100 01101100
  std::cout << "ORIGINAL BITMAP" << std::endl;
  std::cout << "==============" << std::endl;
  print_bitmap(arr, 3, 2);
  flip_horizontaly_bitmap_reversing(arr, 3, 2);
  EXPECT_EQ(arr[0], 0b00110110);
  EXPECT_EQ(arr[1], 0b00110110);
  EXPECT_EQ(arr[2], 0b11001011);
  EXPECT_EQ(arr[3], 0b11010011);
  EXPECT_EQ(arr[4], 0b01101100);
  EXPECT_EQ(arr[5], 0b01101100);
  std::cout << "FLIPPED BITMAP" << std::endl;
  std::cout << "==============" << std::endl;
  print_bitmap(arr, 3, 2);
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
  testing::GTEST_FLAG(catch_exceptions) = false;
  return RUN_ALL_TESTS();
}
