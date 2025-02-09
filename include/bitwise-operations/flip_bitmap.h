#pragma once
#include <cstdint>
int32_t multiply(int32_t a, int32_t b);
void swap_bits(uint8_t* byte1, uint8_t bit1, uint8_t* byte2, uint8_t bit2);
void reverse_array_bits(uint8_t* array, uint16_t bytes);
void flip_horizontaly_bitmap_mtp8bit(uint8_t* flat_bitmap, uint16_t width_bytes,
                                     uint16_t height_lines);
void print_bitmap_mtp8bit(uint8_t* flat_bitmap, uint16_t width_bytes,
                          uint16_t height_lines);
