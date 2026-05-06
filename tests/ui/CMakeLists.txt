# Find necessary Qt Quick Test modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickTest)

qt_add_executable(unit_tests_ui
    TestSetup.cpp
)

# 1. Find every .qml file in the current UI test directory
file(GLOB QML_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.qml")

# 2. Loop through them and register each one as a separate CTest
foreach(QML_FILE IN LISTS QML_TEST_FILES)
    # Extract just the file name (e.g., gets "tst_WelcomeScreen" from "tst_WelcomeScreen.qml")
    get_filename_component(TEST_NAME ${QML_FILE} NAME_WE)

    # Register this specific QML file as its own test
    # By passing the file path, the Qt Test runner will ONLY execute this file
    add_test(
        NAME "UiTest.${TEST_NAME}"
        COMMAND unit_tests_ui ${QML_FILE}
    )
endforeach()

target_link_libraries(unit_tests_ui PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickTest

    # Your Core and Backend
    CoreLib
    BackendLib
    BackendLibplugin
    UiLibplugin
)

# Use \" to safely pass quotes through the Windows command line to C++
target_compile_definitions(unit_tests_ui PRIVATE
    "QUICK_TEST_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\""
    "APP_BUILD_DIR=\"${CMAKE_BINARY_DIR}\""
)