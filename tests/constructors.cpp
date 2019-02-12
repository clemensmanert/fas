#include "test_utils.hpp"

TEST_CASE("Expect constructors cabable creating constexpressions") {
	constexpr auto default_ctr = float8_t();
	constexpr auto copy_ctr = float8_t(default_ctr);

	constexpr auto value_ctr = float8_t(1);
	constexpr auto value_ctr2 = float8_t(1, 2);
}

TEST_CASE("Expect normalizing mantissa in too large exponent"
          " to result in infinity.") {
	REQUIRE(ufloat8_t(0x100, 0x7f).mantissa() == 0);
	REQUIRE(ufloat8_t(0x100, 0x7f).exponent() == 1);
}

TEST_CASE("Expect exponent too large to result in infinity.") {
	REQUIRE(ufloat8_t(0x1, 0x80).mantissa() == 0);
	REQUIRE(ufloat8_t(0x1, 0x80).exponent() == 1);
}

TEST_CASE("Expect normalizing too small mantissa in too small exponent"
          " resulting into -infinity.") {
	REQUIRE(ufloat8_t(0x10, -0x100).mantissa() == 0);
	REQUIRE(ufloat8_t(0x10, -0x100).exponent() == 2);
}

TEST_CASE("Expect NEGATIVE_INFINITY on underflow.") {
	REQUIRE(float8_t(-0x100, 0x7f).mantissa() == 0);
	REQUIRE(float8_t(-0x100, 0x7f).exponent() == 2);
}

TEST_CASE("Expect ZERO on exponent underflow, for positive mantissa.") {
	REQUIRE(float8_t(0x1, -0x80).mantissa() == 0);
	REQUIRE(float8_t(0x1, -0x80).exponent() == 0);
}

TEST_CASE("Expect ZERO on exponent underflow, for negative mantissa.") {
	REQUIRE(float8_t(-0x1, -0x80).mantissa() == 0);
	REQUIRE(float8_t(-0x1, -0x80).exponent() == 0);
}

TEST_CASE("Default ctor should create Zero as value..") {
	REQUIRE(ufloat8_t(0).mantissa() == 0x0);
	REQUIRE(float8_t(0).mantissa() == 0x0);
}

