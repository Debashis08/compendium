# Find necessary Qt Quick Test modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickTest)

add_executable(UiTests
    TestSetup.cpp
)

target_link_libraries(UiTests PRIVATE
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
target_compile_definitions(UiTests PRIVATE
    "QUICK_TEST_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\""
    "APP_BUILD_DIR=\"${CMAKE_BINARY_DIR}\""
)