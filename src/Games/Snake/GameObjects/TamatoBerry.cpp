/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** TamatoBerry
*/

#include "TamatoBerry.hpp"

TamatoBerry::TamatoBerry(Vec2i pos) : AGameObject(pos)
{
    _textureName = "tamato_berry";
    _effects.deltaScore = -5;
    _effects.deltaSpeed = BASE_SPEED;
    _effects.deltaGrowth = 0;
    _effects.killPlayer = false;
    _respawn = false;
    _type = IGameObject::TAMATO_BERRY;
}

void TamatoBerry::applyEffect(SnakeObject &snake) {
    AGameObject::applyEffect(snake);
    snake.setSpeed(_effects.deltaSpeed);
}
