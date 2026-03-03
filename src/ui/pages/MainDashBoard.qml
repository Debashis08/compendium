import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App.Backend 1.0

Item {
    id: root

    // --- USE OUR NEW TITLE BAR ---
        CustomTitleBar {
            id: titleBar
            width: parent.width
            anchors.top: parent.top

            // Turn on the menu button for the dashboard!
            showMenuButton: true

            // Connect the click signal to open the Drawer
            onMenuClicked: sideDrawer.open()
        }

        // --- MAIN CONTENT AREA ---
        Item {
            id: contentArea
            anchors.top: titleBar.bottom // Anchor below the custom title bar
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            Text {
                anchors.centerIn: parent
                text: "Main Dashboard\n" + ServiceProvider.appController.workspacePath
                font.pixelSize: 20
                color: "black" // Or white if you are using a dark background
                horizontalAlignment: Text.AlignHCenter
            }
        }


    // --- 3. THE SIDE DRAWER (MENU) ---
    Drawer {
        id: sideDrawer
        width: parent.width * 0.2
        height: parent.height

        // This ensures the drawer slides out from the left edge
        // over the content (like Notion or a mobile app)
        edge: Qt.LeftEdge

        // Drawer background
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
                        // You can implement logic later to reset the workspace in C++
                        // and transition the state machine back to "Welcome"
                    }
                }

                // This spacer pushes the buttons to the top of the Drawer
                Item { Layout.fillHeight: true }
            }
        }
    }
}
