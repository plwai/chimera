#pragma once

#include <vector>
#include <cassert>
#include <vulkan/vulkan.h>
#include <deque>
#include <functional>
#include <optional>

#define VK_CHECK(value) CHECK(value == VK_SUCCESS, __FILE__, __LINE__);

void CHECK(bool check, const char* fileName, int lineNumber);

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	printf("validation layer: %s\n", pCallbackData->pMessage);

	return VK_FALSE;
}

struct VulkanInstance {
	VkInstance instance;
	std::vector<const char*> validationLayers;
	VkDebugUtilsMessengerEXT debugMessenger;
};

struct VulkanDevice {
	VkPhysicalDevice physicalDevice;
	VkQueue graphicsQueue;
	VkDevice device;
	std::shared_ptr<VulkanInstance> instance;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
};

struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	}

	void flush() {
		// reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)();
		}

		deletors.clear();
	}
};

bool checkValidationLayerSupport();
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void createInstance(const char* appName, const std::vector<const char*>& extensions, const std::vector<const char*>& layers, VkInstance* instance);
void createPhysicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice);
void createLogicalDevice(VulkanInstance* instance, VulkanDevice* device, bool enableValidationLayers);