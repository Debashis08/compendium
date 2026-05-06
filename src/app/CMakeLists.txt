# src/app/CMakeLists.txt

# Create the App Library (Everything except main.cpp)
add_library(AppLib STATIC
    ServiceInitializer.h
    ServiceInitializer.cpp
    
)

# Allow AppLib to see other headers in your project
target_include_directories(AppLib PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Link all necessary underlying libraries to AppLib
target_link_libraries(AppLib PUBLIC
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::StateMachine
    CoreLib
    BackendLib
    BackendLibplugin
    UiLib
    UiLibplugin
)

# Create the executable (only main.cpp)
qt_add_executable(compendium
    main.cpp
)

# Embed the Qt Quick Controls configuration file
qt_add_resources(compendium "configuration"
    PREFIX "/"
    FILES "../ui/compendium-qtquickcontrols2.conf"
)

# Avoid opening a command prompt window on Windows
set_target_properties(compendium PROPERTIES WIN32_EXECUTABLE ON)

# Link our new AppLib to the executable so it can run
target_link_libraries(compendium PRIVATE
    AppLib
)