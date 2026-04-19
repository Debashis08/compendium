The first diagram shows the **Strict Layered Dependencies** (how the four folders relate to each other), and the second diagram maps out the exact **Initialization Lifecycle** (the chronological order of how objects are created and wired together in C++ before the UI loads).

### 1. Architectural Dependency Graph

This flowchart illustrates the "Direction of Dependencies." Notice how all arrows flow inwards toward the `Core` layer, and the `UI` layer only communicates with the `Backend/Bridge` layer, never directly with the `Core`.

```mermaid
flowchart TD
    %% Define Layers
    subgraph AppLayer [src/app/ : The Bootstrapper]
        M[main.cpp]
        SI[ServiceInitializer]
    end

    subgraph UILayer [src/ui/ : The Presentation]
        QML[Main.qml]
    end

    subgraph BackendLayer [src/backend/ : Logic & Bridge]
        AC[AppController\n'appOrchestrator']
        WVM[WorkspaceViewModel]
        WS[WorkspaceService]
    end

    subgraph CoreLayer [src/core/ : The Foundation]
        SP[ServiceProvider]
        IWS[IWorkspaceService]
    end

    %% Initialization & Registration
    M -->|1. Creates| SI
    SI -->|2. Instantiates| WS
    SI -->|3. Instantiates| AC
    SI -->|4. Registers Service into| SP
    
    %% Injection
    M -->|5. Injects into Context| QML

    %% Implementations
    WS -.->|Implements| IWS

    %% Data Flow & Consumption
    WVM -->|Fetches dependency from| SP
    WVM -->|Consumes| IWS
    
    QML -->|Reads currentState from| AC
    QML -->|Binds to Data Properties| WVM

    %% Styling
    classDef core fill:#e1f5fe,stroke:#0288d1,stroke-width:2px;
    classDef backend fill:#fff3e0,stroke:#f57c00,stroke-width:2px;
    classDef ui fill:#e8f5e9,stroke:#388e3c,stroke-width:2px;
    classDef app fill:#f3e5f5,stroke:#7b1fa2,stroke-width:2px;
    
    class SP,IWS core;
    class AC,WVM,WS backend;
    class QML ui;
    class M,SI app;
```

### 2. Object Initialization Lifecycle

This sequence diagram shows the chronological timeline from the moment the user clicks the `.exe` to the moment the QML screen renders. It perfectly captures how you avoided a "God Object" by using a Service Locator and Dependency/Context Injection.

```mermaid
sequenceDiagram
    autonumber
    
    participant Main as main.cpp (App)
    participant SI as ServiceInitializer (App)
    participant SP as ServiceProvider (Core)
    participant WS as WorkspaceService (Backend)
    participant AC as AppController (Backend)
    participant QML as QML Engine (UI)
    participant WVM as WorkspaceViewModel (Backend)

    Note over Main,AC: C++ Bootstrapping Phase
    Main->>SI: Instantiate ServiceInitializer
    SI->>WS: Create WorkspaceService (Concrete)
    SI->>SP: Register WorkspaceService as IWorkspaceService
    Note right of SP: Service Locator is now populated
    
    SI->>AC: Create AppController (Orchestrator)
    Main->>QML: Inject AppController as 'appOrchestrator'
    Note right of Main: UI can now read global state
    
    Note over Main,WVM: UI Rendering Phase
    Main->>QML: engine.loadFromModule("App.Ui", "Main")
    
    QML->>WVM: Call static create() for Singleton
    WVM->>SP: Request IWorkspaceService
    SP-->>WVM: Return pointer to Service
    Note right of WVM: ViewModel is securely connected to Core
    
    QML->>AC: Read appOrchestrator.currentState
    QML->>WVM: Bind to WorkspaceViewModel.workspaceName
    Note left of QML: UI is rendered!
```

### Key Takeaways from the Diagrams:

1. **The App Layer is the Boss:** `main.cpp` and `ServiceInitializer` are the only files that know about *everything*. They act as the master builders, constructing the components and handing them off.
2. **The Core Layer is Blind:** The `ServiceProvider` and `IWorkspaceService` live at the bottom of the dependency tree. They do not know that Qt, QML, or the AppController exist.
3. **The Two Bridges:** The UI connects to the C++ backend through two distinct bridges. It reads global routing state from the `AppController` (injected via Context Property) , and it reads/writes specific screen data through the `WorkspaceViewModel` (instantiated via QML Singleton).