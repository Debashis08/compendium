import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App.Backend 1.0
import "../components"

Item {
    id: root

    // Instantiate the Toolbar
    AppToolbar {
        id: topToolbar
        width: parent.width
        height: parent.height * 0.04

        // Listen to the signal and toggle the drawer
        onMenuClicked: sideDrawer.opened ? sideDrawer.close() : sideDrawer.open()
    }

    // Instantiate the Content Area
    Item {
        id: contentArea
        anchors.top: topToolbar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        // Push content based on drawer position
        anchors.leftMargin: sideDrawer.position * sideDrawer.width

        Text {
            anchors.centerIn: parent
            text: "Main Dashboard\n" + WorkspaceViewModel.workspacePath
            font.pixelSize: 20
            color: "black"
            horizontalAlignment: Text.AlignHCenter
        }
    }

    // Instantiate the Drawer
    SideDrawer {
        id: sideDrawer
        y: topToolbar.height
        width: Math.max(250, parent.width * 0.2)
        height: contentArea.height
    }
}