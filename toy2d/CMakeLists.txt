project(toy2d
    LANGUAGES CXX
)

set(SOURCE_FILES "src/test.cpp")

add_library(toy2d SHARED ${SOURCE_FILES})

target_include_directories(toy2d PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_definitions(toy2d PRIVATE BUILD_DLL)