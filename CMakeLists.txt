cmake_minimum_required(VERSION 3.24)
project(3d-maze-runner)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GLFW options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Vendor//glfw)

# Compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

# Include directories
include_directories(
    include/
    Vendor//glad/include/
    Vendor//glfw/include/
    Vendor//glm/
    Vendor//stb/
)

# Vendor/ sources
file(GLOB Vendor/S_SOURCES Vendor//glad/src/glad.c)

# Recursively get all headers and source files
file(GLOB_RECURSE PROJECT_HEADERS include/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

# Recursively get all assets: shaders (.vs/.fs) and images (.png/.jpg)
file(GLOB_RECURSE PROJECT_ASSETS
    assets/*.vs
    assets/*.VS
    assets/*.fs
    assets/*.FS
    assets/*.png
    assets/*.PNG
    assets/*.jpg
    assets/*.JPG
)

# Project configs
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                          .gitattributes
                          .gitignore
                          .gitmodules)

# Organize in IDE
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendor/s" FILES ${Vendor/S_SOURCES})
source_group("Assets" FILES ${PROJECT_ASSETS})

# Definitions
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

# Executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_ASSETS} ${PROJECT_CONFIGS}
                               ${Vendor/S_SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Copy assets folder after build
if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        DEPENDS ${PROJECT_ASSETS}
    )
endif()
