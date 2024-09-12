#pragma once

#include <cstdint>

static_assert(sizeof(float) == 4, "size of aliased type is not as expected");
using float32_t = float;

static_assert(sizeof(double) == 8, "size of aliased type is not as expected");
using float64_t = double;