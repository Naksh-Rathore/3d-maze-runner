#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GameObject {
    
    enum CameraDirection {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };  

    class FreeCamera {
    private:
        glm::vec3 m_pos{};
        glm::vec3 m_front{};
        glm::vec3 m_up{};
        glm::vec3 m_direction{};
        glm::vec3 m_right{};
        glm::vec3 m_worldUp{};

        float m_yaw{};
        float m_pitch{};

        float m_camSpeed{};
        float m_mouseSensi{};
        float m_zoom{};

        float m_lastX;
        float m_lastY;

        bool m_firstMouse = true;

        void updateCameraVectors();

    public:
        FreeCamera(const glm::vec3& pos, const glm::vec3& front, const glm::vec3& up, float yaw, float pitch, float camSpeed, float mouseSensi);

        glm::mat4 viewMatrix();

        void processKeyboardInput(CameraDirection direction, float deltaTime);
        void processMouseInput(float xOffset, float yOffset, bool stopRoll = true);
        void processScrollInput(float yOffset);

        const glm::vec3& pos() const { return m_pos; }
        void pos(const glm::vec3& val) { m_pos = val; }

        const glm::vec3& front() const { return m_front; }
        void front(const glm::vec3& val) { m_front = val; }

        const glm::vec3& up() const { return m_up; }
        void up(const glm::vec3& val) { m_up = val; }

        const glm::vec3& direction() const { return m_direction; }
        void direction(const glm::vec3& val) { m_direction = val; }

        const glm::vec3& right() const { return m_right; }
        void right(const glm::vec3& val) { m_right = val; }

        const glm::vec3& worldUp() const { return m_worldUp; }
        void worldUp(const glm::vec3& val) { m_worldUp = val; }

        float yaw() const { return m_yaw; }
        void yaw(float val) { m_yaw = val; }

        float pitch() const { return m_pitch; }
        void pitch(float val) { m_pitch = val; }

        float camSpeed() const { return m_camSpeed; }
        void camSpeed(float val) { m_camSpeed = val; }

        float mouseSensi() const { return m_mouseSensi; }
        void mouseSensi(float val) { m_mouseSensi = val; }

        float zoom() const { return m_zoom; }
        void zoom(float val) { m_zoom = val; }      

        float lastX() { return m_lastX; }
        float lastY() { return m_lastY; }

        void setLastX(float x) { m_lastX = x; }
        void setLastY(float y) { m_lastY = y; }

        bool firstMouse() { return m_firstMouse; }
        void setFirstMouse(bool f) { m_firstMouse = f; }
};
    
}
