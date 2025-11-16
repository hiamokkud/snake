cmake_minimum_required(VERSION 3.25)
project(snake LANGUAGES C CXX)

add_subdirectory(third_party/raylib)
add_executable(snake example.cpp)
target_link_libraries(snake PUBLIC raylib)
