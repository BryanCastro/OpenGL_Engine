cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(LearnOpenGL VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "U:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Set the CMAKE_PREFIX_PATH to the vcpkg installed directory
set(CMAKE_PREFIX_PATH "U:/Tools/vcpkg/installed/x64-windows" CACHE STRING "")

# Add the executable
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Find and include GLFW
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Find and include GLAD
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

# Find and include GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

# Find and include Assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Set the output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add additional libraries for Windows
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE gdi32 opengl32)
endif()

# Copy DLLs to the output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "U:/Tools/vcpkg/installed/x64-windows/bin/glfw3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "U:/Tools/vcpkg/installed/x64-windows/debug/bin/glfw3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Copy Assimp DLLs to the output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "U:/Tools/vcpkg/installed/x64-windows/bin/assimp-vc143-mt.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "U:/Tools/vcpkg/installed/x64-windows/debug/bin/assimp-vc143-mtd.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)