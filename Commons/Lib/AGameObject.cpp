/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameObject
*/

#include "GameObject/AGameObject.hpp"

void AGameObject::applyEffect([[maybe_unused]] SnakeObject &snake)
{
    snake.setAlive(!_effects.killPlayer);
    snake.setSpeed(snake.getSpeed() + _effects.deltaSpeed);
    snake.setScore(snake.getScore() + _effects.deltaScore);
    if (_effects.deltaGrowth > 0)
        snake.grow(snake.getPositions()[0].x, snake.getPositions()[0].y, _effects.deltaGrowth);
}
