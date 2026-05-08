# tests/shared/CMakeLists.txt

# Create a static library just for our custom main() function
add_library(SharedTestMain STATIC
    main.cpp
)

# Link the libraries that main.cpp needs to initialize Qt and GTest
target_link_libraries(SharedTestMain PUBLIC
    Qt6::Core
    Qt6::Test
    GTest::gtest
)