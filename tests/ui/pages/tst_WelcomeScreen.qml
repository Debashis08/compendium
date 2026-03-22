// tests/ui/pages/tst_WelcomeScreen.qml
import QtQuick
import QtTest
import QtQuick.Controls
import App.Ui 1.0
import "../utils"

TestCase {
    id: tc
    name: "WelcomeScreenTests"
    when: windowShown

    width: 800
    height: 600
    visible: true

    WelcomeScreen {
        id: welcomeScreen
        anchors.fill: parent
        visible: true

        // 1. THE MOCK: This replaces the need for initTestCase()
        backendController: QtObject {
            property string receivedPath: ""
            function setWorkspacePath(path) {
                receivedPath = path;
            }
        }
    }

    // --- SETUP & TEARDOWN ---

    // Runs automatically AFTER all tests in this file have finished
    function cleanupTestCase() {
        // Give the native Windows dialog thread 50ms to shut down cleanly
        // This prevents the "QWindowsDialogHelperBase... Thread failed to finish" warning.
        tc.wait(50);
    }

    // --- TESTS ---

    function test_01_uiElementsExist() {
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

    function test_03_clickButton() {
        var localBtn = UiTestHelper.findChild(welcomeScreen, "localWorkspaceButton");
        UiTestHelper.interactWithButton(tc, localBtn);
    }
}