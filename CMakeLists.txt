cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(simple_camera)
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
add_executable(simple_camera main.cpp)
target_compile_definitions(simple_camera PRIVATE VK_USE_PLATFORM_XLIB_KHR)
target_include_directories(simple_camera PRIVATE Vulkan::Vulkan)
target_link_libraries(simple_camera Vulkan::Vulkan)
target_link_libraries(simple_camera glfw)