TEST_CASE("Default value for exponent is 1.") {
	// Unsigned mantissa
	REQUIRE(ufloat8_t(0).mantissa() == 0x00);
	REQUIRE(ufloat8_t(0).exponent() == 0);

	REQUIRE(ufloat8_t(1).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1).exponent() == -7);

	REQUIRE(ufloat8_t(2).mantissa() == 0x80);
	REQUIRE(ufloat8_t(2).exponent() == -6);

	REQUIRE(ufloat8_t(3).mantissa() == 0xC0);
	REQUIRE(ufloat8_t(3).exponent() == -6);

	REQUIRE(ufloat8_t(4).mantissa() == 0x80);
	REQUIRE(ufloat8_t(4).exponent() == -5);

	REQUIRE(ufloat8_t(5).mantissa() == 0xA0);
	REQUIRE(ufloat8_t(5).exponent() == -5);

	REQUIRE(ufloat8_t(6).mantissa() == 0xC0);
	REQUIRE(ufloat8_t(6).exponent() == -5);

	REQUIRE(ufloat8_t(7).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7).exponent() == -5);

	REQUIRE(ufloat8_t(8).mantissa() == 0x80);
	REQUIRE(ufloat8_t(8).exponent() == -4);

	REQUIRE(ufloat8_t(9).mantissa() == 0x90);
	REQUIRE(ufloat8_t(9).exponent() == -4);

	REQUIRE(ufloat8_t(10).mantissa() == 0xA0);
	REQUIRE(ufloat8_t(10).exponent() == -4);

	REQUIRE(ufloat8_t(11).mantissa() == 0xB0);
	REQUIRE(ufloat8_t(11).exponent() == -4);

	REQUIRE(ufloat8_t(12).mantissa() == 0xC0);
	REQUIRE(ufloat8_t(12).exponent() == -4);

	REQUIRE(ufloat8_t(13).mantissa() == 0xD0);
	REQUIRE(ufloat8_t(13).exponent() == -4);

	REQUIRE(ufloat8_t(14).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(14).exponent() == -4);

	REQUIRE(ufloat8_t(15).mantissa() == 0xF0);
	REQUIRE(ufloat8_t(15).exponent() == -4);

	REQUIRE(ufloat8_t(16).mantissa() == 0x80);
	REQUIRE(ufloat8_t(16).exponent() == -3);

	REQUIRE(ufloat8_t(17).mantissa() == 0x88);
	REQUIRE(ufloat8_t(17).exponent() == -3);

	REQUIRE(ufloat8_t(31).mantissa() == 0xf8);
	REQUIRE(ufloat8_t(31).exponent() == -3);

	REQUIRE(ufloat8_t(32).mantissa() == 0x80);
	REQUIRE(ufloat8_t(32).exponent() == -2);

	REQUIRE(ufloat8_t(33).mantissa() == 0x84);
	REQUIRE(ufloat8_t(33).exponent() == -2);

	REQUIRE(ufloat8_t(64).mantissa() == 0x80);
	REQUIRE(ufloat8_t(64).exponent() == -1);

	REQUIRE(ufloat8_t(128).mantissa() == 0x80);
	REQUIRE(ufloat8_t(128).exponent() == 0);

	// Signed mantissa
	REQUIRE(float8_t(0).mantissa() == 0x00);
	REQUIRE(float8_t(0).exponent() == 0);

	REQUIRE(float8_t(1).mantissa() == 0x40);
	REQUIRE(float8_t(1).exponent() == -6);

	REQUIRE(float8_t(2).mantissa() == 0x40);
	REQUIRE(float8_t(2).exponent() == -5);

	REQUIRE(float8_t(3).mantissa() == 0x60);
	REQUIRE(float8_t(3).exponent() == -5);

	REQUIRE(float8_t(4).mantissa() == 0x40);
	REQUIRE(float8_t(4).exponent() == -4);

	REQUIRE(float8_t(5).mantissa() == 0x50);
	REQUIRE(float8_t(5).exponent() == -4);

	REQUIRE(float8_t(6).mantissa() == 0x60);
	REQUIRE(float8_t(6).exponent() == -4);

	REQUIRE(float8_t(7).mantissa() == 0x70);
	REQUIRE(float8_t(7).exponent() == -4);

	REQUIRE(float8_t(8).mantissa() == 0x40);
	REQUIRE(float8_t(8).exponent() == -3);

	REQUIRE(float8_t(9).mantissa() == 0x48);
	REQUIRE(float8_t(9).exponent() == -3);

	REQUIRE(float8_t(10).mantissa() == 0x50);
	REQUIRE(float8_t(10).exponent() == -3);

	REQUIRE(float8_t(11).mantissa() == 0x58);
	REQUIRE(float8_t(11).exponent() == -3);

	REQUIRE(float8_t(12).mantissa() == 0x60);
	REQUIRE(float8_t(12).exponent() == -3);

	REQUIRE(float8_t(13).mantissa() == 0x68);
	REQUIRE(float8_t(13).exponent() == -3);

	REQUIRE(float8_t(14).mantissa() == 0x70);
	REQUIRE(float8_t(14).exponent() == -3);

	REQUIRE(float8_t(15).mantissa() == 0x78);
	REQUIRE(float8_t(15).exponent() == -3);

	REQUIRE(float8_t(16).mantissa() == 0x40);
	REQUIRE(float8_t(16).exponent() == -2);

	REQUIRE(float8_t(17).mantissa() == 0x44);
	REQUIRE(float8_t(17).exponent() == -2);

	REQUIRE(float8_t(31).mantissa() == 0x7c);
	REQUIRE(float8_t(31).exponent() == -2);

	REQUIRE(float8_t(32).mantissa() == 0x40);
	REQUIRE(float8_t(32).exponent() == -1);

	REQUIRE(float8_t(33).mantissa() == 0x42);
	REQUIRE(float8_t(33).exponent() == -1);

	REQUIRE(float8_t(64).mantissa() == 0x40);
	REQUIRE(float8_t(64).exponent() == 0);

	REQUIRE(float8_t(-0).mantissa() == 0);

	REQUIRE(float8_t(-1).mantissa() == -0x80);
	REQUIRE(float8_t(-1).exponent() == -7);

	REQUIRE(float8_t(-2).mantissa() == -0x80);
	REQUIRE(float8_t(-2).exponent() == -6);

	REQUIRE(float8_t(-3).mantissa() == -0x60);
	REQUIRE(float8_t(-3).exponent() == -5);

	REQUIRE(float8_t(-4).mantissa() == -0x80);
	REQUIRE(float8_t(-4).exponent() == -5);

	REQUIRE(float8_t(-5).mantissa() == -0x50);
	REQUIRE(float8_t(-5).exponent() == -4);

	REQUIRE(float8_t(-6).mantissa() == -0x60);
	REQUIRE(float8_t(-6).exponent() == -4);

	REQUIRE(float8_t(-7).mantissa() == -0x70);
	REQUIRE(float8_t(-7).exponent() == -4);

	REQUIRE(float8_t(-8).mantissa() == -0x80);
	REQUIRE(float8_t(-8).exponent() == -4);

	REQUIRE(float8_t(-9).mantissa() == -0x48);
	REQUIRE(float8_t(-9).exponent() == -3);

	REQUIRE(float8_t(-10).mantissa() == -0x50);
	REQUIRE(float8_t(-10).exponent() == -3);

	REQUIRE(float8_t(-11).mantissa() == -0x58);
	REQUIRE(float8_t(-11).exponent() == -3);

	REQUIRE(float8_t(-12).mantissa() == -0x60);
	REQUIRE(float8_t(-12).exponent() == -3);

	REQUIRE(float8_t(-13).mantissa() == -0x68);
	REQUIRE(float8_t(-13).exponent() == -3);

	REQUIRE(float8_t(-14).mantissa() == -0x70);
	REQUIRE(float8_t(-14).exponent() == -3);

	REQUIRE(float8_t(-15).mantissa() == -0x78);
	REQUIRE(float8_t(-15).exponent() == -3);

	REQUIRE(float8_t(-16).mantissa() == -0x80);
	REQUIRE(float8_t(-16).exponent() == -3);

	REQUIRE(float8_t(-17).mantissa() == -0x44);
	REQUIRE(float8_t(-17).exponent() == -2);

	REQUIRE(float8_t(-31).mantissa() == -0x7c);
	REQUIRE(float8_t(-31).exponent() == -2);

	REQUIRE(float8_t(-32).mantissa() == -0x80);
	REQUIRE(float8_t(-32).exponent() == -2);

	REQUIRE(float8_t(-33).mantissa() == -0x42);
	REQUIRE(float8_t(-33).exponent() == -1);

	REQUIRE(float8_t(-64).mantissa() == -0x80);
	REQUIRE(float8_t(-64).exponent() == -1);
}

