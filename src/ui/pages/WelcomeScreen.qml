import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import App.Backend 1.0

Item {
    id: root
    // 1. Ensure the root item explicitly fills its container (the Loader)
    anchors.fill: parent

    Column {
        anchors.centerIn: parent
        // 2. Dynamic Spacing: 4% of the window height, but never smaller than 20px
        spacing: Math.max(10, root.height * 0.04)

        // 3. Restrict the Column width to 80% of the screen so text doesn't
        // stretch all the way to the absolute edges on small windows.
        width: root.width * 0.8

        Text {
            text: "Welcome to Compendium"
            // 4. Dynamic Font: 4% of window width, clamped between 24px and 48px
            font.pixelSize: Math.max(20, Math.min(40, root.width * 0.04))
            font.bold: true
            color: "black"
            horizontalAlignment: Text.AlignHCenter

            // 5. Enable Word Wrapping! If the user makes the window very thin,
            // the text will stack nicely instead of getting cut off.
            width: parent.width
            wrapMode: Text.WordWrap
        }

        Text {
            text: "To get started, please select a folder to use as your workspace"
            // Dynamic Font: 2% of window width, clamped between 14px and 24px
            font.pixelSize: Math.max(12, Math.min(20, root.width * 0.02))
            color: "gray"
            horizontalAlignment: Text.AlignHCenter

            width: parent.width
            wrapMode: Text.WordWrap
        }

        Button {
            id: chooseWorkspaceButton
            // text: "Choose Workspace"
            anchors.horizontalCenter: parent.horizontalCenter

            background: Rectangle {
                        // Set the desired corner radius
                        radius: 10
                        // Set colors and borders as needed
                        color: "white"
                        border.color: "black"
                        border.width: 1

                        Text {
                            id: buttonText
                            text: qsTr("Choose Workspace")
                            color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: Math.max(10, Math.min(15, root.width * 0.02))
                        }
                    }

            // 6. Dynamic Button Size: 25% of window width, clamped between 200px and 400px
            width: Math.max(100, Math.min(200, root.width * 0.25))
            // Height is 6% of window height, but at least 40px
            height: Math.max(30, root.height * 0.06)

            onClicked: workspaceDialog.open()
        }
    }

    // --- DIALOG ---
    FolderDialog {
        id: workspaceDialog
        title: "Select Compendium Workspace"

        onAccepted: {
            ServiceProvider.appController.setWorkspacePath(workspaceDialog.selectedFolder)
        }
    }
}
