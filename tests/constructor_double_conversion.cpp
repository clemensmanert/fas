#include "test_utils.hpp"
TEST_CASE("Expect templated value constructor capable creating "
          "constexpressions") {
	constexpr auto double_ctr = float8_t(0.0);
}

TEST_CASE("Expect to create the correct values on using the double "
          "conversion constructor.") {
	// Zero to be zero
	REQUIRE((int)ufloat8_t(0.0).mantissa() == 0);
	REQUIRE((int)ufloat8_t(0.0).exponent() == 0);

	// Minus zero
	REQUIRE((int)float8_t(-0.0).mantissa() == 0);
	REQUIRE((int)float8_t(-0.0).exponent() == 0);

	// One
	REQUIRE((int)ufloat8_t(1.0).mantissa() == 0x80);
	REQUIRE((int)ufloat8_t(1.0).exponent() == -7);

	// Minus one
	REQUIRE((int)float8_t(-1.0).mantissa() == -0x80);
	REQUIRE((int)float8_t(-1.0).exponent() == -7);

	// Two
	REQUIRE((int)ufloat8_t(2.0).mantissa() == 0x80);
	REQUIRE((int)ufloat8_t(2.0).exponent() == -6);

	// Minus two
	REQUIRE((int)float8_t(-2.0).mantissa() == -0x80);
	REQUIRE((int)float8_t(-2.0).exponent() == -6);

	// Larger Value
	REQUIRE((int)ufloat8_t(43386001782419654091580262447550446960640.0)
	            .mantissa() == 0xff);
	REQUIRE((int)ufloat8_t(43386001782419654091580262447550446960640.0)
	            .exponent() == 0x7f);

	// Samller Values
	REQUIRE((int)ufloat8_t(0.5).mantissa() == 0x80);
	REQUIRE((int)ufloat8_t(0.5).exponent() == -8);

	REQUIRE((int)float8_t(-0.5).mantissa() == -0x80);
	REQUIRE((int)float8_t(-0.5).exponent() == -8);

	REQUIRE((int)ufloat8_t(0.25).mantissa() == 0x80);
	REQUIRE((int)ufloat8_t(0.25).exponent() == -9);

	REQUIRE((int)float8_t(-0.25).mantissa() == -0x80);
	REQUIRE((int)float8_t(-0.25).exponent() == -9);

	// Very small values.
	REQUIRE((int)float8_t(-21778071482940061661655974875633165533184.0)
	            .mantissa() == -0x80);
	REQUIRE((int)float8_t(-21778071482940061661655974875633165533184.0)
	            .exponent() == 0x7f);

	// Fractions
	REQUIRE((int)ufloat8_t(1.5).mantissa() == 0xC0);
	REQUIRE((int)ufloat8_t(1.5).exponent() == -7);

	REQUIRE((int)float8_t(-1.5).mantissa() == -0x60);
	REQUIRE((int)float8_t(-1.5).exponent() == -6);
}
