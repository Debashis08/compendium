import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: rootButton

    // 1. Fill the width so the hover effect covers the whole menu row
    Layout.fillWidth: true

    // 2. Default icon sizes (in case you don't specify them in the main file)
    icon.width: 13
    icon.height: 13

    // 3. Text styling (Set to black since your Drawer is white)
    font.pixelSize: 10
    palette.buttonText: "black"

    // 4. THE FIX: Custom Left-Aligned Content
    contentItem: Item {
        implicitHeight: rootButton.icon.height // Gives the button a comfortable clickable height

        Row {
            anchors.left: parent.left
            anchors.leftMargin: 2 // Pushes the icon slightly off the left wall
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8 // Space between the icon and the text

            // The exact PNG/SVG you pass in from the main file
            Image {
                source: rootButton.icon.source
                width: rootButton.icon.width
                height: rootButton.icon.height
                sourceSize: Qt.size(width, height)
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
            }

            // The button text
            Text {
                text: rootButton.text
                font: rootButton.font
                color: rootButton.palette.buttonText
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    // 5. Updated Background (Dark tints for white backgrounds)
    background: Rectangle {
        radius: 0 // Soft rounded corners for a modern look
        color: {
            if (rootButton.hovered) {
                return "#f2f2f2" // Very faint gray when hovered
            } else {
                return "transparent"
            }
        }
    }
}