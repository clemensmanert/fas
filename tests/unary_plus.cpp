#include "test_utils.hpp"

TEST_CASE("Expects the unary plus to return a constexpr.") {
	constexpr auto result = +float8_t();
}

TEST_CASE("Expects the  unary plus operator to return the same value.") {
	REQUIRE(+float8_t() == float8_t());
	REQUIRE(+float8_t(1) == float8_t(1));
	REQUIRE(+float8_t(-1) == float8_t(-1));

	REQUIRE(+float8_t(100) == float8_t(100));
	REQUIRE(+float8_t(-100) == float8_t(-100));
}
