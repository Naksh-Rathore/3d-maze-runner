#include "game_objects/entities/wall.h"

namespace GameObject {
    Wall::Wall(const glm::vec3& worldPos, const glm::vec3& scale) 
        : m_worldPos(worldPos)
        , m_scale(scale)
    {}

    glm::mat4 Wall::modelMatrix() const {
        return glm::translate(glm::mat4(1.0f), m_worldPos) *
            glm::scale(glm::mat4(1.0f), m_scale);
    }
}