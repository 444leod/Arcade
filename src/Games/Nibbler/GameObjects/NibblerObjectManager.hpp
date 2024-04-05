/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** NibblerObjectManager
*/

#pragma once

#include "SnakeLib/GameObject/AGameObjectManager.hpp"
#include "Vec2.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include "Rock.hpp"
#include "SuperCandy.hpp"

#include <random>

class NibblerObjectManager : public AGameObjectManager {
    public:
        NibblerObjectManager();

        ~NibblerObjectManager();

        void update(Vec2i objectCollided, ASnakeObject& snake, float deltaTime) override;

        void initMapObjects(std::vector<std::vector<int>> map);

    protected:
    private:
};
