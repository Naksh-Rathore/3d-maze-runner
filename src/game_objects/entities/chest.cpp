#include "game_objects/entities/chest.h"

#include "utils/collision.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

namespace GameObject {
    Chest::Chest(const glm::vec3& worldPos, const glm::vec3& scale)
        : m_worldPos(worldPos)
        , m_scale(scale)
        , m_isCollected(false)
        , m_shouldAnimate(false)
    {}

    glm::mat4 Chest::modelMatrix() const {
        glm::mat4 model(1.0f);

        glm::vec3 pos = m_worldPos;

        float yOffset = std::sin(glfwGetTime()) * 0.50f;
        pos.y += yOffset;

        model = glm::translate(model, pos);
        model = glm::scale(model, m_scale);

        return model;
    }

    void Chest::update(const glm::vec3& playerPos) {
        // Prevents costly collision calls if not needed
        if (m_isCollected)
            return;

        if (bool result = Collision::pointCube(playerPos, m_worldPos, m_scale.x))
            m_isCollected = true;
    }
}