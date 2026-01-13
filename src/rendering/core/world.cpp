#include "rendering/core/world.h"
#include "rendering/core/renderer.h"
#include "game_objects/fly_cam.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

namespace Rendering {
    World::World()
        : m_camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.25f)
        // Add meshes and materials later
    {
    }

    void World::setRenderQueue(std::vector<RenderCommand>& renderQueue) {
        // Add functionally later when there are game entities
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
    }
}