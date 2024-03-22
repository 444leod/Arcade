/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** SnakeObjectManager
*/

#include "SnakeLib/GameObject/AGameObjectManager.hpp"
#include "Vec2.hpp"

#pragma once

class SnakeObjectManager : public AGameObjectManager {
    public:
        SnakeObjectManager();

        ~SnakeObjectManager();

        void update(Vec2i objectCollided, SnakeObject& snake, float deltaTime) override;

    protected:
    private:
};
