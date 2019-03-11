#include "test_utils.hpp"

TEST_CASE("Expects add to return a constexpression.") {
	constexpr auto result = ufloat8_t(1) + ufloat8_t(1);
	constexpr auto result_value = ufloat8_t(1) + 1;
}

TEST_CASE("Adding Zero does not change the value.") {
	REQUIRE(ufloat8_t() + 0 == 0);
	REQUIRE(ufloat8_t(1) + 0 == 1);
	REQUIRE(ufloat8_t(2) + 0 == 2);
	REQUIRE(ufloat8_t(3) + 0 == 3);
	REQUIRE(ufloat8_t(4) + 0 == 4);
	REQUIRE(ufloat8_t(5) + 0 == 5);
	REQUIRE(ufloat8_t(6) + 0 == 6);
	REQUIRE(ufloat8_t(7) + 0 == 7);
}

TEST_CASE("Adding to Zero does not change the value") {
	REQUIRE(ufloat8_t(0) + 1 == 1);
}

TEST_CASE("Adding two values") {
	REQUIRE(ufloat8_t(0x80, -7) + ufloat8_t(0x80, -7) ==
	        ufloat8_t(0x80, -6));

	// Lhs is the larger value.
	REQUIRE(ufloat8_t(2, 4) + 3 == 35);
	REQUIRE(ufloat8_t(1) + 1 == 2);
	REQUIRE(ufloat8_t(0x10) + 0x10 == 0x20);
	REQUIRE(ufloat8_t(0xF0) + 0xF == 0xFF);
	REQUIRE(ufloat8_t(20) + 20 == 40);
	REQUIRE(ufloat8_t(1, 2) + ufloat8_t(2, 3) == 20);
	REQUIRE(ufloat8_t(1, 2) + ufloat8_t(3, 4) == 52);
	REQUIRE(ufloat8_t(1, 8) + ufloat8_t(1, 8) == 512);
	REQUIRE(ufloat8_t(1, 10) + ufloat8_t(1, 10) == 2048);
	REQUIRE(ufloat8_t(2, 9) + ufloat8_t(4, 8) == 2048);

	REQUIRE(ufloat8_t(10, 0) + 1 == 11);
	REQUIRE(ufloat8_t(100, 0) + 1 == 101);

	REQUIRE(ufloat8_t(0xfe, 0) + 2 == 0x0fe + 2);
	REQUIRE(ufloat8_t(0xfe, 0) + 4 == 0x0fe + 4);
	REQUIRE(ufloat8_t(0xfe, 0) + 6 == 0x0fe + 6);
	REQUIRE(ufloat8_t(0xfe, 0) + 8 == 0x0fe + 8);
	REQUIRE(ufloat8_t(0xfe, 0) + 0x10 == 0x0fe + 0x10);
	REQUIRE(ufloat8_t(0xfe, 0) + 0x20 == 0x0fe + 0x20);
	REQUIRE(ufloat8_t(0xfe, 0) + 0x40 == 0x0fe + 0x40);
	REQUIRE(ufloat8_t(0xfe, 0) + 0x80 == 0x0fe + 0x80);
	REQUIRE(ufloat8_t(0xfe, 0) + 0xf0 == 0x0fe + 0xf0);
	REQUIRE(ufloat8_t(0xfe, 0) + 0xfe == 0x0fe + 0xfe);

	// Rhs is the larger value.
	REQUIRE(ufloat8_t(0x1, 0) + 0x2 == 3);
	REQUIRE(ufloat8_t(0x1, 0) + 0x4 == 5);
	REQUIRE(ufloat8_t(0x1, 0) + 0x4 == 5);
	REQUIRE(ufloat8_t(0x1, 0) + 0x8 == 9);
	REQUIRE(ufloat8_t(0x1, 0) + 0x10 == 0x11);
	REQUIRE(ufloat8_t(0x1, 0) + 0x20 == 0x21);
	REQUIRE(ufloat8_t(0x1, 0) + 0x40 == 0x41);
}

TEST_CASE("Adding negative values") {
	REQUIRE(float8_t(1) + (-1) == 0);
	REQUIRE(float8_t(3) + (-1) == 2);
	REQUIRE(float8_t(0x7f) + (-1) == 0x7e);

	REQUIRE(float8_t(1) + (-1) == 0);
	REQUIRE(float8_t(3) + (-3) == 0);
	REQUIRE(float8_t(0x7f) + (-0x7f) == 0);

	REQUIRE(float8_t(0x10) + (-0x8) == 0x8);
	REQUIRE(float8_t(0x7f) + (-0x7f) == 0);
	REQUIRE(float8_t(0x7f) + (-0x7f) == 0);
}

TEST_CASE("Adding negative values to negative targets.") {
	REQUIRE(float8_t(-1) + (-1) == -2);
	REQUIRE(float8_t(-0x40) + (-0x40) == -0x80);
}

TEST_CASE("Adds negative value to negative where the result loses precision.",
          "[two_negatives_precision_lost]") {
	REQUIRE(float8_t(-0x80) + (-0x2) == -0x82);
}

TEST_CASE("Expect INF on too large value.") {
	REQUIRE(float8_t::MAX() + 1 == float8_t::INF());

	REQUIRE(float8_t(0x70, 0x7f) + float8_t(0x70, 0x7f) ==
	        float8_t::INF());
}

TEST_CASE("Expect NEGATIVE_INF on too small value.") {
	REQUIRE(float8_t::LOWEST() + -1 == float8_t::NEGATIVE_INF());
	REQUIRE(float8_t(-0x70, 0x7f) + float8_t(-0x70, 0x7f) ==
	        float8_t::NEGATIVE_INF());
}

TEST_CASE("Expect INF on adding two INF values.") {
	REQUIRE(float8_t::INF() + float8_t::INF() == float8_t::INF());
}

TEST_CASE("Expect NEGATIVE_INF() on adding two NEGATIVE_INF() values.") {
	REQUIRE(float8_t::NEGATIVE_INF() + float8_t::NEGATIVE_INF() ==
	        float8_t::NEGATIVE_INF());
}

TEST_CASE("Expect NOT_A_NUMBER on adding INF() and NEGATIVE_INF()") {
	REQUIRE(float8_t::NEGATIVE_INF() + float8_t::INF() ==
	        float8_t::NOT_A_NUMBER());

	REQUIRE(float8_t::INF() + float8_t::NEGATIVE_INF() ==
	        float8_t::NOT_A_NUMBER());
}

TEST_CASE("Expect INF() if anything is added to it.") {
	REQUIRE(float8_t::INF() + 1 == float8_t::INF());
	REQUIRE(float8_t(1) + float8_t::INF() == float8_t::INF());
}

TEST_CASE("Expect NEGATIVE_INF() if anything is added to it.") {
	REQUIRE(float8_t::NEGATIVE_INF() + 1 == float8_t::NEGATIVE_INF());

	REQUIRE(float8_t(1) + float8_t::NEGATIVE_INF() ==
	        float8_t::NEGATIVE_INF());
}

TEST_CASE("Expect += do be defined.") {
	float8_t target(1);

	target += 1;
	REQUIRE(target == 2);

	target += float8_t(1);
	REQUIRE(target == 3);
}
