# cmake/TestUtils.cmake

function(add_compendium_unit_test TARGET_NAME)
    # The ARGN variable captures all arguments passed after TARGET_NAME (i.e., your source files)
    set(SOURCES ${ARGN})

    # 1. Create the executable
    add_executable(${TARGET_NAME} ${SOURCES})

    # 2. Allow tests to see the src headers and our central mocks folder
    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/tests/mocks
    )

    # 3. Link all common dependencies every test needs
    target_link_libraries(${TARGET_NAME} PRIVATE
        # Google Test Core
        GTest::gtest GTest::gmock

        # Our custom main() containing the Qt initialization
        SharedTestMain

        # Qt Dependencies
        Qt6::Core
        Qt6::Test

        # Your internal application libraries
        AppLib
        CoreLib
        BackendLib

    )

    # 4. Automatically register the test with CTest (Google Test auto-discovery)
    include(GoogleTest)
    # DISCOVERY_MODE PRE_TEST prevents CMake from running the exe during the build phase
    gtest_discover_tests(${TARGET_NAME} DISCOVERY_MODE PRE_TEST)
endfunction()