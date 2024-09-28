cmake_minimum_required(VERSION 3.10)
project(MyLabProject)

# Указываем, что мы будем использовать C++ и стандарт C++17
set(CMAKE_CXX_STANDARD 17)

# Включаем подкаталог lab1
add_subdirectory(lab1)

# Включаем подкаталог tests
add_subdirectory(tests)
