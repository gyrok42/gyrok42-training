#include "include/bitwise-operations/flip_bitmap.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

// Test multiply function
TEST(FlipBitmapTest, MultiplyTest) {
  EXPECT_EQ(multiply(3, 4), 12);
  EXPECT_EQ(multiply(0, 5), 0);
  EXPECT_EQ(multiply(7, 1), 7);
}

// Test swap_bits function
TEST(FlipBitmapTest, SwapBitsTest) {
  uint8_t byte1 = 0b10101010;
  uint8_t byte2 = 0b01010100;
  swap_bits(&byte1, 7, &byte2, 0);

  EXPECT_EQ(byte1, 0b00101010);
  EXPECT_EQ(byte2, 0b01010101);
}

// Test reverse_array_bits function
TEST(FlipBitmapTest, ReverseArrayBitsTest) {
  uint8_t arr[] = {0b10100000, 0b01100000};
  reverse_array_bits(arr, 2);

  EXPECT_EQ(arr[0], 0b00000110);
  EXPECT_EQ(arr[1], 0b00000101);
}

// Test flip_horizontaly_bitmap_mtp8bit function
TEST(FlipBitmapTest, FlipHorizontalTest) {
  uint8_t arr[6]{
      0b11010011, 0b01101100, 0b01101100,   // reverse: 001101100011011011001011
      0b00110110, 0b00110110, 0b11001011};  // reverse: 110100110110110001101100
  std::cout << "ORIGINAL BITMAP" << std::endl;
  std::cout << "==============" << std::endl;
  print_bitmap_mtp8bit(arr, 3, 2);
  flip_horizontaly_bitmap_mtp8bit(arr, 3, 2);
  EXPECT_EQ(arr[0], 0b00110110);
  EXPECT_EQ(arr[1], 0b00110110);
  EXPECT_EQ(arr[2], 0b11001011);
  EXPECT_EQ(arr[3], 0b11010011);
  EXPECT_EQ(arr[4], 0b01101100);
  EXPECT_EQ(arr[5], 0b01101100);
  std::cout << "FLIPPED BITMAP" << std::endl;
  std::cout << "==============" << std::endl;
  print_bitmap_mtp8bit(arr, 3, 2);
}

// Run all tests
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  testing::GTEST_FLAG(catch_exceptions) = false;
  return RUN_ALL_TESTS();
}