TEST_CASE("Exponent = 0 results in the  mantissa's value") {
	// unsigned
	REQUIRE(ufloat8_t(0, 0).mantissa() == 0x00);
	REQUIRE(ufloat8_t(0, 0).exponent() == 0);

	REQUIRE(ufloat8_t(1, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 0).exponent() == -7);

	REQUIRE(ufloat8_t(2, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(2, 0).exponent() == -6);

	REQUIRE(ufloat8_t(3, 0).mantissa() == 0xC0);
	REQUIRE(ufloat8_t(3, 0).exponent() == -6);

	REQUIRE(ufloat8_t(4, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(4, 0).exponent() == -5);

	REQUIRE(ufloat8_t(5, 0).mantissa() == 0xA0);
	REQUIRE(ufloat8_t(5, 0).exponent() == -5);

	REQUIRE(ufloat8_t(6, 0).mantissa() == 0xC0);
	REQUIRE(ufloat8_t(6, 0).exponent() == -5);

	REQUIRE(ufloat8_t(7, 0).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 0).exponent() == -5);

	REQUIRE(ufloat8_t(8, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(8, 0).exponent() == -4);

	REQUIRE(ufloat8_t(9, 0).mantissa() == 0x90);
	REQUIRE(ufloat8_t(9, 0).exponent() == -4);

	REQUIRE(ufloat8_t(10, 0).mantissa() == 0xA0);
	REQUIRE(ufloat8_t(10, 0).exponent() == -4);

	REQUIRE(ufloat8_t(11, 0).mantissa() == 0xB0);
	REQUIRE(ufloat8_t(11, 0).exponent() == -4);

	REQUIRE(ufloat8_t(12, 0).mantissa() == 0xC0);
	REQUIRE(ufloat8_t(12, 0).exponent() == -4);

	REQUIRE(ufloat8_t(13, 0).mantissa() == 0xD0);
	REQUIRE(ufloat8_t(13, 0).exponent() == -4);

	REQUIRE(ufloat8_t(14, 0).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(14, 0).exponent() == -4);

	REQUIRE(ufloat8_t(15, 0).mantissa() == 0xF0);
	REQUIRE(ufloat8_t(15, 0).exponent() == -4);

	REQUIRE(ufloat8_t(16, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(16, 0).exponent() == -3);

	REQUIRE(ufloat8_t(32, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(32, 0).exponent() == -2);

	REQUIRE(ufloat8_t(64, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(64, 0).exponent() == -1);

	REQUIRE(ufloat8_t(128, 0).mantissa() == 0x80);
	REQUIRE(ufloat8_t(128, 0).exponent() == 0);

	// unsigned
	// Signed mantissa
	REQUIRE(float8_t(0, 0).mantissa() == 0x00);
	REQUIRE(float8_t(0, 0).exponent() == 0);

	REQUIRE(float8_t(1, 0).mantissa() == 0x40);
	REQUIRE(float8_t(1, 0).exponent() == -6);

	REQUIRE(float8_t(2, 0).mantissa() == 0x40);
	REQUIRE(float8_t(2, 0).exponent() == -5);

	REQUIRE(float8_t(3, 0).mantissa() == 0x60);
	REQUIRE(float8_t(3, 0).exponent() == -5);

	REQUIRE(float8_t(4, 0).mantissa() == 0x40);
	REQUIRE(float8_t(4, 0).exponent() == -4);

	REQUIRE(float8_t(5, 0).mantissa() == 0x50);
	REQUIRE(float8_t(5, 0).exponent() == -4);

	REQUIRE(float8_t(6, 0).mantissa() == 0x60);
	REQUIRE(float8_t(6, 0).exponent() == -4);

	REQUIRE(float8_t(7, 0).mantissa() == 0x70);
	REQUIRE(float8_t(7, 0).exponent() == -4);

	REQUIRE(float8_t(8, 0).mantissa() == 0x40);
	REQUIRE(float8_t(8, 0).exponent() == -3);

	REQUIRE(float8_t(9, 0).mantissa() == 0x48);
	REQUIRE(float8_t(9, 0).exponent() == -3);

	REQUIRE(float8_t(10, 0).mantissa() == 0x50);
	REQUIRE(float8_t(10, 0).exponent() == -3);

	REQUIRE(float8_t(11, 0).mantissa() == 0x58);
	REQUIRE(float8_t(11, 0).exponent() == -3);

	REQUIRE(float8_t(12, 0).mantissa() == 0x60);
	REQUIRE(float8_t(12, 0).exponent() == -3);

	REQUIRE(float8_t(13, 0).mantissa() == 0x68);
	REQUIRE(float8_t(13, 0).exponent() == -3);

	REQUIRE(float8_t(14, 0).mantissa() == 0x70);
	REQUIRE(float8_t(14, 0).exponent() == -3);

	REQUIRE(float8_t(15, 0).mantissa() == 0x78);
	REQUIRE(float8_t(15, 0).exponent() == -3);

	REQUIRE(float8_t(16, 0).mantissa() == 0x40);
	REQUIRE(float8_t(16, 0).exponent() == -2);

	REQUIRE(float8_t(32, 0).mantissa() == 0x40);
	REQUIRE(float8_t(32, 0).exponent() == -1);

	REQUIRE(float8_t(64, 0).mantissa() == 0x40);
	REQUIRE(float8_t(64, 0).exponent() == 0);
}

TEST_CASE("Exponent parameter in the constructor.") {
	// signed
	REQUIRE(ufloat8_t(1, 1).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 1).exponent() == -6);

	REQUIRE(ufloat8_t(1, 2).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 2).exponent() == -5);

	REQUIRE(ufloat8_t(1, 3).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 3).exponent() == -4);

	REQUIRE(ufloat8_t(1, 4).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 4).exponent() == -3);

	REQUIRE(ufloat8_t(1, 5).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 5).exponent() == -2);

	REQUIRE(ufloat8_t(1, 6).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 6).exponent() == -1);

	REQUIRE(ufloat8_t(1, 7).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 7).exponent() == 0);

	REQUIRE(ufloat8_t(1, 8).mantissa() == 0x80);
	REQUIRE(ufloat8_t(1, 8).exponent() == 1);

	REQUIRE(ufloat8_t(7, 1).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 1).exponent() == -4);

	REQUIRE(ufloat8_t(7, 2).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 2).exponent() == -3);

	REQUIRE(ufloat8_t(7, 3).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 3).exponent() == -2);

	REQUIRE(ufloat8_t(7, 4).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 4).exponent() == -1);

	REQUIRE(ufloat8_t(7, 5).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 5).exponent() == 0);

	REQUIRE(ufloat8_t(7, 6).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 6).exponent() == 1);

	REQUIRE(ufloat8_t(7, 7).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 7).exponent() == 2);

	REQUIRE(ufloat8_t(7, 8).mantissa() == 0xE0);
	REQUIRE(ufloat8_t(7, 8).exponent() == 3);

	// unsigned
	REQUIRE(float8_t(1, 1).mantissa() == 0x40);
	REQUIRE(float8_t(1, 1).exponent() == -5);

	REQUIRE(float8_t(1, 2).mantissa() == 0x40);
	REQUIRE(float8_t(1, 2).exponent() == -4);

	REQUIRE(float8_t(1, 3).mantissa() == 0x40);
	REQUIRE(float8_t(1, 3).exponent() == -3);

	REQUIRE(float8_t(1, 4).mantissa() == 0x40);
	REQUIRE(float8_t(1, 4).exponent() == -2);

	REQUIRE(float8_t(1, 5).mantissa() == 0x40);
	REQUIRE(float8_t(1, 5).exponent() == -1);

	REQUIRE(float8_t(1, 6).mantissa() == 0x40);
	REQUIRE(float8_t(1, 6).exponent() == -0);

	REQUIRE(float8_t(1, 7).mantissa() == 0x40);
	REQUIRE(float8_t(1, 7).exponent() == 1);

	REQUIRE(float8_t(1, 8).mantissa() == 0x40);
	REQUIRE(float8_t(1, 8).exponent() == 2);

	REQUIRE(float8_t(7, 1).mantissa() == 0x70);
	REQUIRE(float8_t(7, 1).exponent() == -3);

	REQUIRE(float8_t(7, 2).mantissa() == 0x70);
	REQUIRE(float8_t(7, 2).exponent() == -2);

	REQUIRE(float8_t(7, 3).mantissa() == 0x70);
	REQUIRE(float8_t(7, 3).exponent() == -1);

	REQUIRE(float8_t(7, 4).mantissa() == 0x70);
	REQUIRE(float8_t(7, 4).exponent() == -0);

	REQUIRE(float8_t(7, 5).mantissa() == 0x70);
	REQUIRE(float8_t(7, 5).exponent() == 1);

	REQUIRE(float8_t(7, 6).mantissa() == 0x70);
	REQUIRE(float8_t(7, 6).exponent() == 2);

	REQUIRE(float8_t(7, 7).mantissa() == 0x70);
	REQUIRE(float8_t(7, 7).exponent() == 3);

	REQUIRE(float8_t(7, 8).mantissa() == 0x70);
	REQUIRE(float8_t(7, 8).exponent() == 4);
}

