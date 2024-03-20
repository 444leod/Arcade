/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObjectManager
*/

#include <vector>
#include <memory>

#include "GameObject/IGameObject.hpp"

#pragma once

class AGameObjectManager {
    public:
        virtual ~AGameObjectManager() = default;

        virtual void update() = 0;

        virtual std::vector<std::pair<IGameObject::pos, std::string>> dump() = 0;

    protected:
        std::vector<std::shared_ptr<IGameObject>> _gameObjects;
    private:
};
