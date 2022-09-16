#include "vulkanUtil.h"

void CHECK(bool check, const char* fileName, int lineNumber)
{
    if (!check)
    {
        printf("CHECK() failed at %s:%i\n", fileName, lineNumber);
        assert(false);
        exit(EXIT_FAILURE);
    }
}

void createInstance(const char* appName, const std::vector<const char*>& extensions, const std::vector<const char*>& layers, VkInstance* instance) {
    const VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = appName,
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "Chimera",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    const VkInstanceCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(layers.size()),
        .ppEnabledLayerNames = layers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data(),
    };

    VK_CHECK(vkCreateInstance(&createInfo, nullptr, instance));
}