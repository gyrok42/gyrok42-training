/**
 * @file vlq_test.cpp
 * @brief Unit tests for VLQ encoding and decoding using Google Test.
 */

// standard includes
#include <format>
#include <iostream>
// third-party includes
#include <gtest/gtest.h>

// project includes
#include "vlq.h"

/**
 * @brief Tests vlq_encode for correctness.
 */
TEST(VLQTest, EncodeSingleValue) {
  uint8_t buffer[5];
  size_t size;

  size = vlqEncode(127, buffer);
  EXPECT_EQ(size, 1);
  EXPECT_EQ(buffer[0], 0x7F);

  size = vlqEncode(128, buffer);
  EXPECT_EQ(size, 2);
  EXPECT_EQ(buffer[0], 0x81);
  EXPECT_EQ(buffer[1], 0x00);

  size = vlqEncode(16, buffer);
  EXPECT_EQ(size, 1);
  EXPECT_EQ(buffer[0], 0x10);
}

/**
 * @brief Tests vlq_decode for correctness.
 */
TEST(VLQTest, DecodeSingleValue) {
  uint8_t buffer1[] = {0x7F};
  uint8_t buffer2[] = {0x81, 0x00};
  uint8_t buffer3[] = {0x10};
  uint32_t value;
  size_t size;

  size = vlqDecode(buffer1, &value);
  EXPECT_EQ(size, 1);
  EXPECT_EQ(value, 127);

  size = vlqDecode(buffer2, &value);
  EXPECT_EQ(size, 2);
  EXPECT_EQ(value, 128);

  size = vlqDecode(buffer3, &value);
  EXPECT_EQ(size, 1);
  EXPECT_EQ(value, 16);
}

/**
 * @brief Tests vlq_encode_array for correctness.
 */
TEST(VLQTest, EncodeArray) {
  uint32_t values[] = {127, 128};
  uint8_t buffer[10];
  size_t size = vlqEncodeArray(values, 2, buffer);

  EXPECT_EQ(size, 3);
  EXPECT_EQ(buffer[0], 0x7F);
  EXPECT_EQ(buffer[1], 0x81);
  EXPECT_EQ(buffer[2], 0x00);
}

/**
 * @brief Tests vlq_decode_array for correctness.
 */
TEST(VLQTest, DecodeArray) {
  uint8_t buffer[] = {0x7F, 0x81, 0x00};
  uint32_t values[2];
  size_t size = vlqDecodeArray(buffer, 2, values);

  EXPECT_EQ(size, 3);
  EXPECT_EQ(values[0], 127);
  EXPECT_EQ(values[1], 128);
}

/**
 * @brief Main function to execute all Google Test cases.
 *
 * @return 0 on successful test execution.
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
