// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <gtest/gtest.h>
#include "bit-manipulation-tricks.h"

// Test for isPowerOfTwo
TEST(BitManipulationTest, IsPowerOfTwo) {
    EXPECT_TRUE(isPowerOfTwo(1));
    EXPECT_TRUE(isPowerOfTwo(2));
    EXPECT_TRUE(isPowerOfTwo(4));
    EXPECT_TRUE(isPowerOfTwo(8));
    EXPECT_TRUE(isPowerOfTwo(1024));
    EXPECT_FALSE(isPowerOfTwo(0));
    EXPECT_FALSE(isPowerOfTwo(-2));
    EXPECT_FALSE(isPowerOfTwo(3));
    EXPECT_FALSE(isPowerOfTwo(10));
}

// Test for countSetBits
TEST(BitManipulationTest, CountSetBits) {
    EXPECT_EQ(countSetBits(0), 0);
    EXPECT_EQ(countSetBits(1), 1);
    EXPECT_EQ(countSetBits(2), 1);
    EXPECT_EQ(countSetBits(3), 2);
    EXPECT_EQ(countSetBits(7), 3);
    EXPECT_EQ(countSetBits(15), 4);
    EXPECT_EQ(countSetBits(255), 8);
    EXPECT_EQ(countSetBits(-1), 32); // Assuming 32-bit integers
}

// Test for swap
TEST(BitManipulationTest, Swap) {
    int a = 5, b = 10;
    swap(a, b);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 5);

    int x = -3, y = 7;
    swap(x, y);
    EXPECT_EQ(x, 7);
    EXPECT_EQ(y, -3);
}

// Test for isOdd
TEST(BitManipulationTest, IsOdd) {
    EXPECT_TRUE(isOdd(1));
    EXPECT_TRUE(isOdd(3));
    EXPECT_TRUE(isOdd(5));
    EXPECT_FALSE(isOdd(2));
    EXPECT_FALSE(isOdd(10));
    EXPECT_FALSE(isOdd(0));
}

// Test for findUnique
TEST(BitManipulationTest, FindUnique) {
    int arr1[] = {1, 2, 3, 2, 1};
    EXPECT_EQ(findUnique(arr1, 5), 3);

    int arr2[] = {4, 4, 5, 5, 6};
    EXPECT_EQ(findUnique(arr2, 5), 6);

    int arr3[] = {7};
    EXPECT_EQ(findUnique(arr3, 1), 7);
}

// Test for lowestSetBit
TEST(BitManipulationTest, LowestSetBit) {
    EXPECT_EQ(lowestSetBit(0b10100), 0b100);
    EXPECT_EQ(lowestSetBit(0b11000), 0b1000);
    EXPECT_EQ(lowestSetBit(1), 1);
    EXPECT_EQ(lowestSetBit(0), 0);
}

// Test for flipBits
TEST(BitManipulationTest, FlipBits) {
    EXPECT_EQ(flipBits(0), ~0);
    EXPECT_EQ(flipBits(1), ~1);
    EXPECT_EQ(flipBits(-1), 0);
}

// Test for clearLowestSetBit
TEST(BitManipulationTest, ClearLowestSetBit) {
    EXPECT_EQ(clearLowestSetBit(0b10100), 0b10000);
    EXPECT_EQ(clearLowestSetBit(0b1000), 0);
    EXPECT_EQ(clearLowestSetBit(1), 0);
}

// Test for getBit
TEST(BitManipulationTest, GetBit) {
    EXPECT_TRUE(getBit(5, 0));  // 5 = 0b101
    EXPECT_FALSE(getBit(5, 1));
    EXPECT_TRUE(getBit(5, 2));
}

// Test for setBit
TEST(BitManipulationTest, SetBit) {
    EXPECT_EQ(setBit(5, 1), 7);  // 5 = 0b101, set bit 1 -> 0b111
    EXPECT_EQ(setBit(0, 3), 8);
}

// Test for clearBit
TEST(BitManipulationTest, ClearBit) {
    EXPECT_EQ(clearBit(7, 1), 5);  // 7 = 0b111, clear bit 1 -> 0b101
    EXPECT_EQ(clearBit(8, 3), 0);  // 8 = 0b1000, clear bit 3 -> 0b0000
}

// Test for toggleBit
TEST(BitManipulationTest, ToggleBit) {
    EXPECT_EQ(toggleBit(5, 0), 4);  // 5 = 0b101, toggle bit 0 -> 0b100
    EXPECT_EQ(toggleBit(5, 1), 7);  // 5 = 0b101, toggle bit 1 -> 0b111
}

// Test for haveOppositeSigns
TEST(BitManipulationTest, HaveOppositeSigns) {
    EXPECT_TRUE(haveOppositeSigns(10, -5));
    EXPECT_TRUE(haveOppositeSigns(-1, 1));
    EXPECT_FALSE(haveOppositeSigns(5, 5));
    EXPECT_FALSE(haveOppositeSigns(-5, -10));
}

