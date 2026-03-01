qt_add_executable(compendium
    main.cpp
)

# This embeds the file at the root path ":/" which is where Qt looks for it.
qt_add_resources(compendium "configuration"
    PREFIX "/"
    FILES "compendium-qtquickcontrols2.conf"
)

# This below config setting is to avoid openning a command prompt window while running the app in windows machine.
set_target_properties(compendium PROPERTIES WIN32_EXECUTABLE ON)

add_subdirectory(backend)
add_subdirectory(ui)

target_link_libraries(compendium
    PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::StateMachine
    BackendLib
    # critical
    BackendLibplugin
    UiLib
    #critical
    UiLibplugin
)
