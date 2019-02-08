#include "test_utils.hpp"

TEST_CASE("Expects the unary minus to result in a constexpression.") {
	constexpr auto result = -float8_t();
}

TEST_CASE("Expects the  unary minus operator to return the same value.") {
	REQUIRE(-float8_t() == float8_t());
	REQUIRE(-float8_t(1) == float8_t(-1));
	REQUIRE(-float8_t(-1) == float8_t(1));

	REQUIRE(-float8_t(100) == float8_t(-100));
	REQUIRE(-float8_t(-100) == float8_t(100));

	REQUIRE(-float8_t(0x7f) == float8_t(-0x7f));
	REQUIRE(-float8_t(-0x80) == float8_t(0x80));
}

TEST_CASE("Expoect -inf to be negative infinte.") {
	REQUIRE(-float8_t::INF() == float8_t::NEGATIVE_INF());
	REQUIRE(-float8_t::NEGATIVE_INF() == float8_t::INF());

	REQUIRE(-ufloat8_t::INF() == ufloat8_t::NEGATIVE_INF());
	REQUIRE(-ufloat8_t::NEGATIVE_INF() == ufloat8_t::INF());
}
