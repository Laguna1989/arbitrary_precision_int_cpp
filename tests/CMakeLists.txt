
message(STATUS "api: enable unit tests: ${API_ENABLE_UNIT_TESTS}")
if (API_ENABLE_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif ()

if (API_ENABLE_PERFORMANCE_TESTS)
    add_subdirectory(performance_tests)
endif ()
