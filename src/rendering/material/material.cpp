#include "rendering/material/material.h"

Material::Material(const std::string& vertShaderPath, const std::string& fragShaderPath, const std::string& texturePath) 
    : m_vert(vertShaderPath, GL_VERTEX_SHADER)
    , m_frag(fragShaderPath, GL_FRAGMENT_SHADER)
{
    m_shader.link(m_vert, m_frag);
    m_texture.link(texturePath, GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
}

void Material::use(GLuint unit) {
    m_texture.use(unit);
    m_shader.use();
}