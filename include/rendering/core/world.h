#pragma once

#include "rendering/core/renderer.h"
#include "game_objects/camera.h"
#include "game_objects/entities/wall.h"
#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"
#include "game_objects/entities/chest.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

namespace Rendering {
    class World {
        private:
                
            std::vector<GameObject::Wall> m_walls;
            std::vector<GameObject::Chest> m_chests;

            Rendering::Mesh m_planeMesh;
            Rendering::Material m_planeMaterial;
            glm::mat4 m_planeModel;

            Rendering::Mesh m_wallMesh;
            Rendering::Material m_wallMaterial;

            Rendering::Mesh m_chestMesh;
            Rendering::Material m_chestMaterial;

            GameObject::WalkCamera m_playerCamera;

            void populateRenderQueue(std::vector<RenderCommand>& renderQueue);
            void updateEntities();

        public:
            World();

            void updateCameraKeyboard(GameObject::CameraDirection direction, float deltaTime, bool shouldBob = false);
            void updateCameraMouse(double xposIn, double yposIn);
            
            void tick(std::vector<RenderCommand>& renderQueue);

            GameObject::WalkCamera& playerCamera() { return m_playerCamera; }
    };
}