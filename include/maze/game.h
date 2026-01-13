#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendering/core/renderer.h"
#include "rendering/core/world.h"

class Game {
    private:
        GLFWwindow *m_window;
        
        Rendering::Renderer m_renderer;
        Rendering::World m_world;

        std::vector<Rendering::RenderCommand> m_renderQueue;

        float m_deltaTime;
        float m_lastTime;

        float lastX;
        float lastY;

        void mainLoop();
        void processInput();

    public:
        Game();
        ~Game();

        void run();
        
        GLFWwindow *window() { return m_window; }
};  