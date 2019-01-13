#include "test_utils.hpp"

TEST_CASE("Comparison of values should return a constexpression.") {
	constexpr auto smaller = float8_t(2) < float8_t(3);
	constexpr auto greater = float8_t(2) > float8_t(3);

	constexpr auto smaller_equals = float8_t(2) <= float8_t(3);
	constexpr auto greater_equals = float8_t(2) >= float8_t(3);

	constexpr auto smaller_value = float8_t(2) < 1;
	constexpr auto greater_value = float8_t(2) > 1;

	constexpr auto smaller_equals_value = float8_t(2) <= 1;
	constexpr auto greater_equals_value = float8_t(2) >= 1;
}

TEST_CASE("Compare values with same exponent.") {
	REQUIRE(float8_t(2) < float8_t(3));
	REQUIRE(float8_t(3) > float8_t(2));

	REQUIRE(float8_t(2) <= float8_t(3));
	REQUIRE(float8_t(3) >= float8_t(2));
}

TEST_CASE("Compare values with different exponent.") {
	REQUIRE(float8_t(1) < float8_t(2));
	REQUIRE(float8_t(2) > float8_t(1));

	REQUIRE(float8_t(1) > float8_t(-1));
	REQUIRE(float8_t(2) > float8_t(-2));

	REQUIRE(float8_t(1) >= float8_t(-1));
	REQUIRE(float8_t(2) >= float8_t(-2));

	REQUIRE(float8_t(-1) < float8_t(1));
	REQUIRE(float8_t(-2) < float8_t(2));

	REQUIRE(float8_t(-1) <= float8_t(1));
	REQUIRE(float8_t(-2) <= float8_t(2));

	REQUIRE(float8_t::MAX() > float8_t::MIN());
	REQUIRE(float8_t::MAX() >= float8_t::MIN());

	REQUIRE(float8_t::MAX() > float8_t::LOWEST());
	REQUIRE(float8_t::MAX() >= float8_t::LOWEST());

	REQUIRE(float8_t::MIN() < float8_t::LOWEST());
	REQUIRE(float8_t::MIN() <= float8_t::LOWEST());

	REQUIRE(float8_t::MIN() < float8_t::MAX());
	REQUIRE(float8_t::MIN() > float8_t::ZERO());

	REQUIRE(float8_t::LOWEST() < float8_t::MAX());
	REQUIRE(float8_t::LOWEST() < float8_t::ZERO());

	REQUIRE(float8_t::ZERO() < 1);
	REQUIRE(float8_t::ZERO() > -1);

	REQUIRE(float8_t::ZERO() < float8_t::MAX());
	REQUIRE(float8_t::ZERO() < float8_t::MIN());
	REQUIRE(float8_t::ZERO() > float8_t::LOWEST());
}
