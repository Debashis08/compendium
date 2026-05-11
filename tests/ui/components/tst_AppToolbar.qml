import QtQuick
import QtTest
import App.Ui
import "../utils"

TestCase {
    id: rootTest
    name: "AppToolbarTests"
    width: 800
    height: 600
    visible: true
    when: windowShown

    AppToolbar {
        id: toolbar
        width: 800
        height: 60
    }

    SignalSpy {
        id: menuClickSpy
        target: toolbar
        signalName: "menuClicked"
    }

    function init() {
        menuClickSpy.clear()
    }

    function test_uiProperties() {
        verify(toolbar.visible, "Toolbar should be visible by default")
        compare(toolbar.color.toString(), "#f2f2f2", "Toolbar background color should match")
    }

    function test_menuButtonClickEmitsSignal() {
        compare(menuClickSpy.count, 0, "Signal count should be 0 initially")

        // 1. Find the child dynamically, no matter how deep the designer nests it!
        var menuBtn = UiTestHelper.findChild(toolbar, "menuButton")

        // 2. Fast failure if the object name was changed or removed
        verify(menuBtn !== null, "Critical Error: menuButton could not be found in the UI tree")

        // 3. Delegate the layout-waiting and clicking to your robust utility function
        // Pass 'this' (the TestCase context) so the utility can execute verify() and mouseClick()
        UiTestHelper.interactWithButton(this, menuBtn)

        // 4. Verify the signal
        compare(menuClickSpy.count, 1, "menuClicked() signal must be emitted exactly once")
    }
}