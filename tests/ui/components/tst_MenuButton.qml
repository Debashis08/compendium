import QtQuick
import QtQuick.Layouts
import QtTest
import App.Ui
import "../utils"

TestCase {
    id: rootTest
    name: "MenuButtonTests"
    
    // Mimic a small side drawer window size
    width: 250 
    height: 400
    visible: true
    when: windowShown

    // Wrap the button in a ColumnLayout
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        MenuButton {
            id: menuBtn
            text: "Settings"
            icon.source: "qrc:/qt/qml/App/Ui/assets/icons/settings.png"
        }
        
        // Pushes the button to the top like a real drawer
        Item { Layout.fillHeight: true } 
    }

    SignalSpy {
        id: clickSpy
        target: menuBtn
        signalName: "clicked"
    }

    function init() {
        clickSpy.clear()
        // Reset the hover state by moving the fake mouse far away from the button
        mouseMove(rootTest, rootTest.width - 1, rootTest.height - 1)
    }

    function test_defaultProperties() {
        // Test the explicit defaults you set in MenuButton.qml
        compare(menuBtn.icon.width, 13, "Default icon width must be 13")
        compare(menuBtn.icon.height, 13, "Default icon height must be 13")
        compare(menuBtn.font.pixelSize, 10, "Font pixel size must be 10")
        
        // Use Qt.colorEqual instead of === to safely compare color objects
        verify(Qt.colorEqual(menuBtn.palette.buttonText, "black"), "Text should be black")
    }

    function test_hoverBackgroundState() {
        // 1. Give the Layout engine time to size the button
        wait(50)

        // 2. Test default background state
        verify(Qt.colorEqual(menuBtn.background.color, "transparent"), "Background should be transparent when not hovered")

        // 3. Move the mouse precisely over the center of the button to trigger hover
        mouseMove(menuBtn, menuBtn.width / 2, menuBtn.height / 2)
        
        // Give QML's internal state machine a few milliseconds to update the color
        wait(50)

        // 4. Verify the color changed to your custom hex!
        verify(Qt.colorEqual(menuBtn.background.color, "#f2f2f2"), "Background should turn light gray (#f2f2f2) when hovered")
    }

    function test_clickInteraction() {
        // Reuse the bulletproof utility method you built!
        UiTestHelper.interactWithButton(this, menuBtn)

        // Verify the standard QQC2 'clicked' signal fired
        compare(clickSpy.count, 1, "MenuButton should emit clicked() exactly once")
    }
}