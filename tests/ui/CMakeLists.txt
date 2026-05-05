# Find necessary Qt Quick Test modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickTest)

qt_add_executable(uiUnitTests
    TestSetup.cpp
)

# Explicitly register the executable with CTest
add_test(NAME uiUnitTests COMMAND uiUnitTests)

target_link_libraries(uiUnitTests PRIVATE
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
target_compile_definitions(uiUnitTests PRIVATE
    "QUICK_TEST_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\""
    "APP_BUILD_DIR=\"${CMAKE_BINARY_DIR}\""
)