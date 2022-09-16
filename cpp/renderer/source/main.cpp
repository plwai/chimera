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

std::unique_ptr<VulkanInstance> vkInit() {
    auto vkInstance = std::make_unique<VulkanInstance>();

    const char** glfwExtensions;
    uint32_t extensionCount = 0;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

    std::vector<const char*> validationLayers =
    {
        "VK_LAYER_KHRONOS_validation"
    };

    std::vector<const char*> extensions =
    {
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME
    };

    for (uint32_t i = 0; i < extensionCount; i++) {
        extensions.push_back(glfwExtensions[i]);
    }

    createInstance("Chimera Application", extensions, validationLayers, &vkInstance.get()->instance);

    return std::move(vkInstance);
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Chimera", nullptr, nullptr);

    auto vk = vkInit();
    auto renderer = std::make_unique<Renderer>();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    renderer.release();

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}