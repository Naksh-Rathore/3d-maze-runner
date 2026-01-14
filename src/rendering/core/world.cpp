#include "rendering/core/world.h"
#include "rendering/core/renderer.h"
#include "game_objects/fly_cam.h"
#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

namespace Rendering {
    World::World()
        : m_camera(glm::vec3(0.0f, 80.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.25f)
        , m_planeMesh(std::vector<GLfloat>{-0.5f, -0.5f, 0.f, 0.f, 0.f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 0.5f, 0.5f, 0.f, 1.f, 1.f, -0.5f, 0.5f, 0.f, 0.f, 1.f },
                      std::vector<GLuint>{ 0, 1, 2, 2, 3, 0 },
                    5)
        , m_planeMaterial("assets/plane/plane.vs", "assets/plane/plane.fs", "assets/plane/texture.png")
    {
        m_planeMesh.uploadData();
        m_planeMesh.uploadComponent(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    }

    void World::setRenderQueue(std::vector<RenderCommand>& renderQueue) {
        // Render plane
        glm::mat4 model(1.0f);

        model = glm::scale(model, glm::vec3(50.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        renderQueue.push_back({ &m_planeMesh, &m_planeMaterial, model});
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