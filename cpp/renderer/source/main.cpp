#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <memory>
#include "renderer.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 720;
const char* APPLICATION_NAME = "Chimera Application";
const char* VK_VALIDATION_LAYER_NAME = "VK_LAYER_KHRONOS_validation";

std::unique_ptr<VulkanInstance> vkInit(bool debugMode = false);
void setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT* debugMessenger);

std::unique_ptr<VulkanInstance> vkInit(bool debugMode) {
    auto vkInstance = std::make_unique<VulkanInstance>();

    const char** glfwExtensions;
    uint32_t extensionCount = 0;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

    std::vector<const char*> validationLayers;
    std::vector<const char*> extensions;

    if (debugMode && !checkValidationLayerSupport()) {
        validationLayers.push_back(VK_VALIDATION_LAYER_NAME);

        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    for (uint32_t i = 0; i < extensionCount; i++) {
        extensions.push_back(glfwExtensions[i]);
    }

    createInstance(APPLICATION_NAME, extensions, validationLayers, &vkInstance.get()->instance);

    if (debugMode) {
        setupDebugMessenger(vkInstance.get()->instance, &vkInstance.get()->debugMessenger);
    }

    return std::move(vkInstance);
}

void setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT* debugMessenger) {
    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;

    VK_CHECK(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, debugMessenger));
}


int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Chimera", nullptr, nullptr);

    auto vk = vkInit(true);
    auto renderer = std::make_unique<Renderer>();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    renderer.release();

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}