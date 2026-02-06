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
            glm::vec3 m_scale;

            void populateTextures(const std::string& assetsDirectoryPath, int numOfTextures);

        public:
            HUD(const std::string& assetsDirectoryPath, int numOfTextures, const glm::vec3& pos, const glm::vec3& scale = glm::vec3(1.0f));

            glm::mat4 modelMatrix() const;

            Mesh& mesh() { return m_mesh; }
            ShaderProgram& shader() { return m_shader; }    
            std::vector<Texture2D>& textures() { return m_textures; }

            int activeTextureIndex() { return m_activeTextureIndex; }
            void setActiveTextureIndex(int a) { m_activeTextureIndex = a; }

            glm::vec3 scale() { return m_scale; }
            void setScale(const glm::vec3& s) { m_scale = s; }

            glm::vec3 pos() { return m_pos; }
            void setPos(const glm::vec3& p) { m_pos = p; }
    };
}   