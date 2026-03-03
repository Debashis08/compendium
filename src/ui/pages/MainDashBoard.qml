import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App.Backend 1.0

Item {
    id: root

    // --- 1. INTERNAL APP TOOLBAR ---
    // Since Windows owns the very top title bar now, we add a small
    // internal toolbar right below it to hold your hamburger menu.
    Rectangle {
        id: appToolbar
        width: parent.width
        height: 50
        color: "#F3F3F3" // We can bind this to your ThemeService later!

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 10

            Button {
                text: "☰"
                font.pixelSize: 20
                onClicked: sideDrawer.open()
            }

            Item { Layout.fillWidth: true } // Pushes the button to the left
        }
    }

    // --- 2. MAIN CONTENT AREA ---
    Item {
        id: contentArea
        anchors.top: appToolbar.bottom // Anchor below our internal toolbar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Text {
            anchors.centerIn: parent
            text: "Main Dashboard\n" + (ServiceProvider.appController ? ServiceProvider.appController.workspacePath : "")
            font.pixelSize: 20
            color: "black"
            horizontalAlignment: Text.AlignHCenter
        }
    }

    // --- 3. THE SIDE DRAWER (MENU) ---
    Drawer {
        id: sideDrawer
        width: Math.max(250, parent.width * 0.2) // Ensures it doesn't get too thin
        height: parent.height

        edge: Qt.LeftEdge

        Rectangle {
            anchors.fill: parent
            color: "#1E1E1E"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 15
                spacing: 15

                Text {
                    text: "Workspace Menu"
                    color: "gray"
                    font.bold: true
                }

                // Menu Items
                Button {
                    text: "📁 Files"
                    Layout.fillWidth: true
                    onClicked: {
                        console.log("Navigating to Files...")
                        sideDrawer.close()
                    }
                }

                Button {
                    text: "⚙️ Settings"
                    Layout.fillWidth: true
                    onClicked: {
                        console.log("Navigating to Settings...")
                        sideDrawer.close()
                    }
                }

                Button {
                    text: "🔄 Change Workspace"
                    Layout.fillWidth: true
                    onClicked: {
                        console.log("Resetting workspace...")
                        sideDrawer.close()
                    }
                }

                Item { Layout.fillHeight: true } // Spacer
            }
        }
    }
}
