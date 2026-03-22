// tests/ui/pages/tst_WelcomeScreen.qml
import QtQuick
import QtTest
import QtQuick.Controls
import App.Ui 1.0
import "../utils"

TestCase {
    id: tc // <-- Give the TestCase an ID so we can pass it to the helper
    name: "WelcomeScreenTests"
    when: windowShown

    width: 800
    height: 600
    visible: true

    WelcomeScreen {
        id: welcomeScreen
        anchors.fill: parent
        visible: true

        // Mocking the backend dependency
        backendController: QtObject {
            property string receivedPath: ""
            function setWorkspacePath(path) {
                receivedPath = path;
            }
        }
    }

    // --- TESTS ---

    function test_01_uiElementsExist() {
        // Look how clean this is! Calling the global singleton directly.
        var localBtn = UiTestHelper.findChild(welcomeScreen, "localWorkspaceButton");
        var dialog = UiTestHelper.findChild(welcomeScreen, "folderDialog");

        verify(localBtn !== null, "FATAL: Local Workspace button not found");
        verify(dialog !== null, "FATAL: Folder dialog not found");
    }

    function test_02_workspaceSelectionLogic() {
        var testPath = "file:///C:/Mock/Workspace/Path";
        welcomeScreen.processSelectedWorkspace(testPath);
        compare(welcomeScreen.backendController.receivedPath, testPath, "Controller received incorrect path");
    }

    // Example of using the interaction helper:
    function test_03_clickButton() {
        var localBtn = UiTestHelper.findChild(welcomeScreen, "localWorkspaceButton");
        UiTestHelper.interactWithButton(tc, localBtn); // Pass 'tc' here!
    }
}