#include "rendering/hud.h"

#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

#include "utils/common_vertices.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

namespace Rendering {
    HUD::HUD(const std::string& assetsDirectoryPath, int numOfTextures)
        : m_mesh(CommonVertices::SquareVertices, CommonVertices::SquareIndices, 5)
        , m_vert(assetsDirectoryPath + "/vertex.vs", GL_VERTEX_SHADER)
        , m_frag(assetsDirectoryPath + "/fragment.fs", GL_FRAGMENT_SHADER)
    {
        m_mesh.uploadData();
        m_mesh.uploadComponent(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

        m_shader.link(m_vert, m_frag);
    }

    void HUD::populateTextures(const std::string& assetsDirectoryPath, int numOfTextures) {
        for (int i = 1; i <= numOfTextures; i++) {
            m_textures.push_back(Texture2D{});
            m_textures.at(i - 1).link(assetsDirectoryPath + "/texture" + std::to_string(i) + ".png", GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        }
    }
}