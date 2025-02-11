// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// standard includes

// third-party includes
#include <gtest/gtest.h>

// project includes
#include "include/bitwise-operations/basic_bit_operations.h"

/**
 * @test Test case for set_bit function.
 *
 * This test verifies that setting a bit in a byte correctly updates the value.
 */
TEST(BasicBitOperationsTest, SetBitTest) {
  uint8_t byte = 0b00000000;
  set_bit(&byte, 2);  // Set bit at position 2
  EXPECT_EQ(byte, 0b00000100);

  set_bit(&byte, 5);  // Set bit at position 5
  EXPECT_EQ(byte, 0b00100100);

  set_bit(&byte, 2);  // Set same bit again (should remain the same)
  EXPECT_EQ(byte, 0b00100100);
}

/**
 * @test Test case for reset_bit function.
 *
 * This test verifies that resetting a bit in a byte correctly clears the bit.
 */
TEST(BasicBitOperationsTest, ResetBitTest) {
  uint8_t byte = 0b11111111;
  reset_bit(&byte, 2);  // Clear bit at position 2
  EXPECT_EQ(byte, 0b11111011);

  reset_bit(&byte, 5);  // Clear bit at position 5
  EXPECT_EQ(byte, 0b11011011);

  reset_bit(&byte, 0);  // Clear least significant bit
  EXPECT_EQ(byte, 0b11011010);

  reset_bit(&byte, 2);  // Set same bit again (should remain the same)
  EXPECT_EQ(byte, 0b11011010);
}

/**
 * @test Test case for flip_bit function.
 *
 * This test verifies that flipping a bit in a byte correctly toggles its state.
 */
TEST(BasicBitOperationsTest, FlipBitTest) {
  uint8_t byte = 0b00000000;
  flip_bit(&byte, 3);  // Flip bit at position 3
  EXPECT_EQ(byte, 0b00001000);

  flip_bit(&byte, 3);  // Flip the same bit again (should revert)
  EXPECT_EQ(byte, 0b00000000);

  flip_bit(&byte, 7);  // Flip most significant bit
  EXPECT_EQ(byte, 0b10000000);
}

/**
 * @test Test case for the multiply function.
 *
 * This test verifies that the multiply function correctly computes
 * the product of two numbers, including edge cases.
 */
TEST(BasicBitOperationsTest, MultiplyTest) {
  EXPECT_EQ(multiply(3, 4), 12);
  EXPECT_EQ(multiply(0, 5), 0);
  EXPECT_EQ(multiply(7, 1), 7);
}

/**
 * @test Test case for the reverse_bits function.
 *
 * This test verifies that the reverse_bits function correctly
 * reverses the bits of a byte.
 */
TEST(BasicBitOperationsTest, ReverseBitsTest) {
  uint8_t byte_var = 0b11001010;
  reverse_bits(&byte_var);
  EXPECT_EQ(byte_var, 0b01010011);
}

/**
 * @test Test case for swap_bits function.
 *
 * This test ensures that swapping bits between two bytes produces
 * the expected result.
 */
TEST(BasicBitOperationsTest, SwapBitsTest) {
  uint8_t byte1 = 0b10101010;
  uint8_t byte2 = 0b01010100;
  swap_bits(&byte1, 7, &byte2, 0);

  EXPECT_EQ(byte1, 0b00101010);
  EXPECT_EQ(byte2, 0b01010101);
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