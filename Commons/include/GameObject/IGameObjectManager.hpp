/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** IGameObjectManager
*/

#include <vector>
#include <string>

#include "GameObject/IGameObject.hpp"
#include "position.hpp"

#pragma once

class IGameObjectManager {
    public:
        virtual ~IGameObjectManager() = default;

        virtual void update(position objectCollided, SnakeObject& snake, float deltaTime) = 0;

        virtual std::vector<std::pair<position, std::string>> dump() const = 0;

        virtual std::vector<position> getPos() const = 0;
        
        virtual void applyEffects(SnakeObject &snake) const = 0;

    protected:
        virtual position getSpawnPos(std::vector<position> forbidenPositions) const = 0;
    private:
};
