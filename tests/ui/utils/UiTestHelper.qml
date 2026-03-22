// tests/ui/utils/UiTestHelper.qml
pragma Singleton
import QtQuick

QtObject {
    id: root

    // 1. Component Discovery (Does not need test context)
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

    // 2. UI Interaction (Needs the 'tc' context to call verify/mouseClick)
    function interactWithButton(tc, btn) {
        // ADDED 5000: This tells the engine to keep trying for up to 5 seconds
        // before failing with the custom message.
        tc.tryVerify(function() { return btn.width > 0 && btn.height > 0; }, 5000, "Button never laid out properly");

        tc.verify(btn.visible, "Button is invisible");
        tc.verify(btn.enabled, "Button is disabled");

        tc.mouseClick(btn);
    }
}