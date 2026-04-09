import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    // Defined a signal that the parent page can listen to
    signal menuClicked()

    color: "#f2f2f2"

    RowLayout {
        anchors.fill: parent

        Button {
            id: menuButton
            icon.source: "qrc:/ui/icons/menu.png"

            // Base sizes on the component's height/width
            icon.width: root.width * 0.03
            icon.height: root.height * 0.5
            icon.color: "transparent"

            background: Rectangle {
                color: "transparent"
            }

            // Emit the signal
            onClicked: root.menuClicked()
        }

        Item { Layout.fillWidth: true }
    }
}