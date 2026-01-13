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

    void World::updateCamera(float dt, GameObject::CameraDirection direction, float mouseDX, float mouseDY, float scrollY) {
        m_camera.processKeyboardInput(direction, dt);
        m_camera.processMouseInput(mouseDX, mouseDY, true);
        m_camera.processScrollInput(scrollY);
    }
}