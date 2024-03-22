/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** SuperCandy
*/

#include <string>

#include "SuperCandy.hpp"

SuperCandy::SuperCandy(Vec2i pos) : AGameObject(pos)
{
    _textureName = "super_candy";
    _effects.deltaScore = 10;
    _effects.deltaSpeed = 0.95;
    _effects.deltaGrowth = 1;
    _effects.killPlayer = false;
}
