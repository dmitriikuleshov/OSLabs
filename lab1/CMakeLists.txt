# Указываем минимальные необходимые версии и проект
cmake_minimum_required(VERSION 3.10)

# Создаем библиотеку из исходников
add_library(lab1_lib
    src/parent.cpp
    src/utils.cpp
    src/child1.cpp
    src/child2.cpp
)

# Указывает, что библиотека будет искать заголовочные файлы в каталоге include
target_include_directories(lab1_lib PUBLIC include)

# Создаем исполняемые файлы для child1 и child2
add_executable(child1 src/child1.cpp)
target_link_libraries(child1 lab1_lib)

add_executable(child2 src/child2.cpp)
target_link_libraries(child2 lab1_lib)

# Создаем исполняемый файл main, который будет использовать parent
add_executable(main main.cpp)
target_link_libraries(main lab1_lib)
