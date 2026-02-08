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
    , m_renderer(glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f), glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f))
    , m_isRunning(true)
{
    assert(m_window != nullptr);
}

Game::~Game() {

    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

void Game::processInput() {
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::FORWARD, m_deltaTime, true);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::BACKWARD, m_deltaTime, true);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::LEFT, m_deltaTime, true);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_world.updateCameraKeyboard(GameObject::RIGHT, m_deltaTime, true);
}

void Game::mainLoop() {
    while (!glfwWindowShouldClose(m_window) && m_isRunning) {
        float currentTime = (float) glfwGetTime();
        m_deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput();

        m_renderQueue.clear();

        m_world.tick(m_renderQueue);
        m_renderer.renderQueue(m_renderQueue, m_world.playerCamera().viewMatrix());

        glDisable(GL_DEPTH_TEST);
        m_renderer.renderHUD(m_world.chestCollectionHUD());
        m_renderer.renderHUD(m_world.timerBorderHUD());
        m_renderer.renderHUD(m_world.timerBodyHUD());
        glEnable(GL_DEPTH_TEST);

        winLossCheck();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Game::run() {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(m_window, this);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* w, double x, double y){
        Game* game = static_cast<Game*>(glfwGetWindowUserPointer(w));
        game->m_world.updateCameraMouse(x, y);
    });

    glEnable(GL_DEPTH_TEST);

    mainLoop();
}

void Game::winLossCheck() {
    if (GameObject::Chest::chestsCollected() >= 3 && m_world.timer().ratio > 0.0f) {
        std::cout << "You win!" << "\n";
        m_isRunning = false;
    }

    else if (GameObject::Chest::chestsCollected() < 3 && m_world.timer().ratio <= 0.0f ){
        std::cout << "You lose!" << "\n";
        m_isRunning = false;
    }
}
