/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** NibblerObjectManager
*/

#include "NibblerObjectManager.hpp"

#include <memory>
#include <iostream>

NibblerObjectManager::NibblerObjectManager() : AGameObjectManager()
{
    // _gameObjects.push_back(std::make_unique<SuperCandy>(
    //     getSpawnPos(std::vector<Vec2i> {
    //         {(ARENA_WIDTH + 1) / 2 - 0, (ARENA_HEIGHT + 1) / 2},
    //         {(ARENA_WIDTH + 1) / 2 - 1, (ARENA_HEIGHT + 1) / 2},
    //         {(ARENA_WIDTH + 1) / 2 - 2, (ARENA_HEIGHT + 1) / 2},
    //         {(ARENA_WIDTH + 1) / 2 - 3, (ARENA_HEIGHT + 1) / 2}
    //     })
    // ));
    // _gameObjects.push_back(std::make_unique<TamatoBerry>(Vec2i{-1, -1}));
    // _gameObjects.push_back(std::make_unique<AguavBerry>(Vec2i{-1, -1}));
}

NibblerObjectManager::~NibblerObjectManager() {}

void NibblerObjectManager::update(Vec2i objectCollided, SnakeObject& snake, [[maybe_unused]] float deltaTime)
{
    if (Vec2i{-1, -1} == objectCollided) {
        return;
    }
    for (auto &obj : _gameObjects) {
        if (obj->getPos() == objectCollided) {
            obj->applyEffect(snake);
            if (obj->getRespawn() == true)
                obj->setPos(getSpawnPos(getForbidenPos(snake)));
            else
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
                    std::cout << "0";
                    _gameObjects.push_back(std::make_unique<Rock>(Vec2i{x, y}));
                    break;
                case 1: std::cout << "1"; break;
                case 2:
                    std::cout << "2";
                    _gameObjects.push_back(std::make_unique<SuperCandy>(Vec2i{x, y}));
                    break;
                default: std::cout << "?"; break;
            }
        }
        std::cout << std::endl;
    }
}