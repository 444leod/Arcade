/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** Rock
*/

#pragma once

#include "SnakeLib/GameObject/AGameObject.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

class Rock : public AGameObject{
    public:
    Rock(Vec2i pos);

    ~Rock() = default;

    protected:
    private:
};
