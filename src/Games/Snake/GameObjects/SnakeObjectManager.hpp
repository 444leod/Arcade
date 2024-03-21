/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** SnakeObjectManager
*/

#include "SnakeLib/GameObject/AGameObjectManager.hpp"

#pragma once

class SnakeObjectManager : public AGameObjectManager {
    public:
        SnakeObjectManager();

        ~SnakeObjectManager();

        void update(position objectCollided, SnakeObject& snake, float deltaTime) override;

    protected:
    private:
};
