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
// Use for Resource Management, automatic allocation/deallocation of memory objects, by overloading std::shared_ptr and RAII principles
// Source: https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Base_code
// Source: https://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization
//#include <memory>

// Debug
#define DEBUG

class HelloTriangleApplication {
public:
    void run() {
	initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow() {
	spdlog::debug("Initializing GLFW...");
	glfwInit();
    }

    void initVulkan() {

    }

    void mainLoop() {

    }

    void cleanup() {

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
