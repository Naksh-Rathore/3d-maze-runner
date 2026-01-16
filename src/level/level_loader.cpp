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

        glm::vec3 currentPos(-20.0f, 5.0f, -20.0f);
        glm::vec3 scale(glm::vec3(5.0f, 10.0f, 10.0f));
    
        for (char symbol : levelFileContent) {
            if (symbol == '\n') {
                currentPos.x = -20.0f;
                currentPos.z += 7.5f;
                continue;
            }

            if (symbol == '\r')
                continue;

            std::optional<GameObject::Wall> wall = getWallFromSymbol(symbol, currentPos, scale);

            if (wall.has_value())
                walls.push_back(wall.value());

            currentPos.x += 10.0f;
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