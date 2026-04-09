import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Drawer {
    id: root

    edge: Qt.LeftEdge
    modal: false
    dim: false
    closePolicy: Popup.NoAutoClose

    Rectangle {
        anchors.fill: parent
        color: "#f2f2f2"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 5

            MenuButton {
                text: "Files"
                icon.source: "qrc:/ui/icons/folder.png"
                onClicked: {
                    console.log("Navigating to Files.")
                    root.close()
                }
            }

            MenuButton {
                text: "Settings"
                icon.source: "qrc:/ui/icons/settings.png"
                onClicked: {
                    console.log("Navigating to Settings.")
                    root.close()
                }
            }

            MenuButton {
                text: "Trash"
                icon.source: "qrc:/ui/icons/trash.png"
                onClicked: {
                    console.log("Navigating to Trash.")
                    sideDrawer.close()
                }
            }

            Item { Layout.fillHeight: true }
        }
    }
}