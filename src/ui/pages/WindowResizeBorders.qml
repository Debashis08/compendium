import QtQuick
import QtQuick.Window

// This component creates invisible 5-pixel borders around your app
// that trigger the native OS window resizing.
Item {
    id: root
    anchors.fill: parent

    // Thickness of the resize border
    readonly property int borderSize: 5

    // TOP BORDER
    MouseArea {
        height: root.borderSize
        anchors { top: parent.top; left: parent.left; right: parent.right; /*margins: root.borderSize*/ }
        cursorShape: Qt.SizeVerCursor
        onPressed: Window.window.startSystemResize(Qt.TopEdge)
    }

    // BOTTOM BORDER
    MouseArea {
        height: root.borderSize
        anchors { bottom: parent.bottom; left: parent.left; right: parent.right; margins: root.borderSize }
        cursorShape: Qt.SizeVerCursor
        onPressed: Window.window.startSystemResize(Qt.BottomEdge)
    }

    // LEFT BORDER
    MouseArea {
        width: root.borderSize
        anchors { top: parent.top; bottom: parent.bottom; left: parent.left; margins: root.borderSize }
        cursorShape: Qt.SizeHorCursor
        onPressed: Window.window.startSystemResize(Qt.LeftEdge)
    }

    // RIGHT BORDER
    MouseArea {
        width: root.borderSize
        anchors { top: parent.top; bottom: parent.bottom; right: parent.right; /*margins: root.borderSize */}
        cursorShape: Qt.SizeHorCursor
        onPressed: Window.window.startSystemResize(Qt.RightEdge)
    }

    // TOP-LEFT CORNER
    MouseArea {
        width: root.borderSize * 2; height: root.borderSize * 2
        anchors { top: parent.top; left: parent.left }
        cursorShape: Qt.SizeFDiagCursor
        onPressed: Window.window.startSystemResize(Qt.TopEdge | Qt.LeftEdge)
    }

    // TOP-RIGHT CORNER
    MouseArea {
        width: root.borderSize * 2; height: root.borderSize * 2
        anchors { top: parent.top; right: parent.right }
        cursorShape: Qt.SizeBDiagCursor
        onPressed: Window.window.startSystemResize(Qt.TopEdge | Qt.RightEdge)
    }

    // BOTTOM-LEFT CORNER
    MouseArea {
        width: root.borderSize * 2; height: root.borderSize * 2
        anchors { bottom: parent.bottom; left: parent.left }
        cursorShape: Qt.SizeBDiagCursor
        onPressed: Window.window.startSystemResize(Qt.BottomEdge | Qt.LeftEdge)
    }

    // BOTTOM-RIGHT CORNER
    MouseArea {
        width: root.borderSize * 2; height: root.borderSize * 2
        anchors { bottom: parent.bottom; right: parent.right }
        cursorShape: Qt.SizeFDiagCursor
        onPressed: Window.window.startSystemResize(Qt.BottomEdge | Qt.RightEdge)
    }
}
