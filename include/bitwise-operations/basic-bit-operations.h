// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#pragma once

// standard includes
#include <cstdint>
// third-party includes

// project includes

/**
 * @brief Sets a specific bit in a byte.
 *
 * This function sets the bit at the given position to 1.
 *
 * @param byteVar Pointer to the byte in which the bit will be set.
 * @param bitNum The bit position to set (0-7).
 */
void setBit(uint8_t* byteVar, uint8_t bitNum);

/**
 * @brief Resets a specific bit in a byte.
 *
 * This function clears the bit at the given position (sets it to 0).
 *
 * @param byteVar Pointer to the byte in which the bit will be reset.
 * @param bitNum The bit position to reset (0-7).
 */
void resetBit(uint8_t* byteVar, uint8_t bitNum);

/**
 * @brief Toggles (flips) a specific bit in a byte.
 *
 * This function inverts the bit at the given position (1 to 0, or 0 to 1).
 *
 * @param byteVar Pointer to the byte in which the bit will be flipped.
 * @param bitNum The bit position to toggle (0-7).
 */
void flipBit(uint8_t* byteVar, uint8_t bitNum);

/**
 * Multiplies two 32-bit signed integers and returns the result.
 * It does not use the operator *.
 * @param a The first integer to be multiplied.
 * @param b The second integer to be multiplied.
 * @return The product of a and b as a 32-bit signed integer.
 */
int32_t multiply(int32_t a, int32_t b);

/**
 * @brief Reverses the bits in a single byte.
 *
 * This function takes a pointer to an 8-bit value and reverses the order
 * of its bits, so that the least significant bit becomes the most significant,
 * and vice versa.
 *
 * @param byteVar Pointer to the byte whose bits will be reversed.
 */
void reverseBits(uint8_t* byteVar);

/**
 * @brief Swaps two specific bits between two bytes.
 *
 * @param byte1 Pointer to the first byte.
 * @param bit1 The bit position (0-7) in the first byte to swap.
 * @param byte2 Pointer to the second byte.
 * @param bit2 The bit position (0-7) in the second byte to swap.
 */
void swapBits(uint8_t* byte1, uint8_t bit1, uint8_t* byte2, uint8_t bit2);