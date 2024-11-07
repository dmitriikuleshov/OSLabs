# Create a library from the source files
add_library(lab1_lib
    src/parent.cpp
    src/utils.cpp
    src/child1.cpp
    src/child2.cpp
)

# Specify that the library will search for header files in the include directory
# The PUBLIC type means that this path will be visible to all targets that use lab1_lib
target_include_directories(lab1_lib PUBLIC include)

# Create executable files for child1 and child2
add_executable(child1 src/child1.cpp)
target_link_libraries(child1 lab1_lib)

add_executable(child2 src/child2.cpp)
target_link_libraries(child2 lab1_lib)

# Create an executable file for main, which will use parent
add_executable(lab1_main main.cpp)
target_link_libraries(lab1_main lab1_lib)
