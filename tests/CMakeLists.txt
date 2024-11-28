if(NOT GTest_FOUND)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
endif()
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_test lab1_test.cpp ../lab1/src/parent.cpp ../lab1/include/parent.hpp
        ../lab1/src/utils.cpp ../lab1/include/utils.hpp)
target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab1/include)
add_test(lab1_test lab1_test)

add_executable(lab2_test lab2_test.cpp ../lab2/src/utils.cpp ../lab2/include/utils.hpp)
target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_include_directories(lab2_test PRIVATE ../lab2/include)
add_test(lab2_test lab2_test)

add_executable(lab3_test lab3_test.cpp ../lab3/src/parent.cpp ../lab3/include/parent.hpp
        ../lab3/src/utils.cpp ../lab3/include/utils.hpp)
target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)
add_test(lab1_test lab3_test)



