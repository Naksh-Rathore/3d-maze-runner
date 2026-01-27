#include "rendering/material/material.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

namespace Rendering {
    Shader::Shader(const std::string& shaderSourceFile, GLenum shaderType)
        : m_shaderSourceContent { readShader(shaderSourceFile) }
        , m_shaderType { shaderType }
        , m_shader { glCreateShader(m_shaderType) }
    {
    }

    Shader::~Shader() {
        if (m_shader != 0)
            glDeleteShader(m_shader);
    }

    std::string Shader::readShader(const std::string& shaderSourceFile) {
        std::string shaderContents{};
        std::string shaderContentsBuffer{};
    
        std::ifstream shaderFileStream(shaderSourceFile);

        if (!shaderFileStream.is_open()) {
            std::cerr << "Failed to open shader file: " << shaderSourceFile << "\n";
            return "";
        }

        while (std::getline(shaderFileStream, shaderContentsBuffer))
            shaderContents += shaderContentsBuffer + "\n";

        shaderFileStream.close();
        return shaderContents;
    }

    void Shader::compileShader() {
        assert(!m_hasCompiled && "ERROR: Shader cannot be compiled twice!");

        m_hasCompiled = true;

        const char *shaderContent { m_shaderSourceContent.c_str() };

        glShaderSource(m_shader, 1, &shaderContent, nullptr);
        glCompileShader(m_shader);

        int success{};
        char infoLog[1024]{};

        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(m_shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type " << m_shaderType 
                    << "\n" << infoLog 
                    << "\n-- --------------------------------------------------- -- " << std::endl;    
        }
    }
    
    ShaderProgram::ShaderProgram()
        : m_shaderProgram { glCreateProgram() }
    {
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_shaderProgram);
    }

    void ShaderProgram::link(Shader& vertexShader, Shader& fragmentShader) {
        assert(!m_hasLinked && "ERROR: Shader program cannot be linked twice!");

        m_hasLinked = true;

        glAttachShader(m_shaderProgram, vertexShader.shader());
        glAttachShader(m_shaderProgram, fragmentShader.shader());
        glLinkProgram(m_shaderProgram);

        glDetachShader(m_shaderProgram, vertexShader.shader());
        glDetachShader(m_shaderProgram, fragmentShader.shader());
    }

    void Texture2D::link(const std::string& fileName, GLenum wrapOption, GLenum mipMapMinOption, GLenum mipMapMagOption) {
        assert(!m_hasLinked && "ERROR: Texture cannot be linked twice");

        m_hasLinked = true;

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
    
        unsigned char *data { stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0) };

        if (data == nullptr) {
            std::cerr << "Failed to open texture file: " << fileName << "\n";
            return;
        }

        GLenum format = GL_RGB;

        if (nrChannels == 4)
            format = GL_RGBA;

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapOption);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapOption);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipMapMinOption);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mipMapMagOption);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_texture);
    }    
    
    Material::Material(const std::string& vertShaderPath, const std::string& fragShaderPath, const std::string& texturePath) 
    : m_vert(vertShaderPath, GL_VERTEX_SHADER)
    , m_frag(fragShaderPath, GL_FRAGMENT_SHADER)
    {
        m_vert.compileShader();
        m_frag.compileShader();

        m_shader.link(m_vert, m_frag);
        m_texture.link(texturePath, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    }

    void Material::use(GLuint textureUnit) {
        glUseProgram(m_shader.shaderProgram());

        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_texture.texture());
    }

}
