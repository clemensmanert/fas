#include "test_utils.hpp"

TEST_CASE("Expect constants to be available as constexpressions.") {
	constexpr auto zero = float8_t::ZERO();
	constexpr auto min = float8_t::MIN();
	constexpr auto max = float8_t::MAX();
	constexpr auto lowest = float8_t::LOWEST();
	constexpr auto inf = float8_t::INF();
	constexpr auto negative_inf = float8_t::NEGATIVE_INF();
	constexpr auto base = float8_t::EXPONENT_BASE();

	constexpr auto mantissa = float8_t::ZERO().mantissa();
	constexpr auto exponent = float8_t::ZERO().exponent();
}

TEST_CASE("Expect zero value to have zero exponent and mantissa.") {
	// Unsigned
	REQUIRE(ufloat8_t::ZERO().mantissa() == 0x0);
	REQUIRE(ufloat8_t::ZERO().exponent() == 0x0);

	// Signed
	REQUIRE(float8_t::ZERO().mantissa() == 0x0);
	REQUIRE(ufloat8_t::ZERO().exponent() == 0x0);
}

TEST_CASE("Expect max values to have both maximized mantissa and exponent.") {
	// Unsigned
	REQUIRE(ufloat8_t::MAX().mantissa() == 0xff);
	REQUIRE(ufloat8_t::MAX().exponent() == 0x7f);

	// Signed
	REQUIRE(float8_t::MAX().mantissa() == 0x7f);
	REQUIRE(float8_t::MAX().exponent() == 0x7f);
}

TEST_CASE("Expect min values to have both lowest exponent and"
          " min postive mantissa.") {
	// Unsigned
	REQUIRE(ufloat8_t::MIN().mantissa() == 0x01);
	REQUIRE(ufloat8_t::MIN().exponent() == -0x80);

	// Signed
	REQUIRE(float8_t::MIN().mantissa() == 0x01);
	REQUIRE(float8_t::MIN().exponent() == -0x80);
}

TEST_CASE("Expect lowest values to have both lowest mantissa and exponent.") {
	// Unsigned
	REQUIRE(ufloat8_t::LOWEST().mantissa() == 0x0);
	REQUIRE(ufloat8_t::LOWEST().exponent() == 0x7f);

	REQUIRE(float8_t::LOWEST().mantissa() == -0x80);
	REQUIRE(float8_t::LOWEST().exponent() == 0x7f);
}

TEST_CASE("Expect infinte values to have mantissa 0 and exponent 1.") {
	// Unsigned
	REQUIRE(ufloat8_t::INF().mantissa() == 0x0);
	REQUIRE(ufloat8_t::INF().exponent() == 0x1);

	// Signed
	REQUIRE(float8_t::INF().mantissa() == 0x0);
	REQUIRE(float8_t::INF().exponent() == 0x1);
}

TEST_CASE("Expect negative infinte values to have mantissa 0 and exponent 2.") {
	// Unsigned
	REQUIRE(ufloat8_t::NEGATIVE_INF().mantissa() == 0x0);
	REQUIRE(ufloat8_t::NEGATIVE_INF().exponent() == 0x2);

	// Signed
	REQUIRE(float8_t::NEGATIVE_INF().mantissa() == 0x0);
	REQUIRE(float8_t::NEGATIVE_INF().exponent() == 0x2);
}

TEST_CASE("Expect Base to be set correctly.") {
	REQUIRE(ufloat8_t::EXPONENT_BASE() == 0x2);
	REQUIRE(Float<int, int, 3>::EXPONENT_BASE() == 0x3);
}
