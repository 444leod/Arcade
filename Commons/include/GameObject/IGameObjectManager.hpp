/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** IGameObjectManager
*/

#include <vector>
#include <string>

#include "GameObject/IGameObject.hpp"

#pragma once

class IGameObjectManager {
    public:
        virtual ~IGameObjectManager() = default;

        virtual void update() = 0;

        virtual std::vector<std::pair<IGameObject::pos, std::string>> dump() = 0;

    protected:
    private:
};
