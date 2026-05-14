#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QString>
#include <QSignalSpy>

#include "../../src/backend/bridges/WorkspaceViewModel.h"
#include "../mocks/MockWorkspaceService.h"

using ::testing::Return;

class WorkspaceViewModelTest : public :: testing::Test
{
protected:
    MockWorkspaceService mockWorkspaceService;
    WorkspaceViewModel* workspaceViewModel;

    void SetUp() override
    {
        workspaceViewModel = new WorkspaceViewModel(&mockWorkspaceService);
    }

    void TearDown() override
    {
        delete workspaceViewModel;
    }
};

// Unit tests.
TEST_F(WorkspaceViewModelTest, GettersDelegateToServiceSuccessfully)
{
    // Arrange: Tell the mock what to return when asked
    EXPECT_CALL(mockWorkspaceService, getWorkspacePath())
        .WillOnce(Return(QString("D:/mock/old/path")));

    EXPECT_CALL(mockWorkspaceService, getWorkspaceName())
        .WillOnce(Return(QString("MockWorkspace")));

    // Assert: Verify the ViewModel passes those exact values through to the UI
    EXPECT_EQ(workspaceViewModel->workspacePath().toStdString(), "D:/mock/old/path");
    EXPECT_EQ(workspaceViewModel->workspaceName().toStdString(), "MockWorkspace");
}

TEST_F(WorkspaceViewModelTest, SetWorkspacePathUpdatesServiceAndEmitsSignal)
{
    QString newPath = "D:/mock/new/path";

    // Arrnage 1: Expect the workspaceViewModel to pass the path down to the service only once.
    EXPECT_CALL(mockWorkspaceService, setWorkspacePath(newPath)).Times(1);

    // Arrange 2: Spy on the workspaceChanged signal
    QSignalSpy signalSpy(workspaceViewModel, &WorkspaceViewModel::workspaceChanged);

    // Act: Simulate QML calling the setter
    workspaceViewModel->setWorkspacePath(newPath);

    // Assert: Verify the signal fired exactly once so QML knows to redraw
    EXPECT_EQ(signalSpy.count(), 1);
}

TEST_F(WorkspaceViewModelTest, FailsGracefullyIfServiceIsNull)
{
    // Arrange: Create a ViewModel with a deliberately null service pointer
    WorkspaceViewModel nullViewModel(nullptr);

    // Assert 1: Getters should return empty strings, NOT crash the app
    EXPECT_EQ(nullViewModel.workspacePath().toStdString(), "");
    EXPECT_EQ(nullViewModel.workspaceName().toStdString(), "");

    // Assert 2: Calling a setter should do nothing and NOT crash
    // (We wrap this in EXPECT_NO_FATAL_FAILURE to explicitly document that we are testing crash-safety)
    EXPECT_NO_FATAL_FAILURE({
        nullViewModel.setWorkspacePath("Crash/Test");
    });
}