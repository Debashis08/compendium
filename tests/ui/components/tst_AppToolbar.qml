import QtQuick
import QtTest
import App.Ui

TestCase {
    id: rootTest
    name: "AppToolbarTests"

    // Give the test runner window a physical presence.
    width: 800
    height: 600
    visible: true
    when: windowShown

    // Static declaration.
    AppToolbar {
        id: toolbar
        width: 800
        height: 60
    }

    // Attach the spy directly to the statically declared ID.
    SignalSpy {
        id: menuClickSpy
        target: toolbar
        signalName: "menuClicked"
    }

    function init() {
        // Just clear the spy before each test so counts don't leak.
        menuClickSpy.clear()
    }


    function test_uiProperties() {
        verify(toolbar.visible, "Toolbar should be visible by default")
        compare(toolbar.color.toString(), "#f2f2f2", "Toolbar background color should match")
    }

    function test_menuButtonClickEmitsSignal() {
        compare(menuClickSpy.count, 0, "Signal count should be 0 initially")

        // Give the RowLayout 100ms extra to push the button into place.
        wait(100)

        // Traverse the tree: toolbar -> RowLayout -> Button
        var rowLayout = toolbar.children[0]
        var menuBtn = rowLayout.children[0]

        // Safety check to ensure we grabbed the object and it has physical dimensions.
        verify(menuBtn !== undefined, "Menu button could not be found in the tree")
        verify(menuBtn.width > 0, "Button width must be greater than 0 to be clicked")
        verify(menuBtn.height > 0, "Button height must be greater than 0 to be clicked")

        // Click the button mathematically.
        mouseClick(menuBtn)

        compare(menuClickSpy.count, 1, "menuClicked() signal must be emitted exactly once")
    }
}