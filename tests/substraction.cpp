#include "test_utils.hpp"

TEST_CASE("Expects substract to return a constexpression.") {
	constexpr auto result = ufloat8_t(1) - ufloat8_t(1);
	constexpr auto result_value = ufloat8_t(1) - 1;
}

TEST_CASE("Substracting zero results in the same value.") {
	REQUIRE(float8_t() - 0 == 0);
	REQUIRE(float8_t(1) - 0 == 1);
	REQUIRE(float8_t(-1) - 0 == -1);
	REQUIRE(float8_t(100) - 0 == 100);
	REQUIRE(float8_t(-100) - 0 == -100);
}

TEST_CASE("Substracting from zero results in the negative value.") {
	REQUIRE(float8_t() - 0 == 0);
	REQUIRE(float8_t() - 1 == -1);
	REQUIRE(float8_t() - 100 == -100);
	REQUIRE(float8_t() - (-1) == 1);
	REQUIRE(float8_t() - (-100) == 100);
}

TEST_CASE("Substracting same value should result in zero.") {
	REQUIRE(float8_t(1) - 1 == 0);
	REQUIRE(float8_t(2) - 2 == 0);
	REQUIRE(float8_t(4) - 4 == 0);
	REQUIRE(float8_t(100) - 100 == 0);
	REQUIRE(float8_t(0x7f) - 0x7f == 0);
}

TEST_CASE("Substracting a negative value should increase the target.") {
	REQUIRE(float8_t(-0) - (-0) == 0);
	REQUIRE(float8_t(-1) - (-1) == 0);
	REQUIRE(float8_t(-4) - (-4) == 0);
	REQUIRE(float8_t(-100) - (-100) == 0);
	REQUIRE(float8_t(-200) - (-200) == 0);
	REQUIRE(float8_t(-0x80) - (-0x80) == 0);
}

TEST_CASE("Substracting values out of mantissa's range\
 should decrease exponent.") {
	REQUIRE(float8_t(-0x7f) - 1 == -0x80);
	REQUIRE(float8_t(-0x7f) - 2 == -0x80);
	REQUIRE(float8_t(-0x7f) - 3 == -0x80);
	REQUIRE(float8_t(-0x7f) - 4 == -0x82);
	REQUIRE(float8_t(-0x7f) - 5 == -0x82);
	REQUIRE(float8_t(-0x7f) - 6 == -0x84);
	REQUIRE(float8_t(-0x7f) - 7 == -0x84);
	REQUIRE(float8_t(-0x7f) - 8 == -0x86);

	REQUIRE(float8_t(0xf000) - (-0x100) == 0xf100);
}

TEST_CASE("Substracting unsigned flouts.") {
	REQUIRE(ufloat8_t(1) - 1 == 0);
	REQUIRE(ufloat8_t(2) - 1 == 1);

	REQUIRE(ufloat8_t(100) - 1 == 99);
	REQUIRE(ufloat8_t(100) - 99 == 1);

	REQUIRE(ufloat8_t(0xff) - 1 == 0xfe);
	REQUIRE(ufloat8_t(0xff) - 0xff == 0);
}

TEST_CASE(
    "Expect NEGATIVE_INF resulting a substraction in a too small value.") {
	REQUIRE(float8_t::LOWEST() - 1 == float8_t::NEGATIVE_INF());

	REQUIRE(float8_t(-0x70, 0x7f) - float8_t(0x70, 0x7f) ==
	        float8_t::NEGATIVE_INF());
}

TEST_CASE("Expect NEGATIVE_INF on substracting INF from NEGATIVE_INF values.") {
	REQUIRE(float8_t::NEGATIVE_INF() - float8_t::INF() ==
	        float8_t::NEGATIVE_INF());
}

TEST_CASE("Expect NOT_A_NUMBER on substracting NEGATIVE_INF and NEGATIVE_INF") {
	REQUIRE(float8_t::NEGATIVE_INF() - float8_t::NEGATIVE_INF() ==
	        float8_t::NOT_A_NUMBER());
}

TEST_CASE("Expect NOT_A_NUMBER on substracting INF and INF") {
	REQUIRE(float8_t::INF() - float8_t::INF() ==
	        float8_t::NOT_A_NUMBER());
}

TEST_CASE("Expect INF if any number is substracted from it.") {
	REQUIRE(float8_t::INF() - 1 == float8_t::INF());
	REQUIRE(float8_t(1) - float8_t::INF() ==
	        float8_t::NEGATIVE_INF());
}

TEST_CASE("Expect NEGATIVE_INF if anything is substracted from it.") {
	REQUIRE(float8_t::NEGATIVE_INF() - 1 == float8_t::NEGATIVE_INF());
	REQUIRE(float8_t(1) - float8_t::INF() ==
	        float8_t::NEGATIVE_INF());
}

TEST_CASE("Expect -= do be defined.") {
	float8_t target(3);

	target -= 1;
	REQUIRE(target == 2);

	target -= float8_t(1);
	REQUIRE(target == 1);
}
