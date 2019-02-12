#include "test_utils.hpp"

TEST_CASE("Expects multiply to return a constexpression.") {
	constexpr auto result = ufloat8_t(1) * ufloat8_t(1);
	constexpr auto result_value = ufloat8_t(1) * 1;
}

TEST_CASE("Multiplication by zero results in zero.") {
	REQUIRE(ufloat8_t() * 0 == 0);
	REQUIRE(ufloat8_t() * 1 == 0);
	REQUIRE(ufloat8_t() * 3 == 0);
	REQUIRE(ufloat8_t() * 100 == 0);
	REQUIRE(ufloat8_t() * 0xff == 0);
}

TEST_CASE("Multiplication by one results in the other operand.") {
	REQUIRE(ufloat8_t(1) * 0 == 0);
	REQUIRE(ufloat8_t(1) * 1 == 1);
	REQUIRE(ufloat8_t(2) * 1 == 2);
	REQUIRE(ufloat8_t(3) * 1 == 3);
	REQUIRE(ufloat8_t(100) * 1 == 100);
	REQUIRE(ufloat8_t(0xff) * 1 == 0xff);

	REQUIRE(ufloat8_t(0x123456789) * 1 == 0x123456789);
}

TEST_CASE("Multiplication overflow") {
	REQUIRE(ufloat8_t(0x10) * 2 == 0x20);
	REQUIRE(ufloat8_t(0x100) * 2 == 0x200);
	REQUIRE(ufloat8_t(0x1000) * 2 == 0x2000);
	REQUIRE(ufloat8_t(0x10000) * 2 == 0x20000);
	REQUIRE(ufloat8_t(0x100000) * 2 == 0x200000);

	REQUIRE(ufloat8_t(0x10) * 0x20 == 0x200);
	REQUIRE(ufloat8_t(0x100) * 0x20 == 0x2000);
	REQUIRE(ufloat8_t(0x1000) * 0x20 == 0x20000);
	REQUIRE(ufloat8_t(0x10000) * 0x20 == 0x200000);
	REQUIRE(ufloat8_t(0x100000) * 0x20 == 0x2000000);

	REQUIRE(ufloat8_t(0x10) * 0x10 == 0x100);
	REQUIRE(ufloat8_t(0x100) * 0x100 == 0x10000);
	REQUIRE(ufloat8_t(0x1000) * 0x1000 == 0x1000000);
	REQUIRE(ufloat8_t(0x10000) * 0x10000 == 0x100000000);
	REQUIRE(ufloat8_t(0x100000) * 0x100000 == 0x10000000000);
}

TEST_CASE("Mutliplication with both negative factors.") {
	REQUIRE(float8_t(-1) * -1 == 1);
	REQUIRE(float8_t(-2) * -2 == 4);
	REQUIRE(float8_t(-4) * -4 == 16);
	REQUIRE(float8_t(-4) * -4 == 16);
	REQUIRE(float8_t(-10) * -10 == 100);
	REQUIRE(float8_t(-0x80) * -0x80 == 0x4000);
}

TEST_CASE("Mutliplication with one negative and one positive factor.") {
	REQUIRE(float8_t(1) * -1 == -1);
	REQUIRE(float8_t(2) * -2 == -4);
	REQUIRE(float8_t(4) * -4 == -16);
	REQUIRE(float8_t(4) * -4 == -16);
	REQUIRE(float8_t(10) * -10 == -100);
	REQUIRE(float8_t(0x80) * -0x80 == -0x4000);

	// Other way around.
	REQUIRE(float8_t(-1) * 1 == -1);
	REQUIRE(float8_t(-2) * 2 == -4);
	REQUIRE(float8_t(-4) * 4 == -16);
	REQUIRE(float8_t(-4) * 4 == -16);
	REQUIRE(float8_t(-10) * 10 == -100);
	REQUIRE(float8_t(-0x80) * 0x80 == -0x4000);
}

TEST_CASE("Expect *= do be defined.") {
	float8_t target(3);

	target *= 2;
	REQUIRE(target == 6);

	target *= float8_t(3);
	REQUIRE(target == 18);
}

TEST_CASE("Don't miss too much accuracy on large numbers") {
	REQUIRE(float8_t(12345678) * 1 == 12345678);
	REQUIRE(float8_t(-12345678) * 1 == -12345678);
	REQUIRE(float8_t(12345678) * -1 == -12345678);
	REQUIRE(float8_t(-12345678) * -1 == 12345678);

	REQUIRE(float8_t(26) * 26 == 676);
	REQUIRE(float8_t(-26) * 26 == -676);
	REQUIRE(float8_t(26) * -26 == -676);
	REQUIRE(float8_t(-26) * -26 == 676);
}
