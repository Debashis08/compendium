# tests/unit/CMakeLists.txt

find_package(Qt6 REQUIRED COMPONENTS Test)

# Automatically Download and Build Google Test and Google Mock.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent GTest from overriding MSVC runtime library settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(UnitTests
    main.cpp
    # app layer
    app/tst_ServiceInitializer.cpp
    
    # core layer
    core/tst_ServiceProvider.cpp
    
    # backend layer
    backend/bridges/tst_AppController.cpp
    backend/bridges/tst_WorkspaceViewModel.cpp

    backend/services/tst_WorkspaceService.cpp

    ${CMAKE_SOURCE_DIR}/src/app/ServiceInitializer.cpp
)

# Allow tests to see the src headers and our mocks folder
target_include_directories(UnitTests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
)

# Link against our app libraries and test frameworks
target_link_libraries(UnitTests PRIVATE
    Qt6::Test
    gtest
    gmock
    CoreLib
    BackendLib
)

# Automatically discover and register Google Tests
include(GoogleTest)
# DISCOVERY_MODE PRE_TEST prevents CMake from running the exe during the build phase
gtest_discover_tests(UnitTests DISCOVERY_MODE PRE_TEST)