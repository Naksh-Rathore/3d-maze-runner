#pragma once

#include <glad/glad.h>
#include <string>

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


    class Texture2D {
        private:
            GLuint m_texture{};
        
            bool m_hasLinked = false;

        public:
            void link(const std::string& fileName, GLenum wrapOption, GLenum mipMapMinOption, GLenum mipMapMagOption);

            ~Texture2D();

            GLuint texture() { return m_texture; }
    };

    struct Material {
        Rendering::Shader m_vert;
        Rendering::Shader m_frag;

        Rendering::ShaderProgram m_shader;

        Rendering::Texture2D m_texture;

        Material(const std::string& vertShaderPath, const std::string& fragShaderPath, const std::string& texturePath);
    };

}
