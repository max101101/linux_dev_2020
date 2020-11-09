cmake_minimum_required(VERSION 3.13)

project(08_TestingCoverage C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0  -fprofile-arcs -ftest-coverage")

add_library(testing_coverage STATIC src/buf.c)

add_executable(tests tests.c)
target_link_libraries(tests testing_coverage)

include(CTest)

add_test(test_initialization tests 0)
add_test(test_push_clear_free tests 1)
add_test(test_clear_empty tests 2)
add_test(test_push tests 3)
add_test(test_grow_trucn tests 4)
add_test(test_pop tests 5)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS tests)
add_custom_target(coverage COMMAND make ExperimentalCoverage DEPENDS check)
