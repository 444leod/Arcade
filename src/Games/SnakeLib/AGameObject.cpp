/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObject
*/

#include "SnakeLib/GameObject/AGameObject.hpp"

void AGameObject::applyEffect(SnakeObject &snake)
{
    snake.setAlive(!_effects.killPlayer);
    snake.setSpeed(snake.getSpeed() * _effects.deltaSpeed);
    snake.setScore(snake.getScore() + _effects.deltaScore);
    if (_effects.deltaGrowth > 0) {
        snake.grow(_pos.x, _pos.y, _effects.deltaGrowth);
        snake.setGrowToggle(false);
    } else if (_effects.deltaGrowth < 0) {
        snake.shrink(-_effects.deltaGrowth);
        snake.continueMove();
    } else {
        snake.continueMove();
    }
}
