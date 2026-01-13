#pragma once

#include "rendering/core/renderer.h"
#include "game_objects/fly_cam.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace Rendering {
    class World {
        private:
            // Add objects meshes & materials later

            GameObject::FlyCamera m_camera;

        public:
            World();

            void updateCameraKeyboard(GameObject::CameraDirection direction, float deltaTime);
            void updateCameraMouse(double xposIn, double yposIn);
            
            void setRenderQueue(std::vector<RenderCommand>& renderQueue);

            GameObject::FlyCamera& camera() { return m_camera; }
    };
}