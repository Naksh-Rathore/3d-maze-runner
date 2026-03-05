#include "init/init_gl.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Init {
    void framebuffer_size_callback(GLFWwindow *window, [[maybe_unused]] int width, [[maybe_unused]] int height) {
        int frameBufferWidth, frameBufferHeight;

        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
        glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    }

    GLFWwindow* initOpenGL() {
        if (!glfwInit()) {
            std::cerr << "GLFW failed to initialize!\n";
            return nullptr;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window { glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphing Calculator", nullptr, nullptr) };

        if (window == nullptr) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            
            glfwTerminate();
            return nullptr;
        }

        int frameBufferWidth, frameBufferHeight;

        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
        glViewport(0, 0, frameBufferWidth, frameBufferHeight);
        
        return window;
    }
}
