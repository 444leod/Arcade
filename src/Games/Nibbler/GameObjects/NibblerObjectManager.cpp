/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** NibblerObjectManager
*/

#include "NibblerObjectManager.hpp"

#include <memory>
#include <iostream>

NibblerObjectManager::NibblerObjectManager() : AGameObjectManager() {}

NibblerObjectManager::~NibblerObjectManager() {}

void NibblerObjectManager::update(Vec2i objectCollided, ASnakeObject& snake, [[maybe_unused]] float deltaTime)
{
    if (Vec2i{-1, -1} == objectCollided) {
        return;
    }
    for (auto &obj : _gameObjects) {
        if (obj->getPos() == objectCollided) {
            obj->applyEffect(snake);
            if (obj->getRespawn() == true)
                obj->setPos(getSpawnPos(getForbidenPos(snake)));
            if (obj->getBlocking() == false)
                obj->setPos(Vec2i{-1, -1});
        }
    }
}

void NibblerObjectManager::initMapObjects(std::vector<std::vector<int>> map)
{
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