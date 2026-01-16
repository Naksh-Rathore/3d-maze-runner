#pragma once

#include "game_objects/entities/wall.h"

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <optional>

namespace Level {
    class LevelLoader {
        private:
            static std::optional<GameObject::Wall> getWallFromSymbol(char symbol, const glm::vec3& pos, const glm::vec3& scale);

        public:
            static void loadLevel(const std::string& levelFilePath, std::vector<GameObject::Wall>& walls);
    };
}   