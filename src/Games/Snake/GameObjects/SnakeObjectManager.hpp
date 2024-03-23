/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** SnakeObjectManager
*/

#pragma once

#include "SnakeLib/GameObject/AGameObjectManager.hpp"
#include "RandomNumberGenerator.hpp"
#include "Vec2.hpp"


class SnakeObjectManager : public AGameObjectManager {
    public:
        SnakeObjectManager();

        ~SnakeObjectManager();

        void update(Vec2i objectCollided, SnakeObject& snake, float deltaTime) override;

    protected:
    private:
};
