/*
** EPITECH PROJECT, 2024
** GameObjects
** File description:
** TamatoBerry
*/

#include "TamatoBerry.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

TamatoBerry::TamatoBerry(Vec2i pos) : AGameObject(pos)
{
    _textureName = "tamato_berry";
    _effects.deltaScore = 0;
    _effects.deltaSpeed = BASE_SPEED;
    _effects.deltaGrowth = 0;
    _effects.killPlayer = false;
    _respawn = false;
    _type = IGameObject::TAMATO_BERRY;
}

void TamatoBerry::applyEffect(SnakeObject &snake)
{
    snake.setAlive(!_effects.killPlayer);
    snake.setSpeed(_effects.deltaSpeed);
    snake.setScore(snake.getScore() + _effects.deltaScore);
    if (_effects.deltaGrowth > 0) {
        snake.grow(_pos.x, _pos.y, _effects.deltaGrowth);
        snake.setGrowToggle(false);
    }
    _pos = Vec2i{-1, -1};
}