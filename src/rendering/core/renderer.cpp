#include <glad/glad.h>
#include <glm/glm.hpp>

#include "rendering/core/renderer.h"
#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

namespace Rendering {
    Renderer::Renderer(const glm::mat4& projection, const glm::mat4& HUDProjection)
        : m_projection(projection) 
        , m_HUDProjection(HUDProjection)
    {}

    void Renderer::renderQueue(const std::vector<RenderCommand>& renderQueue, const glm::mat4& view) {
        for (const RenderCommand& command : renderQueue) {
            command.m_material->use(0);
            
            command.m_material->m_shader.setMat4("model", command.model);
            command.m_material->m_shader.setMat4("view", view);
            command.m_material->m_shader.setMat4("projection", m_projection);

            command.m_material->m_shader.setInt("texture1", 0);

            glBindVertexArray(command.m_mesh->VAO());
            
            if (command.m_mesh->indices().empty())
                glDrawArrays(command.m_mesh->drawMode(), 0, (GLsizei) command.m_mesh->vertices().size() / command.m_mesh->componentAmount());
            else {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, command.m_mesh->EBO());
                glDrawElements(command.m_mesh->drawMode(), (GLsizei) command.m_mesh->indices().size(), GL_UNSIGNED_INT, nullptr);
            }
        }
    }

    void Renderer::renderHUD(HUD& hud) {
        glUseProgram(hud.shader().shaderProgram());

        hud.shader().setMat4("model", hud.modelMatrix());
        hud.shader().setMat4("view", glm::mat4());
        hud.shader().setMat4("projection", m_projection);

        command.m_material->m_shader.setInt("texture1", 0);
        
        glBindVertexArray(hud.mesh().VAO());
    }
}