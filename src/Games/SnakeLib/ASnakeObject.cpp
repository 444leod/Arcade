/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ASnakeObject
*/

#include <vector>
#include <string>

#include "SnakeLib/SnakeObject/ASnakeObject.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

#include <iostream>

// Public Member Functions

ASnakeObject::ASnakeObject() {}

bool ASnakeObject::setDirection(std::pair<int, int> direction)
{
    if ((_direction.first == -direction.first && _direction.second == -direction.second) ||
        (_direction.first == direction.first && _direction.second == direction.second) ||
        _alive == false)
        return false;
    if (_body[1].x == _body[0].x + direction.first && _body[1].y == _body[0].y + direction.second)
        return false;
    _oldDirection = _direction;
    _direction = direction;
    return true;
}

Vec2i ASnakeObject::update(std::vector<Vec2i> objectsPos, float deltaTime)
{
    _elapsed += deltaTime;
    while (_elapsed > _speed) {
        if (!_alive)
            return {-1, -1};
        Vec2i movRes = move(objectsPos);
        if (Vec2i{-1, -1} != movRes) {
            return movRes;
        }
        _elapsed -= _speed;
    }
    return {-1, -1};
}

std::vector<std::pair<Vec2i, std::string>> ASnakeObject::dump() const
{
    std::vector<std::pair<Vec2i, std::string>> res;
    std::size_t len = _body.size();
    std::size_t i = 0;
    for (auto &part : _body) {
        if (&part == &_body[0])
            res.push_back(getDumpHead());
        else if (&part == &_body[len - 1])
            res.push_back(getDumpTail(len));
        else
            res.push_back(getDumpBody(i));
        i++;
    }
    return res;
}

std::vector<Vec2i> ASnakeObject::getPositions() const
{
    std::vector<Vec2i> res;

    for (auto &part : _body) {
        res.push_back({part.x, part.y});
    }
    return res;
}

void ASnakeObject::grow(int x, int y, std::size_t size)
{
    for (size_t i = 0; i < size; i++)
        _body.insert(_body.begin(), Vec2i{x, y});
}

void ASnakeObject::shrink(size_t size)
{
    for (size_t i = 0; i < size; i++)
        _body.pop_back();
}

Vec2i ASnakeObject::continueMove(void)
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
    if ((_body[0].x > 1 && _direction.first < 0) ||
        (_body[0].x < ARENA_WIDTH  && _direction.first > 0))
        _body[0].x += _direction.first;

    if ((_body[0].y > 1 && _direction.second < 0) ||
        (_body[0].y < ARENA_HEIGHT  && _direction.second > 0))
        _body[0].y += _direction.second;

    if (checkCollision(old_x, old_y))
        _alive = false;
    _growthToggle = true;    
    return {-1, -1};
}

// Privates Member Functions

Vec2i ASnakeObject::move(std::vector<Vec2i> objectsPos)
{
    _oldDirection = _direction;

    for (auto &pos : objectsPos) {
        if (_body[0].x + _direction.first == pos.x && _body[0].y + _direction.second == pos.y) {
            _growthToggle = false;
            return pos;
        }
    }

    return continueMove();
}

bool ASnakeObject::checkCollision(int oldX, int oldY)
{
    if (_body[0].x == oldX && _body[0].y == oldY)
        return true;
    for (std::size_t i = 1; i < _body.size(); i++) {
        if (_body[0].x == _body[i].x && _body[0].y == _body[i].y)
            return true;
    }
    return false;
}

std::pair<Vec2i, std::string> ASnakeObject::getDumpHead() const
{
    return std::make_pair(_body[0], _headTextures.at(std::make_tuple(
        _oldDirection.first,
        _oldDirection.second
    )));
}

std::pair<Vec2i, std::string> ASnakeObject::getDumpTail(std::size_t len) const
{
    return std::make_pair(_body[len - 1], _tailTextures.at(std::make_tuple(
            _body[len - 1].x - _body[len - 2].x,
            _body[len - 1].y - _body[len - 2].y
    )));
}

std::pair<Vec2i, std::string> ASnakeObject::getDumpBody(std::size_t i) const
{
    return std::make_pair(_body[i], _bodyTextures.at(std::make_tuple(
        _body[i].x - _body[i - 1].x,
        _body[i].x - _body[i + 1].x,
        _body[i].y - _body[i - 1].y,
        _body[i].y - _body[i + 1].y
    )));
}
