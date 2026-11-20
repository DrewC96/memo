find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_library(memo_storage STATIC
    StorageManager.cpp
)

target_include_directories(memo_storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(memo_storage PUBLIC memo_core unofficial::sqlite3::sqlite3)
