/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NibblerObject
*/

#pragma once

#include "SnakeLib/SnakeObject/SnakeObject.hpp"

class NibblerObject : public SnakeObject {
    public:
        NibblerObject();
        ~NibblerObject();

        Vec2i update(std::vector<Vec2i> objectsPos, float deltaTime) override;

    protected:
    private:
};
