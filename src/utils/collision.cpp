#include "utils/collision.h"

namespace Collision {
    bool pointCube(const glm::vec3& point, const glm::vec3& cubeCenter, float length) {
        float half = length * 0.5f;

        glm::vec3 min = cubeCenter - glm::vec3(half);
        glm::vec3 max = cubeCenter + glm::vec3(half);

        return (point.x >= min.x && point.x <= max.x) &&
            (point.y >= min.y && point.y <= max.y) &&
            (point.z >= min.z && point.z <= max.z);
    }
}