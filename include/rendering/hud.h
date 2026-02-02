#pragma once

#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

#include <glm/glm.hpp>

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
            int m_activeTextureIndex;

            glm::vec3 m_pos;

            void populateTextures(const std::string& assetsDirectoryPath, int numOfTextures);

        public:
            HUD(const std::string& assetsDirectoryPath, int numOfTextures, const glm::vec3& pos);

            glm::mat4 modelMatrix();

            Mesh& mesh() { return m_mesh; }
            ShaderProgram& shader() { return m_shader; }    
            glm::vec3& pos() { return m_pos; }
            std::vector<Texture2D>& textures() { return m_textures; }

            int activeTextureIndex() { return m_activeTextureIndex; }
            void setActiveTextureIndex(int a) { m_activeTextureIndex = a; }
    };
}   