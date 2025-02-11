// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#pragma once
#include <cstdint>

/**
 * @brief Reverses the bit order of each byte in an array.
 *
 * @param array Pointer to the array of bytes.
 * @param bytes The number of bytes in the array.
 */
void reverse_array_bits_swapping(uint8_t* array, uint16_t bytes);

/**
 * @brief Flips a monochrome bitmap horizontally in place.
 *
 * This function reverses each row of the given monochrome bitmap, effectively
 * flipping the image horizontally. The bitmap is stored as a flat array, where
 * each row is `width_bytes` wide and there are `height_rows` total rows. This
 * function operates directly on the provided data, modifying it in place.
 *
 * The function assumes that each byte represents 8 pixels in a row, using a
 * monochrome (1-bit per pixel) representation.
 *
 * Unlike `flip_horizontaly_bitmap_reversing`, which operates at the byte level,
 * this function directly swaps individual bits within their respective byte
 * locations.
 *
 * @note The `flip_horizontaly_bitmap_reversing` approach is generally
 * preferable as it is simpler, easier to understand, and more straightforward
 * to document.
 *
 * @see flip_horizontaly_bitmap_reversing
 *
 * @param flat_array Pointer to the bitmap data stored as a flat array.
 * @param width_bytes The width of the bitmap in bytes (not pixels).
 * @param height_rows The height of the bitmap in rows.
 */
void flip_horizontaly_bitmap_swapping_bits(uint8_t* flat_array,
                                           uint16_t width_bytes,
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
 * @brief Flips a monochrome bitmap horizontally in place.
 *
 * This function reverses each row of the given monochrome bitmap, effectively
 * flipping the image horizontally. The bitmap is stored as a flat array, where
 * each row is `width_bytes` wide and there are `height_rows` total rows. This
 * function operates directly on the provided data, modifying it in place.
 *
 * The function assumes that each byte represents 8 pixels in a row, using a
 * monochrome (1-bit per pixel) representation.
 *
 * The algorithm first reverses the bits within each byte,
 * then reverses the order of bytes in each row.
 * How it is reversing each row - Showing with letters instead of {0,1}
 * to make visualization easier:
 * fedcbazy xwvutsrq ponmlkji hgfedcba (original bits)
 * yzabcdef qrstuvwx ijklmnop abcdefgh (reverse bits of each byte)
 * abcdefgh ijklmnop qrstuvwx yzabcdef (reverse the bytes order)
 *
 * @param flat_array Pointer to the bitmap data stored as a flat array.
 * @param width_bytes The width of the bitmap in bytes (not pixels).
 * @param height_rows The height of the bitmap in rows.
 */
void flip_horizontaly_bitmap_reversing(uint8_t* flat_array,
                                       uint16_t width_bytes,
                                       uint16_t height_rows);

/**
 * @brief Prints a monochrome bitmap horizontally in place.
 *
 * @param flat_array Pointer to the bitmap data stored as a flat array.
 * @param width_bytes The width of the bitmap in bytes (not pixels).
 * @param height_rows The height of the bitmap in rows.
 */
void print_bitmap(uint8_t* flat_array, uint16_t width_bytes,
                  uint16_t height_rows);