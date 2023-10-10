#pragma once

#include <Arduino.h>
#include "types.hpp"

/**
 * @namespace utils
 * @brief A namespace containing utility functions.
 */
namespace utils {
/**
 * @brief Copy a block of memory from source to destination byte by byte.
 *
 * This function copies a block of memory from the source address to the
 * destination address byte by byte. It is often used for low-level memory
 * manipulation.
 *
 * @param dst Pointer to the destination memory location.
 * @param src Pointer to the source memory location.
 * @param size The number of bytes to copy.
 */
static inline void bytecpy(void* dst, const void* src, size_t size) {
  size_t i;

  for (i = 0; i < size; ++i) {
    ((volatile byte*)dst)[i] = ((volatile const byte*)src)[i];
  }
}
}  // namespace utils
