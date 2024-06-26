/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObjectManager
*/

#include "SnakeLib/GameObject/AGameObjectManager.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include <algorithm>

AGameObjectManager::AGameObjectManager()
{
    for (int x = 1; x < ARENA_WIDTH + 1; x++)
        for (int y = 1; y < ARENA_HEIGHT + 1; y++) {
            _basePositions.push_back(Vec2i{x, y});
        }
}

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

std::vector<Vec2i> AGameObjectManager::getBlockingPos() const
{
    std::vector<Vec2i> blockingPos;

    for (auto &obj : _gameObjects) {
        if (obj->getBlocking() == true)
            blockingPos.push_back(obj->getPos());
    }
    return blockingPos;
}

std::vector<Vec2i> AGameObjectManager::getForbidenPos(ASnakeObject &snake) const
{
    std::vector<Vec2i> res;

    for (auto &obj : _gameObjects) {
        res.push_back(obj->getPos());
    }
    for (auto &pos : snake.getPositions()) {
        res.push_back(pos);
    }
    return res;
}

void AGameObjectManager::applyEffects(ASnakeObject &snake) const
{
    for (auto &obj : _gameObjects) {
        obj->applyEffect(snake);
    }
}

Vec2i AGameObjectManager::getSpawnPos(std::vector<Vec2i> forbidenPositions) const
{
    std::vector<Vec2i> authorizedPos;

    for (auto &pos : _basePositions) {
        if (std::find(forbidenPositions.begin(), forbidenPositions.end(), pos) == forbidenPositions.end()) {
            authorizedPos.push_back(pos);
        }
    }
    return authorizedPos[std::rand() % (authorizedPos.size() - 1)];
}

uint64_t AGameObjectManager::getSizeByType(IGameObject::Type type) const
{
    uint64_t size = 0;

    for (auto &obj : _gameObjects) {
        if (obj->getType() == type)
            size++;
    }
    return size;
}
