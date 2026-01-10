#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendering/material/shader.h"

namespace Rendering {
    class ShaderProgram {
        private:
            GLuint m_shaderProgram{};

        public:
            ShaderProgram();
            ~ShaderProgram();

            void link(Shader& vertexShader, Shader& fragmentShader);
            void use();

            GLuint shaderProgram() const { return m_shaderProgram; }
            void setShaderProgram(GLuint val) { m_shaderProgram = val; }

    };
}
