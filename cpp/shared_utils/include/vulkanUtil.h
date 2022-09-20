#pragma once

#include <vector>
#include <cassert>
#include <vulkan/vulkan.h>
#include <deque>
#include <functional>

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

bool checkValidationLayerSupport();
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void createInstance(const char* appName, const std::vector<const char*>& extensions, const std::vector<const char*>& layers, VkInstance* instance);
void createPhysicalDevice(VkPhysicalDevice* physicalDevice);

struct VulkanInstance {
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
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
