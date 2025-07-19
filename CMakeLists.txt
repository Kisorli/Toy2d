cmake_minimum_required(VERSION 3.15)
project(Toy2D
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDDARD 17)

find_package(glfw3 REQUIRED)

add_subdirectory("toy2d")
add_subdirectory("sandbox")