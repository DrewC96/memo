cmake_minimum_required(VERSION 3.10)
project(MemoProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add core library
add_library(core_lib
    engine/core/Document.cpp
    engine/core/SpatialIndex.cpp
    engine/core/Stroke.cpp
    engine/render/Renderer.cpp
    engine/storage/StorageManager.cpp
    engine/capi/MemoAPI.cpp
)

# Set include directories for the library
target_include_directories(core_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/core
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/render
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/storage
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/capi
)

# Add main executable
add_executable(memo_app main.cpp)

# Link library to main app
target_link_libraries(memo_app core_lib)

# Add test executable
add_executable(document_test engine/tests/DocumentTest.cpp)

# Link library to test (gtest is handled separately in the project configuration)
target_link_libraries(document_test core_lib)

# Set include directories for test
target_include_directories(document_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/core
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/render
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/storage
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/capi
)

# Add test
add_test(NAME DocumentTest COMMAND document_test)