/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** SnakeObjectManager
*/

#include "SnakeObjectManager.hpp"
#include "SuperCandy.hpp"
#include "SnakeObject/SnakeConstants.hpp"
#include <memory>

SnakeObjectManager::SnakeObjectManager()
{
    _gameObjects.push_back(std::make_shared<SuperCandy>(
        getSpawnPos(std::vector<position> {
            {(ARENA_WIDTH + 1) / 2 - 0, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 1, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 2, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 3, (ARENA_HEIGHT + 1) / 2}
        })
    ));
}

SnakeObjectManager::~SnakeObjectManager() {}

void SnakeObjectManager::update(position objectCollided, SnakeObject& snake, [[maybe_unused]] float deltaTime)
{
    if (objectCollided.x == -1 && objectCollided.y == -1) {
        return;
    }
    for (auto &obj : _gameObjects) {
        if (obj->getPos().x == objectCollided.x && obj->getPos().y == objectCollided.y) {
            obj->applyEffect(snake);
        }
        obj->setPos(getSpawnPos(snake.getPositions()));
    }
}

