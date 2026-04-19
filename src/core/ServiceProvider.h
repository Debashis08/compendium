#pragma once
#include "interfaces/IWorkspaceService.h"

class ServiceProvider {
public:
    // Fully inline singleton instance (fixes the LNK errors!)
    static ServiceProvider& instance() {
        static ServiceProvider _instance;
        return _instance;
    }

    // Setters and Getters for Services
    void setWorkspaceService(IWorkspaceService* service) { _workspaceService = service; }
    IWorkspaceService* workspaceService() const { return _workspaceService; }

private:
    ServiceProvider() = default;
    
    // Delete copy/move semantics for strict Singleton
    ServiceProvider(const ServiceProvider&) = delete;
    ServiceProvider& operator=(const ServiceProvider&) = delete;

    IWorkspaceService* _workspaceService = nullptr;
};