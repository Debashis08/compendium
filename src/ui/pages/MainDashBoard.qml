import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App.Backend 1.0
import "../components"

Item {
    id: root

    // Top navbar for side menu and breadcrumbs.
    Rectangle {
        id: appToolbar
        width: parent.width
        height: parent.height * 0.04
        color: "#f2f2f2"

        RowLayout {
            // anchors.fill: parent
            // anchors.leftMargin: 1

            Button {
                id: menuButton
                objectName: "menuButton"

                icon.source: "qrc:/ui/icons/menu.png"
                icon.width: appToolbar.width * 0.03
                icon.height: appToolbar.height * 0.5
                icon.color: "transparent"

                // Custom transparent background
                background: Rectangle {
                    border.color: "transparent"
                    color: "transparent"
                }

                // Action to perform on click.
                onClicked: {
                    if(sideDrawer.opened)
                    {
                        sideDrawer.close()
                    }
                    else
                    {
                        sideDrawer.open()
                    }
                }
            }

            Item { Layout.fillWidth: true } // Pushes the button to the left
        }
    }

    // Main content area.
    Item {
        id: contentArea
        anchors.top: appToolbar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.leftMargin: sideDrawer.position * sideDrawer.width

        Text {
            anchors.centerIn: parent
            text: "Main Dashboard\n" + (ServiceProvider.appController ? ServiceProvider.appController.workspacePath : "")
            font.pixelSize: 20
            color: "black"
            horizontalAlignment: Text.AlignHCenter
        }
    }

    // Side menu.
    Drawer {
        id: sideDrawer
        y: appToolbar.height
        width: Math.max(250, parent.width * 0.2) // Ensures it doesn't get too thin
        height: contentArea.height
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

                // Item { Layout.fillHeight: true } // Spacer

                // Text {
                //     text: "Workspace Menu"
                //     color: "black"
                //     font.bold: false
                // }

                // --- Look how much cleaner this is! ---

                MenuButton {
                    text: "Files"
                    icon.source: "qrc:/ui/icons/folder.png"
                    onClicked: {
                        console.log("Navigating to Files.")
                        sideDrawer.close()
                    }
                }

                MenuButton {
                    text: "Settings"
                    icon.source: "qrc:/ui/icons/settings.png"
                    onClicked: {
                        console.log("Navigating to Settings.")
                        sideDrawer.close()
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

                Item { Layout.fillHeight: true } // Spacer
            }
        }
    }
}
