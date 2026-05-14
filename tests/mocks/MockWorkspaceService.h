#pragma once

#include <gmock/gmock.h>
#include "../../src/core/interfaces/IWorkspaceService.h"
#include <QString>

class MockWorkspaceService : public IWorkspaceService
{
public:
    MOCK_METHOD(QString, getWorkspacePath, (), (const, override));
    MOCK_METHOD(QString, getWorkspaceName, (), (const, override));
    MOCK_METHOD(void, setWorkspacePath, (const QString& path), (override));
    MOCK_METHOD(bool, hasValidWorkspace, (), (const, override));
};