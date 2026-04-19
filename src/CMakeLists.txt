# src/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

# Find Qt modules globally for the source tree
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml StateMachine)

# Enforce build order: Core -> Backend/UI -> App
add_subdirectory(core)
add_subdirectory(backend)
add_subdirectory(ui)
add_subdirectory(app)