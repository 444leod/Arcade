/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObjectManager
*/

#pragma once

#include <vector>
#include <memory>

#include "SnakeLib/GameObject/IGameObjectManager.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

class AGameObjectManager : public IGameObjectManager{
    public:
        AGameObjectManager();

        ~AGameObjectManager() {};

        virtual void update(Vec2i objectCollided, ASnakeObject& snake, float deltaTime) = 0;

        virtual std::vector<std::pair<Vec2i, std::string>> dump() const;

        virtual std::vector<Vec2i> getPos() const;

        virtual std::vector<Vec2i> getBlockingPos() const;

        virtual std::vector<Vec2i> getForbidenPos(ASnakeObject &snake) const;
        
        virtual void applyEffects(ASnakeObject &snake) const;

    protected:
        std::vector<Vec2i> _basePositions;

        virtual Vec2i getSpawnPos(std::vector<Vec2i> forbidenPositions) const;

        std::vector<std::unique_ptr<IGameObject>> _gameObjects;
    private:
};
