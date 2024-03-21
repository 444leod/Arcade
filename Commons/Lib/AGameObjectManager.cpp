/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObjectManager
*/

#include "GameObject/AGameObjectManager.hpp"
#include "SnakeObject/SnakeConstants.hpp"
#include <algorithm>

std::vector<std::pair<position, std::string>> AGameObjectManager::dump() const
{
    std::vector<std::pair<position, std::string>> res;

    for (auto &obj : _gameObjects) {
        res.push_back(obj->dumpTexture());
    }
    return res;
}

std::vector<position> AGameObjectManager::getPos() const
{
    std::vector<position> res;

    for (auto &obj : _gameObjects) {
        res.push_back(obj->getPos());
    }
    return res;
}

void AGameObjectManager::applyEffects(SnakeObject &snake) const
{
    for (auto &obj : _gameObjects) {
        obj->applyEffect(snake);
    }
}

position AGameObjectManager::getSpawnPos(std::vector<position> forbidenPositions) const
{
    position pos {
        rand() % ARENA_WIDTH + 1,
        rand() % ARENA_HEIGHT + 1
    };
    for (auto &obj : _gameObjects) {
        forbidenPositions.push_back(obj->getPos());
    }
    while (std::find(forbidenPositions.begin(), forbidenPositions.end(), pos) != forbidenPositions.end()) {
        pos = position {
            rand() % ARENA_WIDTH + 1,
            rand() % ARENA_HEIGHT + 1
        };
    }
    return pos;
}
