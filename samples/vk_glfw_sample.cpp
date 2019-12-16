#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

int main() {
    std::cout << "Initializing GLFW..." << std::endl;
    glfwInit();

    std::cout << "Initializing GLFW Window..." << std::endl;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    std::cout << "Enumerating Vulkan Extensions..." << std::endl;
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported" << std::endl;

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    std::cout << "Poll for GLFW events..." << std::endl;
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    std::cout << "Destroying GLFW window..." << std::endl;
    glfwDestroyWindow(window);

    std::cout << "Terminating GLFW..." << std::endl;
    glfwTerminate();

    return 0;
}
