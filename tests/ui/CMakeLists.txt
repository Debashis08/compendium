# tests/ui/CMakeLists.txt

# Find necessary Qt Quick Test modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickTest)

qt_add_executable(unit_tests_ui
    TestSetup.cpp
)

# Register the QML module so the Singleton and tests are recognized
qt_add_qml_module(unit_tests_ui
    URI App.Ui.Tests
    VERSION 1.0
    QML_FILES
        # Register utility singleton
        utils/UiTestHelper.qml

        # Register unit test files
        components/tst_AppToolbar.qml
        components/tst_MenuButton.qml
    )

# Explicitly register the executable with CTest
add_test(NAME unit_tests_ui COMMAND unit_tests_ui)

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