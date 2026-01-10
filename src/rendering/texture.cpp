#include "stb_image.h"
#include "rendering/material/texture.h"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rendering {
    void Texture2D::link(const std::string& fileName, GLenum wrapOption, GLenum mipMapMinOption, GLenum mipMapMagOption) {
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        
        unsigned char *data { stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0) };

        if (data == nullptr) {
            std::cerr << "Failed to open texture file: " << fileName << "\n";
            return;
        }

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapOption);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapOption);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipMapMinOption);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mipMapMagOption);
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    void Texture2D::use(GLuint unit) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_texture);
    }
}
