// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file vlq.c
 * @brief Implementation of Variable-Length Quantity (VLQ) encoding and
 * decoding.
 */

// standard includes

// third-party includes

// project includes
#include "include/codecs/vlq.h"

size_t vlq_encode(uint32_t value, uint8_t* buffer) {
  size_t size = 0;
  uint8_t temp[5];

  do {
    temp[size] = (value & 0x7F);
    if (size > 0) {
      temp[size] |= 0x80;
    }
    value >>= 7;
    size++;
  } while (value > 0);

  // Reverse and copy to buffer
  for (size_t i = 0; i < size; i++) {
    buffer[i] = temp[size - i - 1];
  }

  return size;
}

size_t vlq_decode(const uint8_t* buffer, uint32_t* value) {
  *value = 0;
  size_t size = 0;

  for (;;) {
    *value = (*value << 7) | (buffer[size] & 0x7F);
    if (!(buffer[size] & 0x80)) {
      break;
    }
    size++;
  }

  return size + 1;
}

size_t vlq_encode_array(const uint32_t* values, size_t count, uint8_t* buffer) {
  size_t total_size = 0;
  for (size_t i = 0; i < count; i++) {
    total_size += vlq_encode(values[i], buffer + total_size);
  }
  return total_size;
}

size_t vlq_decode_array(const uint8_t* buffer, size_t count, uint32_t* values) {
  size_t total_size = 0;
  for (size_t i = 0; i < count; i++) {
    total_size += vlq_decode(buffer + total_size, &values[i]);
  }
  return total_size;
}
