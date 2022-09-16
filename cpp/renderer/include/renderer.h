#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <memory>

#include <vulkanUtil.h>

class Renderer {
	public:
		Renderer() {
			init();
		}

		~Renderer() {
			cleanup();
		}
		
	private: 
		void init();
		void cleanup();

	private:
		DeletionQueue _deletionQueue;
};