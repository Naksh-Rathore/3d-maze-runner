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

    glm::vec3 slideOnCube(const glm::vec3& currentPos, const glm::vec3& proposedPos, const glm::vec3& cubeCenter, float length) {
        glm::vec3 result = currentPos;
        glm::vec3 test = result;

        test.x = proposedPos.x;
        if (!pointCube(test, cubeCenter, length)) {
            result.x = test.x;
        }

        test = result;
        test.y = proposedPos.y;
        if (!pointCube(test, cubeCenter, length)) {
            result.y = test.y;
        }

        test = result;
        test.z = proposedPos.z;
        
        if (!pointCube(test, cubeCenter, length)) {
            result.z = test.z;
        }

        return result;
    }
}