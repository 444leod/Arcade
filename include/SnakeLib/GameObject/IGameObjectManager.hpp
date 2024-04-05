/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** IGameObjectManager
*/

#pragma once

#include <vector>
#include <string>

#include "SnakeLib/GameObject/IGameObject.hpp"

class IGameObjectManager {
    public:
        virtual ~IGameObjectManager() = default;

        virtual void update(Vec2i objectCollided, ASnakeObject& snake, float deltaTime) = 0;

        virtual std::vector<std::pair<Vec2i, std::string>> dump() const = 0;

        virtual std::vector<Vec2i> getPos() const = 0;

        virtual std::vector<Vec2i> getBlockingPos() const = 0;
        
        virtual std::vector<Vec2i> getForbidenPos(ASnakeObject &snake) const = 0;

        virtual void applyEffects(ASnakeObject &snake) const = 0;

    protected:
        virtual Vec2i getSpawnPos(std::vector<Vec2i> forbidenPositions) const = 0;
    private:
};
