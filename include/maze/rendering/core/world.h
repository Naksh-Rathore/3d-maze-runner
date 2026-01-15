#pragma once

#include "rendering/core/renderer.h"
#include "game_objects/fly_cam.h"
#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

namespace Rendering {
    class World {
        private:
                        
            Rendering::Mesh m_planeMesh;
            Rendering::Material m_planeMaterial;
            glm::mat4 m_planeModel;

            GameObject::FlyCamera m_camera;

        public:
            World();

            void updateCameraKeyboard(GameObject::CameraDirection direction, float deltaTime);
            void updateCameraMouse(double xposIn, double yposIn);
            
            void setRenderQueue(std::vector<RenderCommand>& renderQueue);

            GameObject::FlyCamera& camera() { return m_camera; }
    };
}