#pragma once
#include "vulkanUtil.h"

class VulkanDevice {
	VkPhysicalDevice physicalDevice;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkDevice raw;
	std::shared_ptr<VulkanInstance> instance;

	public:
		VulkanDevice(std::shared_ptr<VulkanInstance> instance, VkPhysicalDevice physicalDevice) 
			: instance(instance), physicalDevice(physicalDevice) {
			this->createLogicalDevice();
		}

		~VulkanDevice() {
			vkDestroyDevice(raw, nullptr);
		}

	private:
		void createLogicalDevice();
};