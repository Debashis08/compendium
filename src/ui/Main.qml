import QtQuick
import QtQuick.Controls
import App.Backend 1.0

Window {
    id: appWindow
    width: 1024
    height: 768
    visible: true
    title: "My MVVM App"

    // ERROR FIX: 'states' belong to Item, not Window.
    // We create a root Item to act as the State Host.
    Item {
        id: rootContainer
        anchors.fill: parent

        // 1. Bind State to C++ Service
        // We access the AppController through the ServiceProvider singleton
        state: ServiceProvider.appController.currentState

        // 2. The Loader for switching screens
        Loader {
            id: mainLoader
            anchors.fill: parent
        }

        // 3. Define States here (inside the Item)
        states: [
            State {
                name: "Init"
                PropertyChanges { target: mainLoader; sourceComponent: splashScreenComp }
            },
            State {
                name: "Welcome"
                PropertyChanges { target: mainLoader; sourceComponent: welcomeScreenComp }
            },
            State {
                name: "MainWorkspace"
                PropertyChanges { target: mainLoader; sourceComponent: mainDashboardComp }
            }
        ]

        // Transitions (Optional)
        transitions: Transition {
            NumberAnimation { properties: "opacity"; duration: 200 }
        }
    }

    // --- Components defined as before ---
    Component { id: splashScreenComp; Item { /* ... */ } }
    Component { id: welcomeScreenComp; WelcomeScreen { /* ... */ } }
    Component { id: mainDashboardComp; MainDashboard { /* ... */ } }
}
