# Testing Architecture & Guide

This document outlines the testing strategy, architecture, and known quirks for the Compendium project. We use **QtTest** for QML UI components and **Google Test (GTest)** for the C++ backend.

## 1. UI Testing Architecture (QML)

Our QML tests are strictly decoupled from the real C++ backend. This ensures tests run in milliseconds, do not require human interaction (like clicking native OS dialogs), and run reliably in CI/CD pipelines.

### The Autotest Parser Limitation

Qt Creator's Autotest plugin uses a static text parser. To ensure tests appear in the IDE's Test Explorer, **every QML test file must have `TestCase` as its root element.** Because we cannot use custom base classes (like `BaseUiTestCase { ... }`), shared test logic is implemented using a **QML Singleton**.

### The `UiTestHelper` Singleton

All shared UI test logic (component discovery, standardized button clicks) lives in `tests/ui/utils/UiTestHelper.qml`.

**Usage in tests:**

QML

```qml
import QtTest
import "../utils" // Imports the helper singleton

TestCase {
    name: "ExampleTest"
    
    function test_clickButton() {
        var btn = UiTestHelper.findChild(myComponent, "submitButton");
        UiTestHelper.interactWithButton(tc, btn); // Pass 'tc' for execution context
    }
}
```

### Mocking C++ Dependencies (Dependency Injection)

UI components should never call global C++ singletons directly (e.g., `ServiceProvider.appController`). This causes tests to crash with `null` references because the standard test runner (`tst_ui.exe`) does not initialize the full C++ backend.

**The Standard:** Inject the dependency via a property that defaults to the real backend in production, but can be overwritten with a `QtObject` mock in tests.

*Production QML:*

QML

```json
property var backendController: ServiceProvider.appController
// ...
backendController.setWorkspacePath(folderUrl)
```

*Test QML:*

QML

```json
backendController: QtObject {
    property string receivedPath: ""
    function setWorkspacePath(path) { receivedPath = path; }
}
```

## 2. CMake Configuration for Tests

When adding new tests or resources, `tests/ui/CMakeLists.txt` must be updated correctly.

### Registering Test Files

Do not use `add_test()`. Use `qt_add_test()` and explicitly list all `.qml` files so the Qt Creator code model indexes them.

CMake

```json
qt_add_test(NAME tst_ui
    TestSetup.cpp
    utils/UiTestHelper.qml
    pages/tst_MyNewTest.qml
)
```

### Resolving Missing Image Warnings

If the test runner complains about missing `qrc:/` images, you must bundle the main application's resource file directly into the test executable:

CMake

```json
    # Inside qt_add_test:
    ${CMAKE_SOURCE_DIR}/src/resources.qrc
```

### The Sibling Import Rule

To allow test files to resolve relative paths cleanly, the QML test engine is locked to the test directory using this macro:

CMake

```json
target_compile_definitions(tst_ui PRIVATE
    QUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)
```

## 3. Known Quirks & Troubleshooting

### The "Test Not Showing in IDE" Issue

If a new test is running in the console but not showing in the Autotest panel:

1. Ensure the root element is exactly `TestCase {`.
2. Ensure the file is listed in `qt_add_test`.
3. Go to **Build > Clear CMake Configuration**.
4. Right-click the project folder and **Run CMake**.
5. Click **Rescan Tests** in the Autotest panel.

### The Windows Thread Warning

You may see the following warning at the very end of a test run on Windows:

> `QCRITICAL: qt.qpa.dialogs: QWindowsDialogHelperBase... Thread failed to finish.`

**Cause:** The QML test engine shuts down faster than the native Windows File Explorer background thread can terminate.
**Fix:** This is harmless. However, to silence it, add a 50ms teardown delay to tests utilizing native dialogs:

QML

```qml
function cleanupTestCase() {
    tc.wait(50); 
}
```