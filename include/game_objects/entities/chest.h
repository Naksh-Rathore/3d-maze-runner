#pragma once

#include <glm/glm.hpp>

namespace GameObject {
    class Chest {
        private:
            glm::vec3 m_worldPos;
            glm::vec3 m_scale;

            bool m_isCollected;

            float m_amplitude;

        public:
            Chest(const glm::vec3& worldPos, const glm::vec3& scale, float amplitude = 0.5f);

            glm::mat4 modelMatrix() const;
            void update(const glm::vec3& playerPos);

            // No setters since unnecessary privilege is bad 
            const glm::vec3& worldPos() const { return m_worldPos; }
            bool isCollected() const { return m_isCollected; }
            float amplitude() { return m_amplitude; }
    };
}