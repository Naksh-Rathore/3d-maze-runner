#ifndef INIT_GL_H
#define INIT_GL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

namespace Init {
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    GLFWwindow* initOpenGL();
};

#endif
