cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
set(PROTO_TARGET primal_camera_proto)
set(TARGET primal_camera)
project(primal)

### PACKAGES ###
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(OpenCV REQUIRED)

### EXECUTABLES ###
add_executable(${PROTO_TARGET} primal_camera_proto.cpp)
add_executable(${TARGET} primal_camera.cpp)

### LIBRARIES ###
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
target_link_libraries(${PROTO_TARGET} spdlog)
target_link_libraries(${PROTO_TARGET} ${OpenCV_LIBS})

### INSTALL ###
install(TARGETS ${PROTO_TARGET} ${TARGET}
		LIBRARY DESTINATION /usr/local/lib
		RUNTIME DESTINATION /usr/local/bin
)
