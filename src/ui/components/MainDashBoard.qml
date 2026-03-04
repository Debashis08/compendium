import QtQuick
import QtQuick.Controls
import App.Backend 1.0 // Or whatever your URI is

Item {
    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Dashboard"
            font.pixelSize: 32
            color: "white"
        }

        Text {
            // This reads the property directly from your C++ controller!
            text: "Current Workspace: " + ServiceProvider.appController.workspacePath
            // color: "lightgreen"
            font.pixelSize: 16
        }
    }
}
