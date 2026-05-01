#pragma once
#include "interfaces/IWorkspaceService.h"

class ServiceProvider {
public:
    // Fully inline singleton instance.
    static ServiceProvider& instance() {
        static ServiceProvider _instance;
        return _instance;
    }

    // Setters and Getters for Services.
    // Workspace service getters and setters.
    void setWorkspaceService(IWorkspaceService* service) { _workspaceService = service; }
    IWorkspaceService* workspaceService() const { return _workspaceService; }

private:
    ServiceProvider() = default;
    
    // Delete copy/move semantics for strict Singleton
    ServiceProvider(const ServiceProvider&) = delete;
    ServiceProvider& operator=(const ServiceProvider&) = delete;

    // Pointer to get workspace service.
    IWorkspaceService* _workspaceService = nullptr;
};