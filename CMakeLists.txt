cmake_minimum_required(VERSION 3.24)
project(3d_maze_runner VERSION 0.1 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable vcpkg toolchain
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please define CMAKE_TOOLCHAIN_FILE pointing to vcpkg toolchain file")
endif()

# Add source files
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    src/**/*.cpp
)

file(GLOB_RECURSE HEADER_FILES
    include/*.h
    include/**/*.h
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Find packages installed by vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-linux/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad::glad glm::glm)

# Preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

# Optional: Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

