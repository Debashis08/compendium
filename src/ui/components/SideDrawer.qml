import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App.Ui 1.0
import App.Backend 1.0

Drawer {
    id: root

    edge: Qt.LeftEdge
    modal: false
    dim: false
    closePolicy: Popup.NoAutoClose
    // property var backendController: ServiceProvider.appController

    Rectangle {
        anchors.fill: parent
        color: "#f2f2f2"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 5

            MenuButton {
                text: WorkspaceViewModel.workspaceName
                bgRadius: 4
                // icon.source: "qrc:/assets/icons/folder.png"
                onClicked: {
                    console.log("Navigating to workspace.")
                    // root.close()
                }
            }

            MenuButton {
                text: "Files"
                bgRadius: 4
                icon.source: "../assets/icons/folder.png"
                onClicked: {
                    console.log("Navigating to Files.")
                    // root.close()
                }
            }

            MenuButton {
                text: "Settings"
                bgRadius: 4
                icon.source: "../assets/icons/settings.png"
                onClicked: {
                    console.log("Navigating to Settings.")
                    // root.close()
                }
            }

            MenuButton {
                text: "Trash"
                bgRadius: 4
                icon.source: "../assets/icons/trash.png"
                onClicked: {
                    console.log("Navigating to Trash.")
                    // sideDrawer.close()
                }
            }

            Item { Layout.fillHeight: true }
        }
    }
}