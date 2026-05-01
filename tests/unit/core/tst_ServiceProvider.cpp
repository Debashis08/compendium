#include <gtest/gtest.h>

// Include the class we are testing
#include "../../src/core/ServiceProvider.h"

// Include our mock service for testing injections
#include "../mocks/MockWorkspaceService.h"

class ServiceProviderTest : public ::testing::Test {
protected:
    // SetUp runs before EVERY test
    void SetUp() override {
        // Guarantee the Singleton starts with a clean slate
        ServiceProvider::instance().setWorkspaceService(nullptr);
    }

    // TearDown runs after EVERY test
    void TearDown() override {
        // Wipe the Singleton clean so it doesn't pollute the next test
        ServiceProvider::instance().setWorkspaceService(nullptr);
    }
};

// --- Actual Unit Tests ---

TEST_F(ServiceProviderTest, IsStrictSingleton) {
    // Act: Grab the instance twice
    ServiceProvider& instance1 = ServiceProvider::instance();
    ServiceProvider& instance2 = ServiceProvider::instance();

    // Assert: Both references MUST point to the exact same memory address
    EXPECT_EQ(&instance1, &instance2);
}

TEST_F(ServiceProviderTest, DefaultsToNullptrBeforeInjection) {
    // Assert: Before anything is set, the getter should safely return null
    EXPECT_EQ(ServiceProvider::instance().workspaceService(), nullptr);
}

TEST_F(ServiceProviderTest, CanSetAndRetrieveWorkspaceService) {
    // Arrange: Create a mock service
    MockWorkspaceService mockService;

    // Act: Inject it into the Service Provider
    ServiceProvider::instance().setWorkspaceService(&mockService);

    // Assert: The pointer we retrieve MUST match the memory address of our mock
    EXPECT_EQ(ServiceProvider::instance().workspaceService(), &mockService);
}