/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObjectManager
*/

#include "SnakeLib/GameObject/AGameObjectManager.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include "RandomNumberGenerator.hpp"
#include <algorithm>

std::vector<std::pair<Vec2i, std::string>> AGameObjectManager::dump() const
{
    std::vector<std::pair<Vec2i, std::string>> res;

    for (auto &obj : _gameObjects) {
        res.push_back(obj->dumpTexture());
    }
    return res;
}

std::vector<Vec2i> AGameObjectManager::getPos() const
{
    std::vector<Vec2i> res;

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

Vec2i AGameObjectManager::getSpawnPos(std::vector<Vec2i> forbidenPositions) const
{
    Vec2i pos {
        rng::rand(1, ARENA_WIDTH ),
        rng::rand(1, ARENA_HEIGHT)
    };
    for (auto &obj : _gameObjects) {
        forbidenPositions.push_back(obj->getPos());
    }
    while (std::find(forbidenPositions.begin(), forbidenPositions.end(), pos) != forbidenPositions.end()) {
        pos = Vec2i {
            rng::rand(1, ARENA_WIDTH),
            rng::rand(1, ARENA_HEIGHT)
        };
    }
    return pos;
}
