# Create a library from the source files
add_library(lab3_lib
    src/parent.cpp
    src/utils.cpp
    src/child1.cpp
    src/child2.cpp
)

# Specify that the library will search for header files in the include directory
# The PUBLIC type means that this path will be visible to all targets that use lab3_lib
target_include_directories(lab3_lib PUBLIC include)

# Create executable files for child1 and child2
add_executable(lab3_child1 src/child1.cpp)
target_link_libraries(lab3_child1 lab3_lib)

add_executable(lab3_child2 src/child2.cpp)
target_link_libraries(lab3_child2 lab3_lib)

# Create an executable file for main, which will use parent
add_executable(lab3_main main.cpp)
target_link_libraries(lab3_main lab3_lib)
