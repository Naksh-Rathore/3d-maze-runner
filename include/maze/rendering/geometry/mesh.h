#pragma once

#include <vector>

#include <glad/glad.h>


namespace Rendering {
    class Mesh {
        private:
            std::vector<GLfloat> m_vertices;
            std::vector<GLuint> m_indices;            

            int m_componentAmount;

            GLuint m_VBO;
            GLuint m_VAO;
            GLuint m_EBO; // Optional

            GLenum m_drawMode;

            bool m_hasUploadedData = false;

        public:
            Mesh(const Mesh&) = delete;
            Mesh& operator=(const Mesh&) = delete;

            Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices = {}, int componentAmount = 3, GLenum drawMode = GL_TRIANGLES);
            ~Mesh();

            void uploadData();
            void uploadComponent(int index, int size, int stride, void *offset);

            const std::vector<GLfloat> vertices() { return m_vertices; }
            const std::vector<GLuint> indices() { return m_indices; }

            int componentAmount() { return m_componentAmount; }

            GLuint VBO() { return m_VBO; }
            GLuint EBO() { return m_EBO; }
            GLuint VAO() { return m_VAO; }

            GLenum drawMode() { return m_drawMode; }
    };
}