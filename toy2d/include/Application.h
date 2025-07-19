#pragma once

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

constexpr const uint32_t width = 800;
constexpr const uint32_t height = 600;
constexpr const char* title = "Hello, Trangle";

class Application
{
public:
    void run();

private:
    //Method function
    void initVulkan();
    void initWindow();
    void mainLoop();
    void cleanup();

    //Static method function(Callback)
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    //Method variable
    GLFWwindow* window;
};