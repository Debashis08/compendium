import QtQuick
import QtTest
import QtQuick.Controls
import App.Ui 1.0
import "../utils"

BaseUiTestCase {
    name: "WelcomeScreenTests"
    when: windowShown

    width: 800
    height: 600
    visible: true

    WelcomeScreen {
        id: welcomeScreen
        anchors.fill: parent
        visible: true

        // 3. INJECT THE MOCK CONTROLLER!
        backendController: QtObject {
            // This property will store whatever the UI tries to send
            property string receivedPath: ""

            // This fake function matches the exact signature of your C++ method
            function setWorkspacePath(path) {
                receivedPath = path;
            }
        }
    }

    // --- TESTS ---
    function test_01_uiElementsExist() {
        var localBtn = findChild(welcomeScreen, "localWorkspaceButton");
        var dialog = findChild(welcomeScreen, "folderDialog");

        verify(localBtn !== null, "FATAL: Local Workspace button not found");
        verify(dialog !== null, "FATAL: Folder dialog not found");
    }

    function test_02_workspaceSelectionLogic() {
        var testPath = "file:///C:/Mock/Workspace/Path";

        // 1. Trigger the logic
        welcomeScreen.processSelectedWorkspace(testPath);

        // 2. Assert the Outcome: Check if the mock received the correct data!
        // This guarantees your QML is wiring the data correctly to the backend interface.
        compare(welcomeScreen.backendController.receivedPath, testPath, "The backend controller did not receive the correct path from the UI");
    }
}