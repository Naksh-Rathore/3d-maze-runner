#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rendering {

    class Shader {
        private:
            std::string m_shaderSourceContent{};
            GLenum m_shaderType{};
            GLuint m_shader{};

            bool m_hasCompiled = false;

            std::string readShader(const std::string& shaderSourceFile);

        public:
            Shader(const std::string& shaderSourceFile, GLenum shaderType);

            void compileShader();

            GLenum shaderType() const { return m_shaderType; }
            GLuint shader() const { return m_shader; }
            std::string shaderSource() const { return m_shaderSourceContent; }

    };
    
};
