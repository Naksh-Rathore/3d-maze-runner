#pragma once

#include "rendering/core/renderer.h"
#include "game_objects/fly_cam.h"

#include <glad/glad.h>

#include <vector>

namespace Rendering {
    class World {
        private:
            // Add objects meshes & materials later

            GameObject::FlyCamera m_camera;

        public:
            World();
            
            void updateCamera(float dt, GameObject::CameraDirection direction, float mouseDX, float mouseDY, float scrollY);
            void setRenderQueue(std::vector<RenderCommand>& renderQueue);
    };
}