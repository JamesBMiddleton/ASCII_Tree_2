cmake_minimum_required(VERSION 3.16.3)

project(ASCII_Tree_2)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Forest)

target_link_libraries(${PROJECT_NAME} forest)
