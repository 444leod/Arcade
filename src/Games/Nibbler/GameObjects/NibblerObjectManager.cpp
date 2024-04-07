/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** NibblerObjectManager
*/

#include "NibblerObjectManager.hpp"

#include <memory>
#include <iostream>
#include <algorithm>

NibblerObjectManager::NibblerObjectManager() : AGameObjectManager() {}

NibblerObjectManager::~NibblerObjectManager() {}

void NibblerObjectManager::update(Vec2i objectCollided, ASnakeObject& snake, [[maybe_unused]] float deltaTime)
{
    if (Vec2i{-1, -1} == objectCollided) {
        return;
    }
    for (auto &obj : _gameObjects) {

        if (obj->getPos() == objectCollided) {
            if (obj->getBlocking() == true)
                handleAutoRedirection(snake, obj->getPos());
            obj->applyEffect(snake);
            if (obj->getRespawn() == true)
                obj->setPos(getSpawnPos(getForbidenPos(snake)));
            if (obj->getBlocking() == false)
                obj->setPos(Vec2i{-1, -1});
        }
    }
}

bool NibblerObjectManager::checkWin(ASnakeObject& snake)
{
    uint16_t eatenCandies = 0;

    for (auto &obj : _gameObjects)
        if (obj->getType() == IGameObject::Type::SUPER_CANDY && obj->getPos() == Vec2i{-1, -1})
            eatenCandies++;
    if (eatenCandies == getSizeByType(IGameObject::Type::SUPER_CANDY))
        snake.setWon(true);
    return snake.getWon();
}

void NibblerObjectManager::handleAutoRedirection(ASnakeObject& snake, Vec2i blockingObj)
{
    Vec2i head = snake.getPositions()[0];
    Vec2i headDelta = head - blockingObj;
    std::vector<Vec2i> objectsPos = getBlockingPos();
    Vec2i newDir = {0, 0};

    if (headDelta.x == 0) {
        if (std::find(objectsPos.begin(), objectsPos.end(), head + Vec2i{1, 0}) == objectsPos.end())
            newDir += Vec2i{1, 0};
        if (std::find(objectsPos.begin(), objectsPos.end(), head + Vec2i{-1, 0}) == objectsPos.end())
            newDir += Vec2i{-1, 0};
    }
    if (headDelta.y == 0) {
        if (std::find(objectsPos.begin(), objectsPos.end(), head + Vec2i{0, 1}) == objectsPos.end())
            newDir += Vec2i{0, 1};
        if (std::find(objectsPos.begin(), objectsPos.end(), head + Vec2i{0, -1}) == objectsPos.end())
            newDir += Vec2i{0, -1};
    }
    if (newDir != Vec2i{0, 0})
        snake.setDirection({newDir.x, newDir.y});
    snake.continueMove();
}

void NibblerObjectManager::initMapObjects(std::vector<std::vector<int>> map)
{
    _gameObjects.clear();
    for (uint16_t y = 0; y < map.size(); y++) {
        for (uint16_t x = 0; x < map[y].size(); x++) {
            switch (map[y][x]) {
                case 0:
                    _gameObjects.push_back(std::make_unique<Rock>(Vec2i{x, y}));
                    break;
                case 2:
                    _gameObjects.push_back(std::make_unique<SuperCandy>(Vec2i{x, y}));
                    break;
                default: break;
            }
        }
    }
}