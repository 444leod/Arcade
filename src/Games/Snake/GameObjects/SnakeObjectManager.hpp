/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** SnakeObjectManager
*/

#pragma once

#include "SnakeLib/GameObject/AGameObjectManager.hpp"
#include "Vec2.hpp"
#include "SuperCandy.hpp"
#include "TamatoBerry.hpp"
#include "AguavBerry.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include <random>

class SnakeObjectManager : public AGameObjectManager {
    public:
        SnakeObjectManager();

        ~SnakeObjectManager();

        void update(Vec2i objectCollided, SnakeObject& snake, float deltaTime) override;

    protected:
    private:
};
