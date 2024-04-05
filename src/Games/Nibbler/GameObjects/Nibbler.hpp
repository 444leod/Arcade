/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#pragma once

#include "SnakeLib/SnakeObject/ASnakeObject.hpp"

class Nibbler : public ASnakeObject {
    public:
        Nibbler() = default;
        Nibbler(std::vector<std::vector<int>> map);
        ~Nibbler() = default;

        Vec2i update(std::vector<Vec2i> objectsPos, float deltaTime) override;

    protected:
    private:
};
