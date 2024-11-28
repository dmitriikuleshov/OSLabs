cmake_minimum_required(VERSION 3.10)
project(lab4)

# Enable C support
set(CMAKE_C_STANDARD 11)

# Compilation options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# Directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Header files
include_directories(${LIB_DIR})

# Target: lib1.so
add_library(lib1 SHARED ${SRC_DIR}/lib1.c)
target_link_libraries(lib1 m) # Link with the math library

# Target: lib2.so
add_library(lib2 SHARED ${SRC_DIR}/lib2.c)
target_link_libraries(lib2 m)

# Test program: test_static
add_executable(test_static ${SRC_DIR}/main_static.c)
target_link_libraries(test_static lib1)
target_include_directories(test_static PRIVATE ${LIB_DIR})

# Set runtime library search path
set_target_properties(test_static PROPERTIES BUILD_RPATH ${BUILD_DIR})

# Test program: test_dynamic
add_executable(test_dynamic ${SRC_DIR}/main_dynamic.c)
target_link_libraries(test_dynamic dl m) # Link with dl and the math library
target_include_directories(test_dynamic PRIVATE ${LIB_DIR})

# Set installation path for files
install(TARGETS lib1 lib2 test_static test_dynamic
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
