#include "test_utils.hpp"

TEST_CASE("Expect pre increment operator to work.") {
	REQUIRE(++float8_t(1) == 2);

	auto target_incremented = float8_t(1);
	auto target_previous = target_incremented++;

	REQUIRE(target_previous == 1);
	REQUIRE(target_incremented == 2);
}
