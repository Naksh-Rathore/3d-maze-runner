#include "game_objects/entities/chest.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace GameObject {
    Chest::Chest(const glm::vec3& worldPos, const glm::vec3& scale, bool shouldAnimate = true)
        : m_worldPos(worldPos)
        , m_scale(scale)
        , m_isCollected(false)
        , m_shouldAnimate(shouldAnimate)
    {}

    glm::mat4 Chest::modelMatrix() const {
        glm::mat4 model(1.0f);

        glm::vec3 pos = m_worldPos;

        if (m_shouldAnimate) {
            float yOffset = std::sin(glfwGetTime()) * 0.25f;
            pos.y += yOffset;
        }

        model = glm::translate(model, pos);
        model = glm::scale(model, m_scale);
    }
}