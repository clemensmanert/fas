#include "test_utils.hpp"

TEST_CASE("Expects divide to return a constexpression.") {
	constexpr auto result = ufloat8_t(1) / ufloat8_t(1);
	constexpr auto result_value = ufloat8_t(1) / 1;
}

TEST_CASE("Dividing zero result in zero.", "[divide]") {
	REQUIRE(ufloat8_t() / 1 == 0);
	REQUIRE(ufloat8_t() / 2 == 0);
	REQUIRE(ufloat8_t() / 15 == 0);
	REQUIRE(ufloat8_t() / 100 == 0);
	REQUIRE(ufloat8_t() / 0xff == 0);
}

TEST_CASE("Divide by one results in operand.", "[divide]") {
	REQUIRE(ufloat8_t(1) / 1 == 1);
	REQUIRE(ufloat8_t(2) / 1 == 2);
	REQUIRE(ufloat8_t(14) / 1 == 14);
	REQUIRE(ufloat8_t(100) / 1 == 100);
	REQUIRE(ufloat8_t(0xff) / 1 == 0xff);
}

TEST_CASE("Divide by minus one results in -operand.", "[divide]") {
	REQUIRE(float8_t(1) / -1 == -1);
	REQUIRE(float8_t(2) / -1 == -2);
	REQUIRE(float8_t(14) / -1 == -14);
	REQUIRE(float8_t(100) / -1 == -100);
	REQUIRE(float8_t(0x7f) / -1 == -0x7f);
}

TEST_CASE("Divide by larger values.", "[divide]") {
	REQUIRE(float8_t(1) / 2 == 0.5);
	REQUIRE(float8_t(1) / -2 == -0.5);
	REQUIRE(float8_t(-1) / -2 == 0.5);
	REQUIRE(float8_t(-1) / 2 == -0.5);

	REQUIRE(float8_t(0x40) / 0x40 == 1);
	REQUIRE(float8_t(0x40) / 0x2 == 0x20);
	REQUIRE(float8_t(0x1000) / 0x100 == 0x10);

	REQUIRE(float8_t(1) / 4 == 0.25);
	REQUIRE(float8_t(1) / 8 == 0.125);
}

TEST_CASE("Expect /= do be defined.") {
	float8_t target(18);

	target /= 3;
	REQUIRE(target == 6);

	target /= float8_t(3);
	REQUIRE(target == 2);
}

TEST_CASE(
    "Expect not to lose precision when dividing through larger numbers.") {
	auto actual = Float<std::int16_t, std::int8_t>(255) / 31;
	REQUIRE(actual == Float<std::int16_t, std::int8_t>(8.2258));

	REQUIRE(actual.mantissa() == 0x41CE);
	REQUIRE(actual.exponent() == -11);

	actual = Float<std::int16_t, std::int8_t>(255) / -31;
	REQUIRE(actual.mantissa() == -0x41CE);
	REQUIRE(actual.exponent() == -11);
}
