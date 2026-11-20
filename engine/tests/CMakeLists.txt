find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(DocumentTest DocumentTest.cpp)

target_link_libraries(DocumentTest
    PRIVATE
        memo_core
        memo_storage
        GTest::gtest_main
)

gtest_discover_tests(DocumentTest)