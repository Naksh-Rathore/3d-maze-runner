#include "game.h"
#include "init/init_gl.h"

#include "rendering/core/renderer.h"
#include "rendering/core/world.h"

#include <cassert>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

Game::Game() 
    : m_window(Init::initOpenGL())
    , m_renderer(glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f))
{
    assert(m_window != nullptr);
}

Game::~Game() {
    glfwTerminate();
}

void Game::processInput() {
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::FORWARD, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::BACKWARD, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::LEFT, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::RIGHT, m_deltaTime);
}

void Game::mainLoop() {
    while (!glfwWindowShouldClose(m_window)) {
        float currentTime = glfwGetTime();
        m_deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput();

        m_renderQueue.clear();

        m_world.setRenderQueue(m_renderQueue);
        m_renderer.renderQueue(m_renderQueue, m_world.camera().viewMatrix());

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Game::run() {
    // To Do: Set up every member 

    glEnable(GL_DEPTH_TEST);

    mainLoop();
}