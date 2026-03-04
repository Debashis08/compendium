import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import App.Ui 1.0
import App.Backend 1.0

Item
{
    id: welcomePage

    ColumnLayout
    {
        anchors.centerIn: parent
        spacing: 20

        Text
        {
            objectName: "welcomeMessage"
            text: "Welcome to compendium"
            font.pixelSize: 32
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
