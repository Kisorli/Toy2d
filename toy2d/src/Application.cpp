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
    setupDebugMessenger();
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

    std::vector<char const*> requiredLayers;
    if (enableValidationLayers)
    {
        requiredLayers.assign(validationLayers.begin(), validationLayers.end());
    }

    auto layerProperties = context.enumerateInstanceLayerProperties();
    if (
        std::ranges::any_of(
            requiredLayers, [&layerProperties](auto const& requiredLayer)
            {
                return std::ranges::none_of(
                    layerProperties,
                    [requiredLayer](auto const& layerProperty)
                    { return strcmp(layerProperty.layerName,requiredLayer) == 0; }
                );
            }
        )
    )
    {
        throw std::runtime_error("One or more required layers are not support! ");
    }

    auto requiredExtensions = getRequiredExtensions();

    auto extensionProperties = context.enumerateInstanceExtensionProperties();
    for (auto const& requiredExtension : requiredExtensions)
    {
        if (std::ranges::none_of
        (
            extensionProperties,
            [requiredExtension](auto const& extensionProperty)
            { return strcmp(extensionProperty.extensionName, requiredExtension) == 0; }
        ))
        {
            throw std::runtime_error("Required GLFW extension not supported: " + std::string(requiredExtension));
        }
    }

    vk::InstanceCreateInfo createInfo
    (
        {},
        &appInfo,
        static_cast<uint32_t>(requiredLayers.size()),
        requiredLayers.data(),
        static_cast<uint32_t>(requiredExtensions.size()),
        requiredExtensions.data()
    );

    instance = vk::raii::Instance(context, createInfo);
}

void Application::setupDebugMessenger()
{
    if (!enableValidationLayers) return;
    vk::DebugUtilsMessageSeverityFlagsEXT serverityFlags( vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError );
    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags( vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation );
    vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT
    (
        {},
        serverityFlags,
        messageTypeFlags,
        &debugCallback
    );
    debugMessenger = instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
}

VkResult Application::vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* instance)
{
    if (pCreateInfo == nullptr || instance == nullptr)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    return ::vkCreateInstance(pCreateInfo, pAllocator, instance);
}

std::vector<const char *> Application::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
     std::vector extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
     if (enableValidationLayers)
     {
        extensions.push_back(vk::EXTDebugUtilsExtensionName);
     }

     return extensions;
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

VKAPI_ATTR vk::Bool32 VKAPI_CALL Application::debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity, vk::DebugUtilsMessageTypeFlagsEXT type, const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData, void *)
{
    std::cerr << "validation layer: type " << to_string(type) << " msg: " << pCallbackData->pMessage << std::endl;

    if (severity >= vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) 
    {
        // Message is important enough to show
    }

    return vk::False;
}
