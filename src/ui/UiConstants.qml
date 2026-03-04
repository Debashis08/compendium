pragma Singleton
import QtQuick

QtObject {
    // Main.qml constants
    readonly property int defaultMainAppWindowHeight: 720
    readonly property int defaultMainAppWindowWidth: 1080
    readonly property int minimumMainAppWindowHeight: 480
    readonly property int minimumMainAppWindowWidth: 640
    readonly property string appName: "compendium"

    // Layout constants
    readonly property int marginSmall: 8
    readonly property int marginMedium: 16
    readonly property int marginLarge: 24

    // Font constants
    readonly property int fontSizeHeading: 24
    readonly property int fontSizeBody: 14

    // Animation speeds
    readonly property int animFast: 150
    readonly property int animNormal: 300
}
