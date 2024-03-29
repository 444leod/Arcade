/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** SnakeObjectManager
*/

#include "SnakeObjectManager.hpp"
#include "SuperCandy.hpp"
#include "TamatoBerry.hpp"
#include "AguavBerry.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include <memory>

SnakeObjectManager::SnakeObjectManager() : AGameObjectManager()
{
    _gameObjects.push_back(std::make_unique<SuperCandy>(
        getSpawnPos(std::vector<Vec2i> {
            {(ARENA_WIDTH + 1) / 2 - 0, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 1, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 2, (ARENA_HEIGHT + 1) / 2},
            {(ARENA_WIDTH + 1) / 2 - 3, (ARENA_HEIGHT + 1) / 2}
        })
    ));
    _gameObjects.push_back(std::make_unique<TamatoBerry>(Vec2i{-1, -1}));
    _gameObjects.push_back(std::make_unique<AguavBerry>(Vec2i{-1, -1}));
}

SnakeObjectManager::~SnakeObjectManager() {}

void SnakeObjectManager::update(Vec2i objectCollided, SnakeObject& snake, [[maybe_unused]] float deltaTime)
{
    bool spawnTamato = false;
    bool spawnAguav = false;

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
            if (obj->getType() == IGameObject::Type::SUPER_CANDY && rng::rand(0, 9) == 0)
                spawnTamato = true;
            if (obj->getType() == IGameObject::Type::SUPER_CANDY && rng::rand(0, 2) == 0)
                spawnAguav = true;
        }
    }
    for (auto &obj : _gameObjects) {
        if (obj->getType() == IGameObject::Type::TAMATO_BERRY && spawnTamato && obj->getPos() == Vec2i{-1, -1}) {
            obj->setPos(getSpawnPos(getForbidenPos(snake)));
            spawnTamato = false;
        }
        if (obj->getType() == IGameObject::Type::AGUAV_BERRY && spawnAguav && obj->getPos() == Vec2i{-1, -1}) {
            obj->setPos(getSpawnPos(getForbidenPos(snake)));
            spawnAguav = false;
        }
    }
}

