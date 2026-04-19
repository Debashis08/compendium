# src/core/CMakeLists.txt

# Define the Core library as a static library
add_library(CoreLib STATIC
    AppConstants.h
    interfaces/IWorkspaceService.h
)

# Core only needs basic Qt Core components
target_link_libraries(CoreLib PUBLIC Qt6::Core)

# Make these headers available to anything that links against CoreLib
target_include_directories(CoreLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
)