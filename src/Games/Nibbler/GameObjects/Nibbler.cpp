/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NibblerObject
*/

#include "Nibbler.hpp"

Nibbler::Nibbler(std::vector<std::vector<int>> map)
{
    for (uint64_t i = 0; i < 4; i++)
        _body.push_back(Vec2i {
            static_cast<int>(map[0].size()) / 2 - static_cast<int>(i),
            static_cast<int>(map.size()) / 2
        });
}

Vec2i Nibbler::update(std::vector<Vec2i> objectsPos, float deltaTime)
{
    _elapsed += deltaTime;
    while (_elapsed > _speed) {
        if (!_alive)
            return {-1, -1};
        _elapsed -= _speed;
        Vec2i movRes = move(objectsPos);
        if (Vec2i{-1, -1} != movRes) {
            return movRes;
        }
    }
    return {-1, -1};
}