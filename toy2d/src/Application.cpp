#include"Application.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>

void Application::run()
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Application::initVulkan()
{
    createInstance();
}

void Application::initWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void Application::mainLoop()
{
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

void Application::cleanup()
{
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

void Application::createInstance()
{
    vk::ApplicationInfo appInfo
    ( 
        "Hello Triangle",
        VK_MAKE_VERSION( 1, 0, 0),
        "No Engine",
        VK_MAKE_VERSION( 1, 0, 0),
        vk::ApiVersion14
    );

    uint32_t glfwExtensionCount = 0;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    auto extensionProperties = context.enumerateInstanceExtensionProperties();
    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        if (std::ranges::none_of
        (
            extensionProperties,
            [glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
            { return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }
        ))
        {
            throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
        }
    }

    vk::InstanceCreateInfo createInfo
    (
        {},
        &appInfo,
        glfwExtensionCount,
        glfwExtensions
    );

    instance = vk::raii::Instance(context, createInfo);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        
        default:
            break;
        }
    }
}