cmake_minimum_required(VERSION 3.14)
project(RayUI)

if (UNIX)
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Build GLFW Wayland support")
    set(GLFW_BUILD_X11 ON CACHE BOOL "Build GLFW X11 support")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# RayUI
add_subdirectory(${CMAKE_SOURCE_DIR}/.. ${CMAKE_SOURCE_DIR}/../build)

# AllWidgets
add_executable(AllWidgets AllWidgets.cpp)
target_compile_options(AllWidgets PRIVATE -Wall -Wextra)
set_target_properties(AllWidgets PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(AllWidgets PRIVATE raylib RayUI)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(AllWidgets PRIVATE "-framework IOKit -framework Cocoa -framework OpenGL")
endif()
