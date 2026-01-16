#include "game_objects/entities/wall.h"

namespace GameObject {
    Wall::Wall(const glm::vec3& worldPos, const glm::vec3& scale, bool isVertical) 
        : m_worldPos(worldPos)
        , m_scale(scale)
        , m_isVertical(isVertical)
    {}

    glm::mat4 Wall::modelMatrix() const {
        glm::mat4 model(1.0f);

        model = glm::translate(model, m_worldPos);

        if (m_isVertical)
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        model = glm::scale(model, m_scale);

        return model;
    }
}