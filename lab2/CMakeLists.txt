# Create a library from the source files
add_library(lab2_lib
    src/utils.cpp
)

# Specify that the library will search for header files in the include directory
# The PUBLIC type means that this path will be visible to all targets that use lab1_lib
target_include_directories(lab2_lib PUBLIC include)

# Create an executable file for main, which will use parent
add_executable(lab2_main main.cpp)
target_link_libraries(lab2_main lab2_lib)

add_executable(lab2_research research/find_time.cpp)
