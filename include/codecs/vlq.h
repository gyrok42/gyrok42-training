// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

// standard includes
#include <cstddef>
#include <cstdint>

// third-party includes

// project includes

/**
 * @brief Encodes a 32-bit integer into VLQ format.
 *
 * @param value The integer value to encode.
 * @param buffer The output buffer to store the encoded bytes.
 * @return The number of bytes used in the encoded representation.
 */
size_t vlqEncode(uint32_t value, uint8_t* buffer);

/**
 * @brief Decodes a VLQ-encoded integer.
 *
 * @param buffer The input buffer containing VLQ-encoded data.
 * @param value Pointer to store the decoded integer value.
 * @return The number of bytes consumed in decoding.
 */
size_t vlqDecode(const uint8_t* buffer, uint32_t* value);

/**
 * @brief Encodes an array of integers into VLQ format.
 *
 * @param values The input array of integers to encode.
 * @param count The number of integers in the array.
 * @param buffer The output buffer to store the encoded data.
 * @return The total number of bytes used in encoding.
 */
size_t vlqEncodeArray(const uint32_t* values, size_t count, uint8_t* buffer);

/**
 * @brief Decodes a VLQ-encoded byte array into an array of integers.
 *
 * @param buffer The input buffer containing VLQ-encoded data.
 * @param count The expected number of integers to decode.
 * @param values The output array to store decoded integers.
 * @return The total number of bytes consumed in decoding.
 */
size_t vlqDecodeArray(const uint8_t* buffer, size_t count, uint32_t* values);