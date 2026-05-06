# tests/CMakeLists.txt

# Create a project for tests.
project(compendiumTests LANGUAGES CXX)

enable_testing()

# Find the Test module (Required for QTest in UI tests and our custom main)
find_package(Qt6 REQUIRED COMPONENTS Core Quick Test QuickTest)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Fix for MSVC: Ensures GTest uses the same runtime library as Qt
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Load your custom testing macro BEFORE adding subdirectories
include(${CMAKE_SOURCE_DIR}/cmake/TestUtils.cmake)

# IMPORTANT: Add the shared folder first so the custom main library is built
add_subdirectory(shared)

# Add all the test folders
add_subdirectory(app)
add_subdirectory(backend)
add_subdirectory(core)
add_subdirectory(mocks)
add_subdirectory(ui)