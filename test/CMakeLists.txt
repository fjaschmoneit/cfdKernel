project(test)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(tests_run
        LINALG_Test.cpp
        FVM_Test.cpp
        FIELD_Test.cpp
        MESH_Test.cpp
        APPLICATION_TEST.cpp
        BLAZE_TEST.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(tests_run kernel_lib)

target_link_libraries(tests_run gtest gtest_main)
