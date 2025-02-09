#pragma once
#include <cstdint>
int32_t multiply(int32_t a, int32_t b);
void swap_bits(uint8_t* byte1, int bit1, uint8_t* byte2, int bit2);
void reverse_array_bits(uint8_t* array, int bytes);
void flip_horizontaly_bitmap_mtp8bit(uint8_t* flat_bitmap, int width_bytes,
                                     int height_lines);
