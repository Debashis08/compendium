import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import App.Ui 1.0
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
            text: "Please create a workspace in local or Google drive"
            // Dynamic Font: 2% of window width, clamped between 14px and 24px
            font.pixelSize: Math.max(8, Math.min(16, root.width * 0.02))
            color: "gray"
            horizontalAlignment: Text.AlignHCenter

            width: parent.width
            wrapMode: Text.WordWrap
        }

        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            // 2. Dynamic Spacing: 4% of the window height, but never smaller than 20px
            spacing: Math.max(10, root.height * 0.04)


            Button {
                id: chooseLocalWorkspaceButton
                objectName: "localWorkspaceButton"
                hoverEnabled: true
                // text: "Choose Workspace"
                // anchors.horizontalCenter: parent.horizontalCenter


                background: Rectangle {
                    radius: 10
                    color: chooseLocalWorkspaceButton.hovered ? "#f0f0f0" : "white"
                    border.color: "#707070"
                    border.width: 1

                    Behavior on color{
                        ColorAnimation {
                            duration: 300
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                // Use contentItem to layout the inside of the button
                contentItem: Row {
                    spacing: 10 // Adjust the space between the icon and the text
                    padding: 10

                    // This keeps both the icon and text perfectly centered in the button
                    anchors.centerIn: parent

                    Image {
                        id: localSystemIcon
                        // Replace this with the actual path to your icon
                        // e.g., "qrc:/images/google_logo.png" or "file:///path/to/icon.png"
                        source: "qrc:/ui/icons/local-system.png"

                        width: parent.width * 0.14  // Set desired icon width
                        height: parent.width * 0.14  // Set desired icon height
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: crateLocalWorkspace
                        text: qsTr("Create local workspace")
                        color: "#707070"
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: Math.max(10, Math.min(12, root.width * 0.02))
                    }
                }

                // 6. Dynamic Button Size: 25% of window width, clamped between 200px and 400px
                width: Math.max(100, Math.min(200, root.width * 0.25))
                // Height is 6% of window height, but at least 40px
                height: Math.max(30, root.height * 0.06)

                onClicked: workspaceDialog.open()
            }

            Button {
                id: chooseGoogleWorkspaceButton
                objectName: "googleWorkspaceButton"
                hoverEnabled: true

                background: Rectangle {
                    radius: 10
                    color: chooseGoogleWorkspaceButton.hovered ? "#f0f0f0" : "white"
                    border.color: "#707070"
                    border.width: 1

                    Behavior on color{
                        ColorAnimation {
                            duration: 300
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                // Use contentItem to layout the inside of the button
                contentItem: Row {
                    spacing: 10 // Adjust the space between the icon and the text
                    padding: 10

                    // This keeps both the icon and text perfectly centered in the button
                    anchors.centerIn: parent

                    Image {
                        id: googleIcon
                        // Replace this with the actual path to your icon
                        // e.g., "qrc:/images/google_logo.png" or "file:///path/to/icon.png"
                        source: "qrc:/ui/icons/google.png"

                        width: parent.width * 0.14  // Set desired icon width
                        height: parent.width * 0.14  // Set desired icon height
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: loginWithGoogleButtonText
                        text: qsTr("Log in With Google")
                        color: "#707070"
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: Math.max(10, Math.min(12, root.width * 0.02))
                    }
                }

                // Dynamic Button Size
                width: Math.max(100, Math.min(200, root.width * 0.25))
                height: Math.max(30, root.height * 0.06)

                // onClicked: workspaceDialog.open()
            }
        }
    }

    // --- DIALOG ---
    FolderDialog {
        id: workspaceDialog
        objectName: "folderDialog"
        title: "Select local workspace"

        onAccepted: {
            ServiceProvider.appController.setWorkspacePath(workspaceDialog.selectedFolder)
        }
    }
}
