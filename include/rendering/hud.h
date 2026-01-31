#pragma once

#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

#include <vector>
#include <string>

namespace Rendering {
    class HUD {
        private:
            Mesh m_mesh;

            Shader m_vert;
            Shader m_frag;

            ShaderProgram m_shader;

            std::vector<Texture2D> m_textures;

            void populateTextures(const std::string& assetsDirectoryPath, int numOfTextures);

        public:
            HUD(const std::string& assetsDirectoryPath, int numOfTextures);
    };
}   