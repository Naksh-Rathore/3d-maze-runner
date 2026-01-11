#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Rendering {
    class Texture2D {
        private:
            GLuint m_texture{};
            
            bool m_hasLinked = false;

        public:
            void link(const std::string& fileName, GLenum wrapOption, GLenum mipMapMinOption, GLenum mipMapMagOption);

            ~Texture2D();

            GLuint texture() { return m_texture; }
    };
}

