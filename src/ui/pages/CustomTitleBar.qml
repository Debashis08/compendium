import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

Rectangle {
    id: root
    height: 40
    color: "#2C2C2C"

    property bool showMenuButton: false
    signal menuClicked()

    // --- THE FIX: NATIVE SYSTEM DRAG ---
    MouseArea {
        anchors.fill: parent
        // Start dragging the window when the user presses down
        onPressed: Window.window.startSystemMove()

        // Bonus: Double-click to maximize/restore
        onDoubleClicked: {
            if (Window.window.visibility === Window.Maximized) {
                Window.window.showNormal()
            } else {
                Window.window.showMaximized()
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 10

        // We set z: 1 so the buttons sit on top of the MouseArea
        // and can still be clicked without triggering a window drag.
        z: 1

        Button {
            text: "☰"
            font.pixelSize: 18
            visible: root.showMenuButton
            background: Item {}
            contentItem: Text {
                text: parent.text
                color: "white"
                font.pixelSize: parent.font.pixelSize
                verticalAlignment: Text.AlignVCenter
            }
            onClicked: root.menuClicked()
        }

        Text {
            text: "Compendium"
            color: "white"
            font.pixelSize: 14
            font.bold: true
        }

        Item { Layout.fillWidth: true }

        Row {
            spacing: 0

            Button {
                text: "—"
                width: 40; height: root.height
                background: Item {}
                contentItem: Text { text: parent.text; color: "white"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                onClicked: Window.window.showMinimized()
            }

            Button {
                text: Window.window.visibility === Window.Maximized ? "❐" : "☐"
                width: 40; height: root.height
                background: Item {}
                contentItem: Text { text: parent.text; color: "white"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                onClicked: {
                    if (Window.window.visibility === Window.Maximized) {
                        Window.window.showNormal()
                    } else {
                        Window.window.showMaximized()
                    }
                }
            }

            Button {
                text: "✕"
                width: 40; height: root.height
                background: Rectangle { color: parent.hovered ? "#E81123" : "transparent" }
                contentItem: Text { text: parent.text; color: "white"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                onClicked: Window.window.close()
            }
        }
    }
}
