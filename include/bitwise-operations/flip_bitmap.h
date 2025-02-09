#pragma once
#include <cstdint>

/**
 * @brief Multiplies two 32-bit signed integers and returns the result.
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
void reverse_array_bits(uint8_t* array, uint16_t bytes);

/**
 * @brief Flips a monochrome bitmap horizontally in place.
 *
 * @param flat_bitmap Pointer to the bitmap data stored as a flat array.
 * @param width_bytes The width of the bitmap in bytes (not pixels).
 * @param height_rows The height of the bitmap in rows.
 */
void flip_horizontaly_bitmap(uint8_t* flat_bitmap, uint16_t width_bytes,
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
