if (API_ENABLE_UNIT_TESTS)
    # Download and unpack googletest at configure time
    configure_file(${CMAKE_SOURCE_DIR}/ext/googletest/CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/ext/googletest/googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ext/googletest/googletest-download)
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ext/googletest/googletest-download)
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/ext/googletest/googletest-src
            ${CMAKE_CURRENT_BINARY_DIR}/ext/googletest/googletest-build
            EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include")
    endif ()


    file(GLOB_RECURSE UNITTESTFILES ${CMAKE_CURRENT_SOURCE_DIR}/*)

    add_executable(arbitrary_precision_int_unit_tests ${UNITTESTFILES})
    target_link_libraries(arbitrary_precision_int_unit_tests gtest_main)
    target_link_libraries(arbitrary_precision_int_unit_tests ArbitraryPrecisionInteger)
endif ()
