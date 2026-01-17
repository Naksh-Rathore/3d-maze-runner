#include "level/level_loader.h"
#include "game_objects/entities/wall.h"

#include <glm/glm.hpp>

#include <fstream>
#include <cassert>
#include <optional>

namespace Level {
    void LevelLoader::loadLevel(const std::string& levelFilePath, std::vector<GameObject::Wall>& walls) {
        std::ifstream levelFile(levelFilePath);
        
        std::string levelFileContentBuffer;
        std::string levelFileContent;

        assert(levelFile.is_open() && "ERROR: File could not be opened!");

        while (std::getline(levelFile, levelFileContentBuffer))
            levelFileContent += levelFileContentBuffer + "\n";
    
        const float cell_x = 10.0f;
        const float cell_z = 10.0f;

        const float wall_height = 10.0f;

        const float eps = 0.02f;

        const float wall_scale_x = cell_x - eps;
        const float wall_scale_y = wall_height;
        const float wall_scale_z = cell_z - eps;

        glm::vec3 currentPos(-20.0f, wall_height * 0.5f, -20.0f);

        glm::vec3 scale(
            wall_scale_x,
            wall_scale_y,
            wall_scale_z
        );

        const float startX = currentPos.x;

        for (char symbol : levelFileContent) {
            if (symbol == '\n') {
                currentPos.x = startX;
                currentPos.z += cell_z;
                continue;
            }

            if (symbol == '\r')
                continue;

            if (auto wall = getWallFromSymbol(symbol, currentPos, scale))
                walls.push_back(wall.value());

            currentPos.x += cell_x;
        }
    }

    std::optional<GameObject::Wall> LevelLoader::getWallFromSymbol(char symbol, const glm::vec3& pos, const glm::vec3& scale) {
        switch (symbol) {
            case '.':
                return std::nullopt;

            case '-':
                return GameObject::Wall(pos, scale, true);
            
            case '|':
                return GameObject::Wall(pos, scale, false);
        }
    }
}