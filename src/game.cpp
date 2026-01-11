#include "game.h"
#include "init/init_gl.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Game::Game() 
    : m_window(Init::initOpenGL())
{
    assert(m_window != nullptr);
}

Game::~Game() {
    glfwTerminate();
}

void Game::processInput() {
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}

void Game::mainLoop() {
    while (!glfwWindowShouldClose(m_window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Game::run() {
    // To Do: Set up every member 

    mainLoop();
}