TEST_CASE("Values to large for mantissa shall be shrinked") {
	// unsigned
	REQUIRE(ufloat8_t(0x100).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x100).exponent() == 0x1);

	REQUIRE(ufloat8_t(0x1000).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x1000).exponent() == 5);

	REQUIRE(ufloat8_t(0x10000).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x10000).exponent() == 0x9);

	REQUIRE(ufloat8_t(0x100000).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x100000).exponent() == 13);

	REQUIRE(ufloat8_t(0x1000000).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x1000000).exponent() == 17);

	REQUIRE(ufloat8_t(0x10000000).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x10000000).exponent() == 21);

	// signed
	REQUIRE(float8_t(0x100).mantissa() == 0x40);
	REQUIRE(float8_t(0x100).exponent() == 0x2);

	REQUIRE(float8_t(0x1000).mantissa() == 0x40);
	REQUIRE(float8_t(0x1000).exponent() == 6);

	REQUIRE(float8_t(0x10000).mantissa() == 0x40);
	REQUIRE(float8_t(0x10000).exponent() == 10);

	REQUIRE(float8_t(0x100000).mantissa() == 0x40);
	REQUIRE(float8_t(0x100000).exponent() == 14);

	REQUIRE(float8_t(0x1000000).mantissa() == 0x40);
	REQUIRE(float8_t(0x1000000).exponent() == 18);

	REQUIRE(float8_t(0x10000000).mantissa() == 0x40);
	REQUIRE(float8_t(0x10000000).exponent() == 22);

	// signed with negative values
	REQUIRE(float8_t(-0x100).mantissa() == -0x80);
	REQUIRE(float8_t(-0x100).exponent() == 0x1);

	REQUIRE(float8_t(-0x1000).mantissa() == -0x80);
	REQUIRE(float8_t(-0x1000).exponent() == 5);

	REQUIRE(float8_t(-0x10000).mantissa() == -0x80);
	REQUIRE(float8_t(-0x10000).exponent() == 9);

	REQUIRE(float8_t(-0x100000).mantissa() == -0x80);
	REQUIRE(float8_t(-0x100000).exponent() == 13);

	REQUIRE(float8_t(-0x1000000).mantissa() == -0x80);
	REQUIRE(float8_t(-0x1000000).exponent() == 17);

	REQUIRE(float8_t(-0x10000000).mantissa() == -0x80);
	REQUIRE(float8_t(-0x10000000).exponent() == 21);
}

