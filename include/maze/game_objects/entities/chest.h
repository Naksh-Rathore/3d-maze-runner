#pragma once

#include <glm/glm.hpp>

namespace GameObject {
    class Chest {
        private:
            glm::vec3 m_worldPos;
            glm::vec3 m_scale;

            bool m_isCollected;
            bool m_shouldAnimate;

        public:
            Chest(const glm::vec3& worldPos, const glm::vec3& scale, bool shouldAnimate = true);

            glm::mat4 modelMatrix() const;
            void update(const glm::vec3& playerPos);

            // No setters since unnecessary privilege is bad 
            const glm::vec3& worldPos() const { return m_worldPos; }
            bool isCollected() const { return m_isCollected; }
            bool shouldAnimate() const { return m_shouldAnimate; }
    };
}