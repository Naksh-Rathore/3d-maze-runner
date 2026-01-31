#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

#include "rendering/hud.h"

namespace Rendering {
    struct RenderCommand {
        Mesh* m_mesh;
        Material* m_material;

        glm::mat4 model;
    };

    class Renderer {
        private:
            glm::mat4 m_projection;
            glm::mat4 m_HUDProjection;

        public:
            Renderer(const glm::mat4& projection, const glm::mat4& HUDProjection);
            
            void renderQueue(const std::vector<RenderCommand>& renderQueue, const glm::mat4& view);
            void renderHUD(HUD& hud, int textureIndex = 0);
    };  
}
