/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SuperCandy
*/

#include "AGameObject.hpp"

#pragma once

class SuperCandy : public AGameObject{
    public:
        SuperCandy(std::string textureName, IGameObject::pos pos) : AGameObject(textureName, pos) {}
        ~SuperCandy() = default;

    protected:
    private:
};
