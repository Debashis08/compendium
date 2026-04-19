# src/ui/CMakeLists.txt

# Tell CMake that UiConstants is a globally accessible Singleton
set_source_files_properties(UiConstants.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(UiLib
    STATIC
    URI "App.Ui"
    VERSION 1.0
    QML_FILES
        Main.qml
        UiConstants.qml
        components/AppToolbar.qml
        components/MenuButton.qml
        components/SideDrawer.qml
        pages/CustomTitleBar.qml
        pages/MainDashBoard.qml
        pages/WelcomeScreen.qml
        pages/WindowResizeBorders.qml
)

# Link the backend plugin so the UI can resolve the QML_ELEMENT types
target_link_libraries(UiLib
    PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    BackendLibplugin
)