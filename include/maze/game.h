#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game {
    private:
        GLFWwindow *m_window;
        
        void mainLoop();
        void processInput();

    public:
        Game();
        ~Game();

        void run();
        
        GLFWwindow *window() { return m_window; }
};  