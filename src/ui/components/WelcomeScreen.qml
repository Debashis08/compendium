import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs // Required for FolderDialog in Qt 6

// Make sure your backend import is here so we can access ServiceProvider
import App.Backend 1.0

Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 30

        Text {
            text: "Welcome to Compendium"
            font.pixelSize: 32
            font.bold: true
            color: "white"
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            text: "To get started, please select a folder\nto use as your workspace."
            font.pixelSize: 16
            color: "lightgray"
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            text: "Choose Workspace Folder"
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 40

            // 1. Open the dialog when clicked
            onClicked: workspaceDialog.open()
        }
    }

    // 2. The Native Folder Picker Dialog
    FolderDialog {
        id: workspaceDialog
        title: "Select Compendium Workspace"

        // 3. When the user clicks "Select Folder" in the OS window
        onAccepted: {
            // workspaceDialog.selectedFolder returns a file:/// URL
            // Pass it to your C++ controller.
            ServiceProvider.appController.setWorkspacePath(workspaceDialog.selectedFolder)

            // Note: Because your setWorkspacePath() cleans the URL, saves it,
            // and emits workspaceConfigured(), the State Machine will automatically
            // transition to "MainWorkspace" the moment this happens!
        }
    }
}
