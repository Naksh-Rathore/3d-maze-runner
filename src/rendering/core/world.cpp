#include "rendering/core/world.h"
#include "rendering/core/renderer.h"
#include "game_objects/fly_cam.h"
#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"
#include "utils/common_vertices.h"
#include "level/level_loader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

namespace Rendering {
    World::World()
        : m_camera(glm::vec3(0.0f, 80.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.25f)

        , m_planeMesh(CommonVertices::SquareVertices,
                      CommonVertices::SquareIndices,
                    5)
        , m_planeMaterial("assets/plane/plane.vs", "assets/plane/plane.fs", "assets/plane/texture.png")
        , m_planeModel(glm::scale(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(50.0f)))

        , m_wallMesh(CommonVertices::CubeVertices, CommonVertices::CubeIndices, 5)
        , m_wallMaterial("assets/wall/wall.vs", "assets/wall/wall.fs", "assets/wall/texture.jpg")
    {
        m_planeMesh.uploadData();
        m_planeMesh.uploadComponent(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    
        m_wallMesh.uploadData();
        m_wallMesh.uploadComponent(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

        Level::LevelLoader::loadLevel("assets/levels/level1.txt", m_walls);
    }

    void World::setRenderQueue(std::vector<RenderCommand>& renderQueue) {
        // Render plane
        renderQueue.push_back({ &m_planeMesh, &m_planeMaterial, m_planeModel});

        for (GameObject::Wall wall : m_walls) 
            renderQueue.push_back({ &m_wallMesh, &m_wallMaterial, wall.modelMatrix() });
        
    }

    void World::updateCameraKeyboard(GameObject::CameraDirection direction, float deltaTime) {
        m_camera.processKeyboardInput(direction, deltaTime);
    }

    void World::updateCameraMouse(double xposIn, double yposIn) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (m_camera.firstMouse()) {
            m_camera.setLastX(xpos);
            m_camera.setLastY(ypos);
            
            m_camera.setFirstMouse(false);
            return;
        }

        float xoffset = xpos - m_camera.lastX();
        float yoffset = m_camera.lastY() - ypos; // reversed since y-coordinates go from bottom to top

        m_camera.setLastX(xpos);
        m_camera.setLastY(ypos);

        m_camera.processMouseInput(xoffset, yoffset);
    }
}