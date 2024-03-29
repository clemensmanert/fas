cmake_minimum_required(VERSION 3.1...3.12)

include(FetchContent)

FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.10
	)

FetchContent_GetProperties(catch)
if(NOT catch_POPULATED)
  FetchContent_Populate(catch)
  add_subdirectory(${catch_SOURCE_DIR} ${catch_BINARY_DIR})
endif()

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
	"${CMAKE_CURRENT_LIST_DIR}/division.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/increment.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/decrement.cpp"
	)

set(TESTS_CMD tests)

add_executable("${TESTS_CMD}" "${TEST_SOURCES}")
target_link_libraries(tests PRIVATE Catch2::Catch2)
add_test(NAME "${TESTS_CMD}" COMMAND "${TESTS_CMD}")
set_property(TARGET "${TESTS_CMD}" PROPERTY CXX_STANDARD 17)
