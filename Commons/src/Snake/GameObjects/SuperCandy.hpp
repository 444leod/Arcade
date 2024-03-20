/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SuperCandy
*/

#include "GameObject/AGameObject.hpp"

#pragma once

class SuperCandy : public AGameObject {
    public:
        SuperCandy(std::string textureName, IGameObject::pos pos);

        ~SuperCandy() = default;

    protected:
    private:
};
