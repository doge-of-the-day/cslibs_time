#pragma once

// include for the default integer types
#include <cstdint>

/// @brief typedef for 32-bit floating point values
using float32_t = float;
static_assert(sizeof(float) == 4, "size of aliased type is not as expected");
/// @brief typedef for 64-bit floating point values
using float64_t = double;
static_assert(sizeof(double) == 8, "size of aliased type is not as expected");