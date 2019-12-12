cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
set(TARGET simple_camera)
project(${TARGET})
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
add_executable(${TARGET} main.cpp)
# XLIB = x11
target_compile_definitions(${TARGET} PRIVATE VK_USE_PLATFORM_XLIB_KHR)
# TODO: Fix the validation layers not matching in instance and layer properties
# Rebuild Vulkan SDK to v1.1.130
#  * Vulkan-Headers
#  * Vulkan-Loader
#  * Vulkan-Tools
target_include_directories(${TARGET} PRIVATE Vulkan::Vulkan)
target_link_libraries(${TARGET} Vulkan::Vulkan)
target_link_libraries(${TARGET} glfw)
target_link_libraries(${TARGET} spdlog)
