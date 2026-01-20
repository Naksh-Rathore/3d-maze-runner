#include "game_objects/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GameObject {
    FreeCamera::FreeCamera(const glm::vec3& pos, const glm::vec3& front, const glm::vec3& up, float yaw, float pitch, float camSpeed, float mouseSensi)
    : m_pos { pos }
    , m_front { front }
    , m_worldUp { up }
    , m_camSpeed { camSpeed }
    , m_mouseSensi { mouseSensi }
    , m_zoom { 45.0f }
    , m_yaw { yaw }          
    , m_pitch { pitch }  
    {
        updateCameraVectors();
    }

    glm::mat4 FreeCamera::viewMatrix() {
        return glm::lookAt(m_pos, m_pos + m_front, m_up);
    }

    void FreeCamera::processKeyboardInput(CameraDirection direction, float deltaTime) {
        float camSpeed { m_camSpeed * deltaTime };

        if (direction == FORWARD)
            m_pos += m_front * camSpeed;
        if (direction == BACKWARD)
            m_pos -= m_front * camSpeed;
        if (direction == RIGHT)  
            m_pos += m_right * camSpeed;
        if (direction == LEFT)
            m_pos -= m_right * camSpeed;
    }

    void FreeCamera::processMouseInput(float xOffset, float yOffset, bool stopRoll) {
        xOffset *= m_mouseSensi;
        yOffset *= m_mouseSensi;

        m_yaw += xOffset;
        m_pitch += yOffset;

        if (stopRoll) {
            if (m_pitch > 89.0f)
                m_pitch = 89.0f;
            if (m_pitch < -89.0f)
                m_pitch = -89.0f;
        }   

        updateCameraVectors();
    }

    void FreeCamera::processScrollInput(float yOffset) {
        m_zoom -= (float) yOffset;

        if (m_zoom < 1.0f)
            m_zoom = 1.0f;
        if (m_zoom > 45.0f)
            m_zoom = 45.0f;
    }

    void FreeCamera::updateCameraVectors() {
        m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front.y = sin(glm::radians(m_pitch));
        m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        
        m_front = glm::normalize(m_front);

        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }

    WalkCamera::WalkCamera(float groundPos)
        : FreeCamera(glm::vec3(0.0f, groundPos, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 15.0f, 0.125f)
        , m_groundPos(groundPos)
    {}

    void WalkCamera::processKeyboardInput(CameraDirection direction, float deltaTime) {
        float camSpeed { this->camSpeed() * deltaTime };

        if (direction == FORWARD)
            setPos(pos() + front() * camSpeed);
        if (direction == BACKWARD)
            setPos(pos() - front() * camSpeed);
        if (direction == RIGHT)  
            setPos(pos() + right() * camSpeed);
        if (direction == LEFT)
            setPos(pos() - right() * camSpeed);

        glm::vec3 currentPos = pos();
        currentPos.y = m_groundPos;

        setPos(currentPos);
    }

}
