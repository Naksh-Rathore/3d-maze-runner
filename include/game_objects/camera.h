#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GameObject {
    
    enum CameraDirection {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        NONE
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
        void setPos(const glm::vec3& val) { m_pos = val; }

        const glm::vec3& front() const { return m_front; }
        void setFront(const glm::vec3& val) { m_front = val; }

        const glm::vec3& right() const { return m_right; }
        void setRight(const glm::vec3& val) { m_right = val; }

        float mouseSensi() const { return m_mouseSensi; }
        void setMouseSensi(float val) { m_mouseSensi = val; }

        float camSpeed() const { return m_camSpeed; } 

        float zoom() const { return m_zoom; }
        void zoom(float val) { m_zoom = val; }

        float lastX() const { return m_lastX; }
        float lastY() const { return m_lastY; }

        void setLastX(float x) { m_lastX = x; }
        void setLastY(float y) { m_lastY = y; }

        bool firstMouse() const { return m_firstMouse; } 
        void setFirstMouse(bool f) { m_firstMouse = f; }

    };
    
    class WalkCamera : public FreeCamera {
        private:
            float m_groundPos;
            float m_amplitude;
            float m_frequency;
            float m_bobTheta;

        public:
            WalkCamera(float groundPos = 0.0f, float amplitude = 0.5f, float frequency = 5.0f);

            void processKeyboardInput(CameraDirection direction, float deltaTime, bool shouldBob = false);
            glm::vec3 proposedPosition(CameraDirection direction, float deltaTime, bool shouldBob = false);    
    };
}
