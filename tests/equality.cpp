#include "test_utils.hpp"

TEST_CASE("Equals and unequals are constexpressions.") {
	constexpr auto rr = ufloat8_t(1);
	constexpr auto result_eq = ufloat8_t(1) == ufloat8_t(1);
	constexpr auto result_eq_value = ufloat8_t(1) == 1;

	constexpr auto result_uneq = ufloat8_t(1) != ufloat8_t(1);
	constexpr auto result_uneq_value = ufloat8_t(1) != 1;
}

TEST_CASE("One value should be equals to itself.") {
	ufloat8_t target(1, 0);
	REQUIRE(target == target);
}

TEST_CASE("Different values should be different.") {
	REQUIRE(float8_t(-1) != float8_t(1));
	REQUIRE(float8_t(-1) != 1);
}

TEST_CASE("Same values should be same.") {
	REQUIRE(ufloat8_t(0x10, 1) == 0x20);
	REQUIRE(ufloat8_t(0x2, 3) == 0x10);
	REQUIRE(ufloat8_t(0xFF, 4) == 0xFF0);
}

TEST_CASE("Expect to be equals when exponent is zero no matter mantissa") {
	REQUIRE(ufloat8_t(0) == ufloat8_t::ZERO());
}
