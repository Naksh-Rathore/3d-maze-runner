#include <glm/glm.hpp>

namespace Collision {
    bool pointCube(const glm::vec3& point, const glm::vec3& cubeCenter, float length);
    glm::vec3 slideOnCube(const glm::vec3& currentPos, const glm::vec3& proposedPos, const glm::vec3& cubeCenter, float length);
}