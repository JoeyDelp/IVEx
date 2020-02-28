# CMake Catch2 Unit test executable
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# Unit test dependencies
find_package(Catch2 REQUIRED NO_MODULE)

# Unit test executable
add_executable(ivex_unit)

 # Unit test executable sources
target_sources(ivex_unit PRIVATE
  catch_main.cpp
  Input.cpp
)

# Unit test subfolders

# Link unit test dependencies
target_link_libraries(ivex_unit PRIVATE
  ivex
  Catch2::Catch2
)

# Add all test cases as individual tests
include(Catch)
catch_discover_tests(
  ivex_unit
  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
  TEST_PREFIX ivex::unit::
)
