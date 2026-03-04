pragma Singleton
import QtQuick

QtObject {
    // Layout constants
    readonly property string appName: "compendium"
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
