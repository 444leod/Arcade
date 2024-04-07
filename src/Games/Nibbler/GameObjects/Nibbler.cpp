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
            static_cast<int>(map.size()) - 2
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

Vec2i Nibbler::continueMove(void)
{
    int old_x = _body[0].x;
    int old_y = _body[0].y;

    if (_growthToggle == false) {
        _growthToggle = true;
        return {-1, -1};
    }
    if (!(_direction.first == 0 && _direction.second == 0)) {
        for (std::size_t i = _body.size() - 1; i > 0; i--) {
            _body[i].x = _body[i - 1].x;
            _body[i].y = _body[i - 1].y;
        }
    }
    if ((_body[0].x > 1 && _direction.first < 0) || (_direction.first > 0))
        _body[0].x += _direction.first;

    if ((_body[0].y > 1 && _direction.second < 0) || (_direction.second > 0))
        _body[0].y += _direction.second;

    if (checkCollision(old_x, old_y))
        _alive = false;
    _growthToggle = true;    
    return {-1, -1};
}
