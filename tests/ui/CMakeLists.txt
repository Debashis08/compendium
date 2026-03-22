cmake_minimum_required(VERSION 3.16)

project(UiTests LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickTest Test)

# 1. Define the executable AND list your QML files
# Adding the QML files here is what forces Qt Creator to parse them
# so they appear in the Test Explorer UI.
qt_add_executable(tst_ui
    TestSetup.cpp
    utils/UiTestHelper.qml
    pages/tst_WelcomeScreen.qml

    ${CMAKE_SOURCE_DIR}/src/resources.qrc
)

# 2. Link Dependencies
target_link_libraries(tst_ui
    PRIVATE
    Qt6::Quick
    Qt6::QuickTest
    Qt6::Test
    BackendLib # Your C++ Backend Library
    BackendLibplugin
    UiLib      # Your QML UI Library
    UiLibplugin
)

# 3. Include Directories
target_include_directories(tst_ui PRIVATE
    ${CMAKE_SOURCE_DIR}/src/backend
    ${CMAKE_SOURCE_DIR}/src/backend/interfaces
    ${CMAKE_SOURCE_DIR}/src/backend/core
)

# 4. Define Source Dir for QML engine
# We append "/pages" here so the QUICK_TEST_MAIN macro specifically
# scans the folder where your actual tst_ files are located.
target_compile_definitions(tst_ui PRIVATE
    QUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

# --- FIX START ---

# 5. Register the test using standard CMake
# The COMMAND matches the executable target name defined above (tst_ui)
add_test(NAME tst_ui COMMAND tst_ui)

# Optional: If on Windows, you might need to ensure the test finds DLLs.
# This helper (available in Qt 6.3+) sets the environment.
# If this fails, just stick to the plain add_test line above.
if(COMMAND qt_add_test_helper)
    qt_add_test_helper(tst_ui)
endif()