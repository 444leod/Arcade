/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObjectManager
*/

#include <vector>
#include <memory>

#include "SnakeLib/GameObject/IGameObjectManager.hpp"

#pragma once

class AGameObjectManager : public IGameObjectManager{
    public:
        AGameObjectManager() {};

        ~AGameObjectManager() {};

        virtual void update(Vec2i objectCollided, SnakeObject& snake, float deltaTime) = 0;

        virtual std::vector<std::pair<Vec2i, std::string>> dump() const;

        virtual std::vector<Vec2i> getPos() const;
        
        virtual void applyEffects(SnakeObject &snake) const;

    protected:
        virtual Vec2i getSpawnPos(std::vector<Vec2i> forbidenPositions) const;

        std::vector<std::shared_ptr<IGameObject>> _gameObjects;
    private:
};
