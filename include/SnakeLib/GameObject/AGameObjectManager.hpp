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

        virtual void update(position objectCollided, SnakeObject& snake, float deltaTime) = 0;

        virtual std::vector<std::pair<position, std::string>> dump() const;

        virtual std::vector<position> getPos() const;
        
        virtual void applyEffects(SnakeObject &snake) const;

    protected:
        virtual position getSpawnPos(std::vector<position> forbidenPositions) const;

        std::vector<std::shared_ptr<IGameObject>> _gameObjects;
    private:
};
