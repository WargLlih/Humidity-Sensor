#pragma once

#include <Arduino.h>
#include "types.hpp"

namespace utils {
static inline void bytecpy(void* dst, const void* src, size_t size) {
  size_t i;

  for (i = 0; i < size; ++i) {
    ((volatile byte*)dst)[i] = ((volatile const byte*)src)[i];
  }
}
}