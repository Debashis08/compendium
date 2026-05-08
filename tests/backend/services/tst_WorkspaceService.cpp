#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QSettings>
#include <QTemporaryDir>
#include <QString>

// Include the class we are testing
#include "backend/services/WorkspaceService.h"

class WorkspaceServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // IMPORTANT: Isolate QSettings for this specific test suite!
        // By changing the app/org names, QSettings writes to a temporary "sandbox"
        // in the Windows Registry instead of overwriting your real application's saved data.
        QCoreApplication::setOrganizationName("CompendiumTestOrg");
        QCoreApplication::setApplicationName("WorkspaceServiceTestApp");

        // Clear any lingering settings from previous test runs to guarantee a clean slate
        QSettings settings;
        settings.clear();
    }

    void TearDown() override {
        // Clean up the sandbox registry settings after the test finishes
        QSettings settings;
        settings.clear();
    }
};

// --- Actual Unit Tests ---

TEST_F(WorkspaceServiceTest, InitializesWithEmptySettings) {
    WorkspaceService service;

    // Assert: Since QSettings is empty, it should default to safe fallback values
    EXPECT_EQ(service.getWorkspacePath().toStdString(), "");
    EXPECT_EQ(service.getWorkspaceName().toStdString(), "No Workspace");
    EXPECT_FALSE(service.hasValidWorkspace());
}

TEST_F(WorkspaceServiceTest, SanitizesQmlFilePathsCorrectly) {
    WorkspaceService service;

    // Arrange: Simulate the exact string a QML FileDialog returns on Windows
    QString mockQmlPath = "file:///C:/Users/Test/MyWorkspace";

    // Act: Set the path
    service.setWorkspacePath(mockQmlPath);

    // Assert: Verify it stripped the 'file://' and the leading slash
#ifdef Q_OS_WIN
    EXPECT_EQ(service.getWorkspacePath().toStdString(), "C:/Users/Test/MyWorkspace");
#else
    EXPECT_EQ(service.getWorkspacePath().toStdString(), "/C:/Users/Test/MyWorkspace");
#endif

    // Assert: Verify the folder name was extracted correctly
    EXPECT_EQ(service.getWorkspaceName().toStdString(), "MyWorkspace");
}

TEST_F(WorkspaceServiceTest, PersistsPathToQSettings) {
    // Act: Create a service, set a path, and let the service be destroyed
    {
        WorkspaceService service1;
        service1.setWorkspacePath("D:/Saved/EnterpriseApp");
    }

    // Assert: Create a brand new service instance.
    // It should automatically load the path we just saved into QSettings.
    WorkspaceService service2;
    EXPECT_EQ(service2.getWorkspacePath().toStdString(), "D:/Saved/EnterpriseApp");
    EXPECT_EQ(service2.getWorkspaceName().toStdString(), "EnterpriseApp");
}

TEST_F(WorkspaceServiceTest, ValidationChecksRealFileSystem) {
    WorkspaceService service;

    // Arrange 1: A fake directory path
    service.setWorkspacePath("C:/This/Directory/Should/Never/Exist/12345");

    // Assert 1: QDir should correctly identify this doesn't exist
    EXPECT_FALSE(service.hasValidWorkspace());

    // Arrange 2: Create a REAL, temporary folder on the hard drive using QTemporaryDir
    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid()) << "Could not create temporary directory for test.";

    // Act 2: Point the service to the real temporary folder
    service.setWorkspacePath(tempDir.path());

    // Assert 2: QDir should see the real folder and return true
    EXPECT_TRUE(service.hasValidWorkspace());

    // Note: QTemporaryDir automatically deletes the folder from your hard drive
    // when it goes out of scope at the end of this test!
}