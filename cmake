
cmake_minimum_required(VERSION 3.0)
project(YourProjectName)

set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)

add_executable(your_program your_program.c)
target_link_libraries(your_program raylib)

