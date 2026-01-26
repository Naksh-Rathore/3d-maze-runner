#include "rendering/geometry/mesh.h"

#include <vector>
#include <cassert>

#include <glad/glad.h>

namespace Rendering {
    Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, int componentAmount, GLenum drawMode)
        : m_vertices(vertices)
        , m_indices(indices)
        , m_componentAmount(componentAmount)
        , m_drawMode(drawMode)
    {
    }

    Mesh::~Mesh() {
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
        if (m_EBO) glDeleteBuffers(1, &m_EBO);
    }

    void Mesh::uploadData() {
        assert(!m_hasUploadedData && "ERROR: Cannot upload mesh data twice!");
        m_hasUploadedData = true;

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
    
        if (!m_indices.empty()) {
            glGenBuffers(1, &m_EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);
        }        

        uploadComponent(0, 3, m_componentAmount * sizeof(GLfloat), (void *) 0);
    }

    void Mesh::uploadComponent(int index, int size, int stride, void *offset) {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);
    }
}