TEST_CASE("Smallest possible value on signed 7 bit mantissa") {
	REQUIRE(float8_t(-0x80).mantissa() == -128);
	REQUIRE(float8_t(-0x80).exponent() == 0);
}

TEST_CASE("Largest possible value on signed 7 bit mantissa") {
	REQUIRE(float8_t(0x7f).mantissa() == 0x7f);
	REQUIRE(float8_t(0x7f).exponent() == 0);
}

TEST_CASE("Same values constructed with different mantissa/exponent should be"
          "shifted to the same byte values") {
	// unsigned
	REQUIRE(ufloat8_t(0x1, 7).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x1, 7).exponent() == 0);
	REQUIRE(ufloat8_t(0x80, -7).mantissa() == 0x80);
	REQUIRE(ufloat8_t(0x80, -7).exponent() == -7);

	// signed
	REQUIRE(float8_t(0x1, 6).mantissa() == 0x40);
	REQUIRE(float8_t(0x1, 6).exponent() == 0);
	REQUIRE(float8_t(0x40, -6).mantissa() == 0x40);
	REQUIRE(float8_t(0x40, -6).exponent() == -6);
}

TEST_CASE("Do not shift if its impossible") {
	// unsigned
	REQUIRE(ufloat8_t(0xff, 0).mantissa() == 0xff);
	REQUIRE(ufloat8_t(0xff, 0).exponent() == 0);

	// signed
	REQUIRE(float8_t(0x7f, 0).mantissa() == 0x7f);
	REQUIRE(float8_t(0x7f, 0).exponent() == 0);
}

TEST_CASE("Checks correctnes if the represented type is smaller "
          "than the mantissas type.") {
	using smaller_type = int8_t;
	using larger_type = int32_t;
	using exponent_type = int16_t;

	using Fp_Target = Float<larger_type, exponent_type>;

	// Positive value
	REQUIRE(Fp_Target((smaller_type)0x1).mantissa() == 0x40000000);
	REQUIRE(Fp_Target((smaller_type)0x1).exponent() == -30);

	// Negative value
	REQUIRE(Fp_Target((smaller_type)-0x1).mantissa() == 0x80000000);
	REQUIRE(Fp_Target((smaller_type)-0x1).exponent() == -31);
}

using Base3FloatT = Float<int16_t, int16_t, 3>;

TEST_CASE("Tests whether the type creates correct values for base 3.") {
	REQUIRE(Base3FloatT(0, 0).mantissa() == 0);
	REQUIRE(Base3FloatT(0, 0).exponent() == 0);

	REQUIRE(Base3FloatT(1).mantissa() == 0x4c'e3);
	REQUIRE(Base3FloatT(1).exponent() == -9);
}
