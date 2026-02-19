import QtQuick
import QtQuick.Window
// Import the folder to access CounterPage
import "pages"

Window
{
    width: 1080
    height: 720
    visible: true
    title: qsTr("compendium")

    WelcomePage
    {
        anchors.fill: parent
    }
}
