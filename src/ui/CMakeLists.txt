set_source_files_properties(UiConstants.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(UiLib
    # Explicitly state it is a STATIC lib here
    STATIC
    URI "App.Ui"
    VERSION 1.0
    # Standardizes the resource path
    RESOURCE_PREFIX "/qt/qml"

    # Declare the qml files.
    QML_FILES
        Main.qml
        UiConstants.qml
        pages/CounterPage.qml
        components/StandardButton.qml
        components/WelcomeScreen.qml
        components/MainDashBoard.qml
)

target_link_libraries(UiLib PRIVATE Qt6::Quick)
