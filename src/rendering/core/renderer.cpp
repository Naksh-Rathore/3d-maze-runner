#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/core/renderer.h"
#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

namespace Rendering {
    Renderer::Renderer(const glm::mat4& projection, const glm::mat4& HUDProjection) 
        : m_projection(projection) 
        , m_HUDProjection(HUDProjection)
    {}

    void Renderer::renderQueue(const std::vector<RenderCommand>& renderQueue, const glm::mat4& view, const glm::vec3& cameraPos, const glm::vec3& cameraFront) {
        for (const RenderCommand& command : renderQueue) {
            command.m_material->use(0);
            
            command.m_material->m_shader.setMat4("model", command.model);
            command.m_material->m_shader.setMat4("view", view);
            command.m_material->m_shader.setMat4("projection", m_projection);

            command.m_material->m_shader.setInt("texture1", 0);

            if (command.isConeLit) {
                command.m_material->m_shader.setVec3("light.position", cameraPos);
                command.m_material->m_shader.setVec3("light.direction", glm::normalize(cameraFront));
                command.m_material->m_shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
                command.m_material->m_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
                command.m_material->m_shader.setVec3("viewPos", cameraPos);

                // light properties
                command.m_material->m_shader.setVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
                // we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
                // each environment and lighting type requires some tweaking to get the best out of your environment.
                command.m_material->m_shader.setVec3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
                command.m_material->m_shader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
                command.m_material->m_shader.setFloat("light.constant", 1.0f);
                command.m_material->m_shader.setFloat("light.linear", 0.09f);
                command.m_material->m_shader.setFloat("light.quadratic", 0.032f);

                // material properties
                command.m_material->m_shader.setFloat("material.shininess", 32.0f);
                command.m_material->m_shader.setInt("material.diffuse", 0);
            }

            glBindVertexArray(command.m_mesh->VAO());
            
            if (command.m_mesh->indices().empty())
                glDrawArrays(command.m_mesh->drawMode(), 0, (GLsizei) command.m_mesh->vertices().size() / command.m_mesh->componentAmount());
            else {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, command.m_mesh->EBO());
                glDrawElements(command.m_mesh->drawMode(), (GLsizei) command.m_mesh->indices().size(), GL_UNSIGNED_INT, nullptr);
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            glUseProgram(0);
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    void Renderer::renderHUD(HUD& hud) {
        glUseProgram(hud.shader().shaderProgram());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, hud.textures().at(hud.activeTextureIndex()).texture());

        hud.shader().setMat4("model", hud.modelMatrix());
        hud.shader().setMat4("view", glm::mat4(1.0f));
        hud.shader().setMat4("projection", m_HUDProjection);

        hud.shader().setInt("texture1", 0);

        for (const auto& [name, value] : hud.customFloatUniforms())
            hud.shader().setFloat(name.c_str(), value);

        glBindVertexArray(hud.mesh().VAO());
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hud.mesh().EBO());
        glDrawElements(hud.mesh().drawMode(), (GLsizei) hud.mesh().indices().size(), GL_UNSIGNED_INT, nullptr);

        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}