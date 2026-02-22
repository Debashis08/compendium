import QtQuick
import QtQuick.Controls
import QtQuick.Window

import App.Backend 1.0

Window {
    id: appWindow
    width: 1080
    height: 720
    visible: true
    title: "Compendium"

    // Optional: Default background color for the whole window
    // color: "#1E1E1E"

    // ERROR FIX: 'states' belong to Item, not Window.
    Item {
        id: rootContainer
        anchors.fill: parent

        // 2. BIND STATE TO C++
        // This is the magic line. It listens to the C++ State Machine.
        // If AppController sets state to "Welcome", this QML state automatically updates.
        state: ServiceProvider.appController ? ServiceProvider.appController.currentState : "Init"

        // 3. THE LOADER
        Loader {
            id: mainLoader
            anchors.fill: parent
            // Helper to keep focus when screens change
            focus: true
        }

        // 4. DEFINE STATES
        // These names MUST match the strings in AppController.cpp (setCurrentState)
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

        // 5. TRANSITIONS
        // A simple cross-fade when switching screens
        transitions: Transition {
            NumberAnimation {
                target: mainLoader.item
                property: "opacity"
                from: 0.0
                to: 1.0
                duration: 300
                easing.type: Easing.OutQuad
            }
        }
    }

    // --- COMPONENT DEFINITIONS ---

    Component {
        id: splashScreenComp
        // Simple loading text while C++ checks settings
        Rectangle {
            color: "#1E1E1E"
            Column {
                anchors.centerIn: parent
                spacing: 20
                BusyIndicator { running: true }
                Text {
                    text: "Loading Compendium..."
                    color: "white"
                    font.pixelSize: 18
                }
            }
        }
    }

    Component {
        id: welcomeScreenComp
        // This loads the WelcomeScreen.qml file we created
        WelcomeScreen {
            // We can handle signals here if needed, but usually
            // WelcomeScreen calls the ServiceProvider directly.
        }
    }

    Component {
        id: mainDashboardComp
        // This loads the MainDashboard.qml file we created
        MainDashBoard {

        }
    }
}
