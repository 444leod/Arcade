/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** IGameObjectManager
*/

#include <vector>
#include <string>

#include "SnakeLib/GameObject/IGameObject.hpp"

#pragma once

class IGameObjectManager {
    public:
        virtual ~IGameObjectManager() = default;

        virtual void update(Vec2i objectCollided, SnakeObject& snake, float deltaTime) = 0;

        virtual std::vector<std::pair<Vec2i, std::string>> dump() const = 0;

        virtual std::vector<Vec2i> getPos() const = 0;
        
        virtual void applyEffects(SnakeObject &snake) const = 0;

    protected:
        virtual Vec2i getSpawnPos(std::vector<Vec2i> forbidenPositions) const = 0;
    private:
};
