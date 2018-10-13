#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "fas/float.hpp"
#include "fas/stream.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstdint>

using namespace fas;
using ufloat8_t = Float<uint8_t, int8_t>;
using float8_t = Float<int8_t, int8_t>;

#endif // TEST_UTILS_HPP
