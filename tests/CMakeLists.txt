# Указываем минимальные необходимые версии и проект
cmake_minimum_required(VERSION 3.10)

# Найдите Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Создаем исполняемый файл для тестов
add_executable(lab1_test lab1_test.cpp)

# Связываем тесты с необходимыми библиотеками
target_link_libraries(lab1_test GTest::GTest GTest::Main lab1_lib)
