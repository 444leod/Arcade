/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** SuperCandy
*/

#include <string>

#include "SuperCandy.hpp"

SuperCandy::SuperCandy(std::string textureName, IGameObject::pos pos) : AGameObject(textureName, pos)
{
    _effects = {
        1,
        0,
        0,
        false
    };

}
