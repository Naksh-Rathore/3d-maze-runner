#include "game_objects/timer.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace GameObject {
    Timer::Timer(float r, float d)
        : ratio(r)
        , duration(d)
    {}

    void Timer::tick() {
        ratio = 1 - glm::clamp((float) (glfwGetTime() / duration), 0.0f, 1.0f);
    }
}
