#include "test_utils.hpp"

TEST_CASE("Casting should return a constexpr.") {
	constexpr auto result = static_cast<int8_t>(float8_t::ZERO());
}

TEST_CASE("Casting an value statically.") {
	// Large numbers
	REQUIRE(static_cast<int8_t>(float8_t::ZERO()) == 0);
	REQUIRE(static_cast<double>(float8_t::ZERO()) == 0.0);
	REQUIRE(static_cast<float>(float8_t::ZERO()) == 0.0);

	REQUIRE(static_cast<int8_t>(float8_t(127)) == 127);
	REQUIRE(static_cast<float>(float8_t(127)) == 127);

	REQUIRE(static_cast<int8_t>(float8_t(-128)) == -128);
	REQUIRE(static_cast<float>(float8_t(-128)) == -128);

	REQUIRE(static_cast<int16_t>(float8_t(0x100)) == 0x100);
	REQUIRE(static_cast<float>(float8_t(0x100)) == 0x100);

	REQUIRE(static_cast<int16_t>(float8_t(0x4000)) == 0x4000);
	REQUIRE(static_cast<float>(float8_t(0x4000)) == 0x4000);

	REQUIRE(static_cast<int16_t>(float8_t(-0x4000)) == -0x4000);
	REQUIRE(static_cast<float>(float8_t(-0x4000)) == -0x4000);

	// Fractions
	REQUIRE(static_cast<int16_t>(float8_t(1, -1)) == 0);
	REQUIRE(static_cast<float>(float8_t(1, -1)) == 0.5);
	REQUIRE(static_cast<float>(float8_t(1, -3)) == 0.125);

	REQUIRE(static_cast<float>(float8_t(3, -1)) == 1.5);
	REQUIRE(static_cast<float>(float8_t(11, -1)) == 5.5);
	REQUIRE(static_cast<float>(float8_t(-11, -1)) == -5.5);

	// Fractions to int
	REQUIRE(static_cast<int>(float8_t(1, -1)) == 0);
	REQUIRE(static_cast<int>(float8_t(3, -1)) == 1);
}
