cmake_minimum_required(VERSION 3.10)
project("ArbitraryPrecisionInteger")

option(API_ENABLE_UNIT_TESTS "Enable unit tests" ON)
option(API_ENABLE_PERFORMANCE_TESTS "Enable performance tests" ON)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD 17)

add_subdirectory(src)

add_subdirectory(tests)

