#pragma once

#include <vector>
#include <cassert>
#include <vulkan/vulkan.h>
#include <deque>
#include <functional>

#define VK_CHECK(value) CHECK(value == VK_SUCCESS, __FILE__, __LINE__);

void createInstance(const char* appName, const std::vector<const char*>& extensions, const std::vector<const char*>& layers, VkInstance* instance);

struct VulkanInstance {
	VkInstance instance;
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
