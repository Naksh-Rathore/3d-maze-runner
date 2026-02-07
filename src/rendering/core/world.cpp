#include "rendering/core/world.h"
#include "rendering/core/renderer.h"

#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

#include "game_objects/camera.h"
#include "game_objects/entities/chest.h"

#include "level/level_loader.h"

#include "utils/collision.h"
#include "utils/common_vertices.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

#include <GLFW/glfw3.h>
#include <iostream>

namespace Rendering {
    World::World()
        : m_playerCamera(5.0f)

        , m_planeMesh(CommonVertices::SquareVertices, CommonVertices::SquareIndices, 5)
        , m_planeMaterial("assets/plane/vertex.vs", "assets/plane/fragment.fs", "assets/plane/texture.png")
        , m_planeModel(glm::scale(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(50.0f)))

        , m_wallMesh(CommonVertices::CubeVertices, CommonVertices::CubeIndices, 5)
        , m_wallMaterial("assets/wall/vertex.vs", "assets/wall/fragment.fs", "assets/wall/texture.png")

        , m_chestMesh(CommonVertices::CubeVertices, CommonVertices::CubeIndices, 5)
        , m_chestMaterial("assets/chest/vertex.vs", "assets/chest/fragment.fs", "assets/chest/texture.png")

        , m_chestCollectionHUD("assets/chest_collection_hud", 4, glm::vec3(175.0f, 750.0f, 0.0f), glm::vec3(500.0f, 275.0f, 1.0f))
        , m_timerBorderHUD("assets/timer_border_hud", 1, glm::vec3(650.0f, 725.0f, 0.0f), glm::vec3(350.0f, 150.0f, 1.0f))
        , m_timerBodyHUD("assets/timer_body_hud", 1, glm::vec3(650.0f, 721.0f, 0.0f), glm::vec3(270.0f, 108.0f, 1.0f))

        , m_timer(0.0f, 60.0f)
    {
        m_planeMesh.uploadData();
        m_planeMesh.uploadComponent(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    
        m_wallMesh.uploadData();
        m_wallMesh.uploadComponent(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

        m_chestMesh.uploadData();
        m_chestMesh.uploadComponent(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

        Level::LevelLoader::loadLevel("assets/levels/level1.txt", m_walls, m_chests);
    }

    void World::populateRenderQueue(std::vector<RenderCommand>& renderQueue) {
        renderQueue.push_back({ &m_planeMesh, &m_planeMaterial, m_planeModel});

        for (GameObject::Wall& wall : m_walls) 
            renderQueue.push_back({ &m_wallMesh, &m_wallMaterial, wall.modelMatrix() });

        for (const GameObject::Chest& chest : m_chests) {
            if (chest.isCollected())
                continue;

            renderQueue.push_back({ &m_chestMesh, &m_chestMaterial, chest.modelMatrix() });
        }
    }

    void World::updateCameraKeyboard(GameObject::CameraDirection direction, float deltaTime, bool shouldBob) {
        glm::vec3 proposedPosition = m_playerCamera.proposedPosition(direction, deltaTime, shouldBob);

        const float wallWidthBuffer = 1.0f;

        for (const GameObject::Wall& wall : m_walls) {
            float cubeLength = wall.width() + wallWidthBuffer;
            proposedPosition = Collision::slideOnCube(m_playerCamera.pos(), proposedPosition, wall.worldPos(), cubeLength);
        }

        m_playerCamera.setPos(proposedPosition);
    }

    void World::updateCameraMouse(double xposIn, double yposIn) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (m_playerCamera.firstMouse()) {
            m_playerCamera.setLastX(xpos);
            m_playerCamera.setLastY(ypos);
            
            m_playerCamera.setFirstMouse(false);
            return;
        }

        float xoffset = xpos - m_playerCamera.lastX();
        float yoffset = m_playerCamera.lastY() - ypos; // reversed since y-coordinates go from bottom to top

        m_playerCamera.setLastX(xpos);
        m_playerCamera.setLastY(ypos);

        m_playerCamera.processMouseInput(xoffset, yoffset);
    }

    void World::updateHUDs() {
        int activeTextureIndex = GameObject::Chest::chestsCollected();
        m_chestCollectionHUD.setActiveTextureIndex(activeTextureIndex);

        m_timer.tick();
        m_timerBodyHUD.editCustomFloatUniform("timerRatio", m_timer.ratio);
    }

    void World::updateEntities() {
        for (GameObject::Chest& chest : m_chests)
            chest.update(m_playerCamera.pos());
    }

    void World::tick(std::vector<RenderCommand>& renderQueue) {
        updateEntities();
        updateHUDs();

        populateRenderQueue(renderQueue);
    }
}