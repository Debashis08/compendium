#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the class we are testing
#include "../../src/backend/bridges/AppController.h"

// Include our mocks and service locator
#include "MockWorkspaceService.h"
#include "../../src/core/ServiceProvider.h"
#include "../../src/backend/services/WorkspaceService.h"

using ::testing::Return;

class AppControllerTest : public ::testing::Test {
protected:
    AppController* controller;
    MockWorkspaceService mockWorkspaceService;

    // This runs before EVERY test
    void SetUp() override {
        // Inject our mock into the central registry so AppController uses it
        ServiceProvider::instance().setWorkspaceService(&mockWorkspaceService);
        
        // Instantiate the controller
        controller = new AppController(&mockWorkspaceService);
    }

    // This runs after EVERY test
    void TearDown() override {
        delete controller;
        // Clean up the service registry to prevent test pollution
        ServiceProvider::instance().setWorkspaceService(nullptr);
    }
};

// --- Actual Unit Tests ---

TEST_F(AppControllerTest, InitialStateIsSetCorrectly) {
    // Verify the state machine starts where we expect
    EXPECT_EQ(controller->currentState(), "initialState");
}

TEST_F(AppControllerTest, TransitionsToWelcomeWhenNoWorkspace) {
    // Arrange: Tell the mock to pretend there is NO valid workspace
    EXPECT_CALL(mockWorkspaceService, hasValidWorkspace())
        .WillOnce(Return(false));

    // Act: Trigger the startup sequence
    // controller->initialize(); // (Replace with whatever method starts your app logic)

    // Assert: Verify state changed to welcome
    // EXPECT_EQ(controller->currentState(), "welcomeState");
}

TEST_F(AppControllerTest, TransitionsToWorkspaceWhenValidWorkspaceExists) {
    // Arrange: Tell the mock to pretend a workspace DOES exist
    EXPECT_CALL(mockWorkspaceService, hasValidWorkspace())
        .WillOnce(Return(true));

    // Act: Trigger the startup sequence
    // controller->initialize();

    // Assert: Verify state changed to workspace
    // EXPECT_EQ(controller->currentState(), "workspaceState");
}