#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendering/material/shader.h"

namespace Rendering {
    class ShaderProgram {
        private:
            GLuint m_shaderProgram{};

            bool m_hasLinked = false;

        public:
            ShaderProgram();
            ~ShaderProgram();

            void link(Shader& vertexShader, Shader& fragmentShader);

            GLuint shaderProgram() const { return m_shaderProgram; }
    };
}
