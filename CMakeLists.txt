cmake_minimum_required(VERSION 3.24)
project(3d_maze_runner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

if (WIN32)
    set(GLFW_LIB glfw)
else()
    set(GLFW_LIB glfw3)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW_LIB}
    glad::glad
    glm::glm
)


target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
