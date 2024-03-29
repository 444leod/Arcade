/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** AguavBerry
*/

#include "AguavBerry.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

AguavBerry::AguavBerry(Vec2i pos) : AGameObject(pos)
{
    _textureName = "aguav_berry";
    _effects.deltaScore = -5;
    _effects.deltaSpeed = 1;
    _effects.deltaGrowth = -1;
    _effects.killPlayer = false;
    _respawn = false;
    _type = IGameObject::Type::AGUAV_BERRY;
}
