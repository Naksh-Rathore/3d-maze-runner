#pragma once

#include "rendering/material/shader.h"
#include "rendering/material/shader_program.h"
#include "rendering/material/texture.h"

struct Material {
    Rendering::Shader m_vert;
    Rendering::Shader m_frag;

    Rendering::ShaderProgram m_shader;

    Rendering::Texture2D m_texture;

    Material(const std::string& vertShaderPath, const std::string& fragShaderPath, const std::string& texturePath);
};