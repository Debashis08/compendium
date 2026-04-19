# src/app/CMakeLists.txt

qt_add_executable(compendium
    main.cpp
    ServiceInitializer.h
    ServiceInitializer.cpp
    
    # We still include the legacy QRC file here if you aren't fully 
    # relying on qt_add_qml_module's native asset management yet.
    ../ui/resources.qrc
)

# Embed the Qt Quick Controls configuration file
qt_add_resources(compendium "configuration"
    PREFIX "/"
    FILES "../ui/compendium-qtquickcontrols2.conf"
)

# Avoid opening a command prompt window on Windows
set_target_properties(compendium PROPERTIES WIN32_EXECUTABLE ON)

# The executable must link all underlying libraries and their QML plugins
target_link_libraries(compendium
    PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::StateMachine
    CoreLib
    BackendLib
    BackendLibplugin
    UiLib
    UiLibplugin
)