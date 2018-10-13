cmake_minimum_required(VERSION 3.1...3.12)

project(floating_point VERSION 0.1
  DESCRIPTION "A generic floating point arithmetic implemented in software."
  LANGUAGES CXX)

include_directories("${PROJECT_SOURCE_DIR}")

enable_testing()
include(CTest)


add_subdirectory(tests)
