import QtQuick
import QtTest

TestCase {
    id: baseTest

    // 1. Centralized Component Discovery
    function findChild(parentItem, objectName) {
        if (!parentItem) return null;
        for (var i = 0; i < parentItem.data.length; i++) {
            var child = parentItem.data[i];
            if (child.objectName === objectName) return child;
            var result = findChild(child, objectName);
            if (result) return result;
        }
        return null;
    }

    // 2. Centralized Interaction (Replaces flaky wait() calls)
    function interactWithButton(btn) {
        // Wait dynamically for the button to actually render on screen
        tryVerify(function() { return btn.width > 0 && btn.height > 0; }, "Button never laid out properly");

        verify(btn.visible, "Button is invisible");
        verify(btn.enabled, "Button is disabled");

        mouseClick(btn);
    }
}