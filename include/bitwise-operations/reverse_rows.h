// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#pragma once
#include <cstdint>

/**
 * @brief Reverses the bit order of an array of bytes.
 *
 * Suppose we have an array like:
 * [0b11001100, 0b10101010, 0b10011100]
 * The array will be reversed such that it will be like:
 * [0b00111001, 0b01010101, 0b00110011]
 * This function does that by directly accessing each bit of the array
 * and their 'mirror' bit then swapping them.
 * @param array Pointer to the array of bytes.
 * @param bytes The number of bytes in the array.
 */
void reverse_array_bits_swapping(uint8_t* array, uint16_t bytes);

/**
 * @brief Reverses the bits of each row of a 2D bit matrix.
 *
 * This function reverses the bits of each row. A 2D matrix of bits is stored as
 * a flat array, where each row is `width_bytes` wide and there are
 * `height_rows` total rows. This function operates directly on the provided
 * data, modifying it in place.
 *
 *
 * Unlike `reverse_rows`, which operates at the byte level,
 * this function directly swaps individual bits within their respective byte
 * locations.
 *
 * @note The `reverse_rows` approach is generally
 * preferable as it is simpler, easier to understand, and more straightforward
 * to document.
 *
 * @see reverse_rows
 *
 * @param flat_array Pointer to the 2D bit array data stored as a flat array.
 * @param width_bytes The width of the 2D bit array in bytes (not bits).
 * @param height_rows The height of the 2D bit array in rows.
 */
void reverse_rows_swapping_bits(uint8_t* flat_array, uint16_t width_bytes,
                                uint16_t height_rows);

/**
 * @brief Reverses the order of elements in an array.
 *
 * This function swaps elements in the given array to reverse its order
 * in place. It modifies the original array.
 *
 * @param arr Pointer to the array to be reversed.
 * @param size The number of elements in the array.
 */
void reverseArray(uint8_t* arr, int size);

/**
 * @brief Reverses the bits of each row of a 2D bit matrix.
 *
 * This function reverses the bits of each row. A 2D matrix of bits is stored as
 * a flat array, where each row is `width_bytes` wide and there are
 * `height_rows` total rows. This function operates directly on the provided
 * data, modifying it in place.
 *
 * The algorithm first reverses the bits within each byte,
 * then reverses the order of bytes in each row.
 * 
 * Demonstrating the algorithm - Showing  the bits with letters instead of
 * {0,1} to make visualization easier: 
 * fedcbazy xwvutsrq ponmlkji hgfedcba (original bits)
 * yzabcdef qrstuvwx ijklmnop abcdefgh (reverse bits of each byte)
 * abcdefgh ijklmnop qrstuvwx yzabcdef (reverse the bytes order)
 *
 * @param flat_array Pointer to the 2D bit array data stored as a flat array.
 * @param width_bytes The width of the 2D bit array in bytes (not bits).
 * @param height_rows The height of the 2D bit array in rows.
 */
void reverse_rows(uint8_t* flat_array, uint16_t width_bytes,
                  uint16_t height_rows);

/**
 * @brief Prints a 2D matrix of bits.
 *
 * @param flat_array Pointer to the 2D maxtrix of bits data stored as a flat array.
 * @param width_bytes The width of the 2D maxtrix of bits in bytes (not pixels).
 * @param height_rows The height of the 2D maxtrix of bits in rows.
 */
void print_2D_bit_matrix(uint8_t* flat_array, uint16_t width_bytes,
                  uint16_t height_rows);