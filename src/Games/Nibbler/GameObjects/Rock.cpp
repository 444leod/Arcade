/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** Rock
*/

#include "Rock.hpp"

Rock::Rock(Vec2i pos) : AGameObject(pos)
{
    _textureName = "rock";
    _effects.deltaScore = 0;
    _effects.deltaSpeed = 1;
    _effects.deltaGrowth = 0;
    _effects.killPlayer = false;
    _respawn = false;
    _type = IGameObject::Type::AGUAV_BERRY;
}
