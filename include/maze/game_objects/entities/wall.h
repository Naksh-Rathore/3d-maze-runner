#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GameObject {


    class Wall {
        private:
            glm::vec3 m_worldPos;
            glm::vec3 m_scale;

        public:
            Wall(const glm::vec3& worldPos, const glm::vec3& scale);

            glm::mat4 modelMatrix() const;

            const glm::vec3& worldPos() { return m_worldPos; }
            const glm::vec3& scale() { return m_scale; }

            // Setters aren't needed **yet** since there is really no dynamic position changes or scale changes
    };
}