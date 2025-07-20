#pragma once

#include <vulkan/vulkan_raii.hpp>
#include <vulkan/vk_platform.h>

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

constexpr const uint32_t width = 800;
constexpr const uint32_t height = 600;
constexpr const char* title = "Hello, Trangle";

const std::vector validationLayers = 
{
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

std::vector<const char*> deviceExtensions = {
    vk::KHRSwapchainExtensionName,
    vk::KHRSpirv14ExtensionName,
    vk::KHRSynchronization2ExtensionName,
    vk::KHRCreateRenderpass2ExtensionName
};

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

    //For initVulkan function
    void createInstance();
    void setupDebugMessenger();
    void pickPhysicalDevice();

    //Other function
    VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* instance);
    std::vector<const char*> getRequiredExtensions();

    //Callback function
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity, vk::DebugUtilsMessageTypeFlagsEXT type, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void*);

    //Method variable
    GLFWwindow* window;

    vk::raii::Context context;
    vk::raii::Instance instance = nullptr;
    vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;
    vk::raii::PhysicalDevice physicalDevice;
};