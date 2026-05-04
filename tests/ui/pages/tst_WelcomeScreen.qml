import QtQuick
import QtTest

import App.Ui

TestCase {
    name: "WelcomeScreenTests"

    Component {
        id: welcomeScreenComponent

        // 2. Because we imported App.Ui, the engine knows exactly what this is!
        WelcomeScreen {
            width: 800
            height: 600
        }
    }

    property var screen: null

    function init() {
        screen = welcomeScreenComponent.createObject(null)
        verify(screen !== null, "WelcomeScreen should instantiate without errors")
    }

    function cleanup() {
        if (screen) {
            screen.destroy()
            screen = null
        }
    }

    function test_rendersCorrectly() {
        verify(screen.visible, "Welcome screen should be visible")
        compare(screen.width, 800, "Width should match initialization")
        compare(screen.height, 600, "Height should match initialization")
    }
}