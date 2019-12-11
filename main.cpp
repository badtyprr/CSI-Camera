/******************************************************************************
Towards learning Vulkan to integrate with a CSI camera

Dependencies:
 * vulkan >= 1.1.100 
 * glfw3 >= 3.2
 * spdlog >= 1.4.2
*****************************************************************************/
// GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Logging
#include "spdlog/spdlog.h"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
// Use for Resource Management, automatic allocation/deallocation of memory objects, by overloading std::shared_ptr and RAII principles
// Source: https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Base_code
// Source: https://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization
//#include <memory>

// Debug
#define DEBUG

// Window Parameters
const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
	initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
	GLFWwindow* window;
	VkInstance instance;

    void initWindow() {
		spdlog::debug("Initializing GLFW...");
		glfwInit();
	
		// GLFW historically required OpenGL, but we're using Vulkan
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		// Temporarily disable window resizing
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		spdlog::debug("Creating GLFW window...");
		// Parameters: X, Y, window_name, monitor, OpenGL_stuff
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

	void createInstance() {
		// Application info struct for the driver
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;
		// Default initialization
		appInfo.pNext = nullptr;

		// Defines global extensions and validation layers
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		
		// Get extensions from GLFW
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		
		spdlog::debug("Getting available Vulkan extensions from GLFW...");
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		spdlog::debug("Number of extensions (GLFW): {}", glfwExtensionCount);

		// Get extensions from Vulkan directly
		uint32_t vkExtensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);
		std::vector<VkExtensionProperties> vkExtensions(vkExtensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, vkExtensions.data());
		spdlog::debug("Available extensions (Vulkan): {}", vkExtensionCount);
		for (const auto& vkExtension : vkExtensions) {
			spdlog::debug("\t{} {}", vkExtension.extensionName, vkExtension.specVersion);
		}

		// Vulkan extensions
		// TODO: I want to pass in vkExtension information instead of glfw, but how to convert the vkExtensions to createInfo.ppEnabledExtensionNames?
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		// Last two attributes are for validation layers
		createInfo.enabledLayerCount = 0;

		// Create the Vulkan instance
		spdlog::debug("Creating Vulkan instance...");
		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		// Check if instance was created successfully
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to create Vulkan instance!");
		}
	}

	// TODO: As a challenge, try to create a function that checks if all of the extensions returned by glfwGetRequiredInstanceExtensions are included in the supported extensions list.
	void checkVkExtensions() {
	}

    void initVulkan() {
		createInstance();
    }

    void mainLoop() {
		spdlog::debug("Polling for GLFW events...");
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
    }

    void cleanup() {
		spdlog::debug("Destroying Vulkan instance...");
		// Can destroy with an optional allocator (nullptr, for now)
		vkDestroyInstance(instance, nullptr);
		spdlog::debug("Destroying GLFW window...");
		glfwDestroyWindow(window);
		spdlog::debug("Terminating GLFW...");
		glfwTerminate();
    }
};

int main() {
#ifdef DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
