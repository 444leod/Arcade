/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SnakeObject
*/

#include <vector>
#include <string>
#include <map>

#include "SnakeObject/SnakeObject.hpp"
#include "SnakeObject/SnakeConstants.hpp"

// Public Member Functions

SnakeObject::SnakeObject()
{
    _score = 0;
    _speed = 0.2;
    _elapsed = 0;
    _alive = true;
    _readyToRotate = true;
    _direction = std::make_pair(1, 0);
    for (int i = 0; i < 4; i++)
        _body.push_back(SnakeObject::BodyPart {(ARENA_WIDTH + 1) / 2 - i, (ARENA_HEIGHT + 1) / 2});
}

bool SnakeObject::setDirection(std::pair<int, int> direction)
{
    if ((_direction.first == -direction.first && _direction.second == -direction.second) ||
        (_direction.first == direction.first && _direction.second == direction.second) ||
        _alive == false ||
        _readyToRotate == false)
        return false;
    _direction = direction;
    _readyToRotate = false;
    return true;
}

position SnakeObject::update([[maybe_unused]] std::vector<position> objectsPos, float deltaTime)
{
    _elapsed += deltaTime;
    while (_elapsed > _speed) {
        if (!_alive)
            return {-1, -1};
        position movRes = move(objectsPos);
        if (movRes.x != -1 && movRes.y != -1) {
            return movRes;
            // _score += 1;
            // _gameSpeed -= _gameSpeed < 0.02 ? 0 : 0.005;
            // resetGoal();
            // _superCandy.setPos({_goalPos.x, _goalPos.y});
            // printf("%d, %d\n", _superCandy.getPos().x, _superCandy.getPos().y);
        }

        _elapsed -= _speed;
    }
    return {-1, -1};
}

std::vector<std::pair<SnakeObject::BodyPart, std::string>> SnakeObject::dump() const
{
    std::vector<std::pair<SnakeObject::BodyPart, std::string>> res;
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

std::vector<position> SnakeObject::getPositions() const
{
    std::vector<position> res;

    for (auto &part : _body) {
        res.push_back({part.x, part.y});
    }
    return res;
}

// Privates Member Functions

position SnakeObject::move([[maybe_unused]] std::vector<position> objectsPos)
{
    int old_x = _body[0].x;
    int old_y = _body[0].y;

    _readyToRotate = true;

    // if (_body[0].x + _direction.first ==  goalPos.first && _body[0].y + _direction.second == goalPos.second) {
    //     grow(goalPos.first, goalPos.second, 1);
    //     return true;
    // }
    for (auto &pos : objectsPos) {
        if (_body[0].x + _direction.first == pos.x && _body[0].y + _direction.second == pos.y) {
            return pos;
        }
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
    return {-1, -1};
}

void SnakeObject::grow(int x, int y, std::size_t size)
{
    for (size_t i = 0; i < size; i++)
        _body.insert(_body.begin(), SnakeObject::BodyPart{x, y});
}

bool SnakeObject::checkCollision(int oldX, int oldY)
{
    if (_body[0].x == oldX && _body[0].y == oldY)
        return true;
    for (std::size_t i = 1; i < _body.size(); i++) {
        if (_body[0].x == _body[i].x && _body[0].y == _body[i].y)
            return true;
    }
    return false;
}

std::pair<SnakeObject::BodyPart, std::string> SnakeObject::getDumpHead() const
{
    return std::make_pair(_body[0], _headTextures.at(std::make_tuple(
        _direction.first,
        _direction.second
    )));
}

std::pair<SnakeObject::BodyPart, std::string> SnakeObject::getDumpTail(std::size_t len) const
{
    return std::make_pair(_body[len - 1], _tailTextures.at(std::make_tuple(
            _body[len - 1].x - _body[len - 2].x,
            _body[len - 1].y - _body[len - 2].y
    )));
}

std::pair<SnakeObject::BodyPart, std::string> SnakeObject::getDumpBody(std::size_t i) const
{
    return std::make_pair(_body[i], _bodyTextures.at(std::make_tuple(
        _body[i].x - _body[i - 1].x,
        _body[i].x - _body[i + 1].x,
        _body[i].y - _body[i - 1].y,
        _body[i].y - _body[i + 1].y
    )));
}
