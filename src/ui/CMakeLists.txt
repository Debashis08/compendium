# src/ui/CMakeLists.txt

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