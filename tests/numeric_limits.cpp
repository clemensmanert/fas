#include "test_utils.hpp"

TEST_CASE("Expect to fullfill numeric limits.") {
	REQUIRE(std::numeric_limits<float8_t>::max().mantissa() == 0x7f);
	REQUIRE(std::numeric_limits<float8_t>::max().exponent() == 0x7f);

	REQUIRE(std::numeric_limits<float8_t>::min().mantissa() == 0x01);
	REQUIRE(std::numeric_limits<float8_t>::min().exponent() == -0x80);

	REQUIRE(std::numeric_limits<float8_t>::lowest().mantissa() == -0x80);
	REQUIRE(std::numeric_limits<float8_t>::lowest().exponent() == 0x7f);
}
