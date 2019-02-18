#include "test_utils.hpp"

TEST_CASE("Expect to fullfill the same traits as double.") {
	REQUIRE(std::is_fundamental<float8_t>::value == true);
	REQUIRE(std::is_arithmetic<float8_t>::value == true);
	REQUIRE(std::is_floating_point<float8_t>::value == true);
	REQUIRE(std::is_scalar<float8_t>::value == true);
	REQUIRE(std::is_object<float8_t>::value == true);

	REQUIRE(std::is_integral<float8_t>::value == false);
	REQUIRE(std::is_compound<float8_t>::value == false);
}
