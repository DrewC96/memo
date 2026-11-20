add_library(memo_core STATIC
    Document.cpp
    Stroke.cpp
    SpatialIndex.cpp
)

target_include_directories(memo_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(memo_core PUBLIC cxx_std_17)