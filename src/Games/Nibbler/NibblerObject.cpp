/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NibblerObject
*/

#include "NibblerObject.hpp"

Vec2i NibblerObject::update(std::vector<Vec2i> objectsPos, float deltaTime)
{
    printf("testnbur\n");
    _elapsed += deltaTime;
    while (_elapsed > _speed) {
        if (!_alive)
            return {-1, -1};
        printf("test\n");
        _elapsed -= _speed;
        Vec2i movRes = move(objectsPos);
        if (Vec2i{-1, -1} != movRes) {
            return movRes;
        }
    }
    return {-1, -1};
}