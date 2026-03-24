# compendium\tests\ui\CMakeLists.txt

cmake_minimum_required(VERSION 3.16)
project(UiTests LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Quick QuickTest Test)

# Define the executable and list all QML files.
# Adding the QML files here is what forces Qt Creator to parse them so they appear in the Test Explorer UI.
qt_add_executable(tst_ui
    TestSetup.cpp
    utils/UiTestHelper.qml
    pages/tst_WelcomeScreen.qml

    # Adding the src/resources, so in unit tests the icons appear correctly.
    ${CMAKE_SOURCE_DIR}/src/resources.qrc
)

# Link Dependencies
target_link_libraries(tst_ui
    PRIVATE

    # Requied Qt packages.
    Qt6::Quick
    Qt6::QuickTest
    Qt6::Test

    #C++ Backend Library.
    BackendLib
    BackendLibplugin

    # QML Ui Library.
    UiLib
    UiLibplugin
)

# Include Directories.
target_include_directories(tst_ui PRIVATE
    ${CMAKE_SOURCE_DIR}/src/backend
    ${CMAKE_SOURCE_DIR}/src/backend/interfaces
    ${CMAKE_SOURCE_DIR}/src/backend/core
)

# Define Source directory for QML engine.
target_compile_definitions(tst_ui PRIVATE
    QUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

# Register the test using standard CMake.
# The COMMAND matches the executable target name defined above (tst_ui).
add_test(NAME tst_ui COMMAND tst_ui)

# Optional: If on Windows, it might be needed to ensure the test finds DLLs.
# This helper (available in Qt 6.3+) sets the environment.
# If this fails, just stick to the plain add_test.
if(COMMAND qt_add_test_helper)
    qt_add_test_helper(tst_ui)
endif()