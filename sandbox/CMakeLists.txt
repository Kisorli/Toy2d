project(sandbox)

add_executable(sandbox "sandbox.cpp")

target_include_directories(sandbox PRIVATE
    "toy2d/include"
)

target_link_libraries(sandbox PRIVATE toy2d)