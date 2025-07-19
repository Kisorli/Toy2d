cmake_minimum_required(VERSION 3.15)
project(Toy2D
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory("toy2d")
add_subdirectory("sandbox")