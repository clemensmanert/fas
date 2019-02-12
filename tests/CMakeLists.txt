cmake_minimum_required(VERSION 3.1...3.12)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)

FetchContent_MakeAvailable(Catch2)

set(TEST_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/main_test.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/constants.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/traits.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/numeric_limits.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/constructors.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/constructor_double_conversion.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/equality.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/comparison.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/conversion.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/unary_plus.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/unary_minus.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/addition.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/substraction.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/multiplication.cpp"
	)

set(TESTS_CMD tests)

add_executable("${TESTS_CMD}" "${TEST_SOURCES}")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
add_test(NAME "${TESTS_CMD}" COMMAND "${TESTS_CMD}")
set_property(TARGET "${TESTS_CMD}" PROPERTY CXX_STANDARD 17)
