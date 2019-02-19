#include "test_utils.hpp"

TEST_CASE("Expect predecrement operator to work.") {
	REQUIRE(--float8_t(2) == 1);
}

TEST_CASE("Expect postdecrement operator to work.") {
	auto target_decremented = float8_t(2);
	auto target_previous = target_decremented--;

	REQUIRE(target_previous == 2);
	REQUIRE(target_decremented == 1);
}
