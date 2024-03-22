/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** SnakeObjectManager
*/

#include "SnakeObjectManager.hpp"
#include "SuperCandy.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include <memory>

SnakeObjectManager::SnakeObjectManager()
{
    _gameObjects.push_back(std::make_shared<SuperCandy>(
        getSpawnPos(std::vector<Vec2i> {
            {(ARENA_WIDTH + 1) / 2 - 0, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 1, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 2, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 3, (ARENA_HEIGHT + 1) / 2}
        })
    ));
}

SnakeObjectManager::~SnakeObjectManager() {}

void SnakeObjectManager::update(Vec2i objectCollided, SnakeObject& snake, [[maybe_unused]] float deltaTime)
{
    if (Vec2i{-1, -1} == objectCollided) {
        return;
    }
    for (auto &obj : _gameObjects) {
        if (obj->getPos() == objectCollided) {
            obj->applyEffect(snake);
        }
        obj->setPos(getSpawnPos(snake.getPositions()));
    }
}

