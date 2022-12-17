#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <vector>
#include <cassert>
#include <vulkan/vulkan.h>
#include <deque>
#include <functional>
#include <optional>
#include <set>

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

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator); 

struct VulkanInstance {
	VkInstance raw;
	VkSurfaceKHR surface;
	std::vector<const char*> validationLayers;
	VkDebugUtilsMessengerEXT debugMessenger;

	~VulkanInstance() {
		if (static_cast<uint32_t>(validationLayers.size())) {
			DestroyDebugUtilsMessengerEXT(raw, debugMessenger, nullptr);
		}

		vkDestroySurfaceKHR(raw, surface, nullptr);
		vkDestroyInstance(raw, nullptr);
	}
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
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
void createSurface(GLFWwindow* window, VkInstance instance, VkSurfaceKHR* surface);
void createPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice* physicalDevice);

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);