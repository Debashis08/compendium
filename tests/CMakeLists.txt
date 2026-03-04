# tests/CMakeLists.txt

# Create a project for tests
project(compendiumTests LANGUAGES CXX)

enable_testing()
# Find the Test module (Required for QTest)
find_package(Qt6 REQUIRED COMPONENTS Quick Test QuickTest)

add_subdirectory(backend)
add_subdirectory(ui)
