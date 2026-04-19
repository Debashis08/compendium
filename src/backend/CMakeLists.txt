# src/backend/CMakeLists.txt

# Load Secrets & Environment Variables (Optional)
include("${CMAKE_SOURCE_DIR}/Secrets.local.cmake" OPTIONAL)
set(GOOGLE_CLIENT_ID "$ENV{GOOGLE_CLIENT_ID}")
set(GOOGLE_CLIENT_SECRET "$ENV{GOOGLE_CLIENT_SECRET}")

if(NOT GOOGLE_CLIENT_ID OR NOT GOOGLE_CLIENT_SECRET)
    message(WARNING "BackendLib: Google OAuth keys are missing. Auth will not work.")
endif()

# Define Source Files
set(BACKEND_SOURCES
    bridge/AppController.h
    bridge/AppController.cpp
    bridge/WorkspaceViewModel.h
    bridge/WorkspaceViewModel.cpp
    services/LoggerService.h
    services/LoggerService.cpp
    services/WorkspaceService.h
    services/WorkspaceService.cpp
)

# Create QML Module for the Backend
qt_add_qml_module(BackendLib
    STATIC
    URI "App.Backend"
    VERSION 1.0
    SOURCES ${BACKEND_SOURCES}
)

# Inject Secrets into backend
target_compile_definitions(BackendLib PRIVATE
    CLIENT_ID="${GOOGLE_CLIENT_ID}"
    CLIENT_SECRET="${GOOGLE_CLIENT_SECRET}"
)

# Make headers available to the App orchestrator
target_include_directories(BackendLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/bridge
    ${CMAKE_CURRENT_SOURCE_DIR}/services
)

# Link against CoreLib and necessary Qt modules
target_link_libraries(BackendLib 
    PUBLIC 
    CoreLib
    Qt6::Quick
    Qt6::Qml
    Qt6::StateMachine
)