#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Add Qt Test includes for async waiting
#include <QCoreApplication>
#include <QSignalSpy>

// Include the class we are testing
#include "../../src/backend/bridges/AppController.h"

// Include our mocks and service locator
#include "MockWorkspaceService.h"
#include "../../src/core/ServiceProvider.h"

using ::testing::Return;

class AppControllerTest : public ::testing::Test
{
protected:
    AppController* controller;
    MockWorkspaceService mockWorkspaceService;

    void SetUp() override {
        // Inject our mock into the central registry so AppController uses it
        ServiceProvider::instance().setWorkspaceService(&mockWorkspaceService);

        // Instantiate the controller
        controller = new AppController(&mockWorkspaceService);
    }

    void TearDown() override {
        delete controller;
        // Clean up the service registry to prevent test pollution
        ServiceProvider::instance().setWorkspaceService(nullptr);
    }
};

// --- Actual Unit Tests ---

TEST_F(AppControllerTest, InitialStateIsSetCorrectly) {
    // Force the Qt Event Loop to process the state machine "start" event
    QCoreApplication::processEvents();

    // Verify the state machine starts where we expect (Convert QString to std::string)
    EXPECT_EQ(controller->currentState().toStdString(), "initialState");
}

TEST_F(AppControllerTest, TransitionsToWelcomeWhenNoWorkspace) {
    // Arrange: Tell the mock to pretend there is NO valid workspace
    EXPECT_CALL(mockWorkspaceService, hasValidWorkspace())
        .WillOnce(Return(false));

    // Act:
    // The AppController automatically starts a timer on initialization.
    // We use QSignalSpy to wait until that timer finishes and emits its signal.
    QSignalSpy checkSpy(controller, &AppController::checkCompletedNeedsSetup);

    // This safely waits for the signal (up to 5 seconds) without freezing the app
    checkSpy.wait();

    // Give the state machine one final tick to process the actual transition
    QCoreApplication::processEvents();

    // Assert: Verify state changed to welcome
    EXPECT_EQ(controller->currentState().toStdString(), "welcomeState");
}

TEST_F(AppControllerTest, TransitionsToWorkspaceWhenValidWorkspaceExists) {
    // Arrange: Tell the mock to pretend a workspace DOES exist
    EXPECT_CALL(mockWorkspaceService, hasValidWorkspace())
        .WillOnce(Return(true));

    // Act: Listen for the other signal this time
    QSignalSpy checkSpy(controller, &AppController::checkCompletedReady);

    checkSpy.wait(); // Wait for the timer to fire

    QCoreApplication::processEvents(); // Allow the transition to occur

    // Assert: Verify state changed to workspace
    EXPECT_EQ(controller->currentState().toStdString(), "workspaceState");
}