#include "game_objects/entities/wall.h"

namespace GameObject {
    Wall::Wall(const glm::vec3& worldPos, const glm::vec3& scale) 
        : m_worldPos(worldPos)
        , m_scale(scale)
    {}

    glm::mat4 Wall::modelMatrix() const {
        glm::mat4 model(1.0f);

        model = glm::translate(model, m_worldPos);
        model = glm::scale(model, m_scale);

        return model;
    }
}