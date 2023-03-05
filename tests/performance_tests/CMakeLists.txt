include(FetchContent)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG v1.6.0
        )
FetchContent_MakeAvailable(googlebenchmark)

file(GLOB_RECURSE PERFORMANCEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(api_performance_test ${PERFORMANCEFILES})

target_link_libraries(api_performance_test benchmark::benchmark)
target_link_libraries(api_performance_test ArbitraryPrecisionInteger)
