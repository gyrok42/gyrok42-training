#pragma once
#include <cstdint>

/**
 * Multiplies two 32-bit signed integers and returns the result.
 *
 * @param a The first integer to be multiplied.
 * @param b The second integer to be multiplied.
 * @return The product of a and b as a 32-bit signed integer.
 */
int32_t multiply(int32_t a, int32_t b);

/**
 * @brief Swaps two specific bits between two bytes.
 *
 * @param byte1 Pointer to the first byte.
 * @param bit1 The bit position (0-7) in the first byte to swap.
 * @param byte2 Pointer to the second byte.
 * @param bit2 The bit position (0-7) in the second byte to swap.
 */
void swap_bits(uint8_t* byte1, uint8_t bit1, uint8_t* byte2, uint8_t bit2);

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
 * @param flat_bitmap Pointer to the bitmap data stored as a flat array.
 * @param width_bytes The width of the bitmap in bytes (not pixels).
 * @param height_rows The height of the bitmap in rows.
 */
void flip_horizontaly_bitmap_swapping_bits(uint8_t* flat_bitmap,
                                           uint16_t width_bytes,
                                           uint16_t height_rows);

/**
 * @brief Reverses the bits in a single byte.
 *
 * This function takes a pointer to an 8-bit value and reverses the order
 * of its bits, so that the least significant bit becomes the most significant,
 * and vice versa.
 *
 * @param byte_var Pointer to the byte whose bits will be reversed.
 */
void reverse_bits(uint8_t* byte_var);

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
 *
 * @param flat_bitmap Pointer to the bitmap data stored as a flat array.
 * @param width_bytes The width of the bitmap in bytes (not pixels).
 * @param height_rows The height of the bitmap in rows.
 */
void flip_horizontaly_bitmap_reversing(uint8_t* flat_bitmap,
                                       uint16_t width_bytes,
                                       uint16_t height_rows);

/**
 * @brief Prints a monochrome bitmap horizontally in place.
 *
 * @param flat_bitmap Pointer to the bitmap data stored as a flat array.
 * @param width_bytes The width of the bitmap in bytes (not pixels).
 * @param height_rows The height of the bitmap in rows.
 */
void print_bitmap(uint8_t* flat_bitmap, uint16_t width_bytes,
                  uint16_t height_rows);