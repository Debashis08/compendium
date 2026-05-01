#include <gtest/gtest.h>
#include <QCoreApplication> // Required because initialize() uses qApp

// Include the class we are testing
#include "../../src/app/ServiceInitializer.h"

// Include the Service Locator to verify registration
#include "../../src/core/ServiceProvider.h"

class ServiceInitializerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure the global Service Locator is completely empty before we begin
        ServiceProvider::instance().setWorkspaceService(nullptr);
    }

    void TearDown() override {
        // Clean up the global state so this test doesn't pollute other tests
        ServiceProvider::instance().setWorkspaceService(nullptr);
    }
};

// --- Actual Unit Tests ---

TEST_F(ServiceInitializerTest, SuccessfullyWiresDependenciesOnInitialization) {
    // Arrange: Create the initializer
    ServiceInitializer initializer;

    // Verify pre-conditions (everything should be null)
    EXPECT_EQ(initializer.getAppController(), nullptr);
    EXPECT_EQ(ServiceProvider::instance().workspaceService(), nullptr);

    // Act: Run the initialization sequence
    initializer.initialize();

    // Assert 1: The AppController was successfully created
    EXPECT_NE(initializer.getAppController(), nullptr);

    // Assert 2: The WorkspaceService was created AND registered in the ServiceProvider
    EXPECT_NE(ServiceProvider::instance().workspaceService(), nullptr);
}