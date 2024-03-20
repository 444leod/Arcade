/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include <vector>
#include <string>
#include <map>

#include "Snake.hpp"

// Public Member Functions

Snake::Snake()
{
    _alive = true;
    _readyToRotate = true;
    _direction = std::make_pair(1, 0);
    for (int i = 0; i < 4; i++)
        _body.push_back(Snake::BodyPart {(ARENA_WIDTH + 1) / 2 - i, (ARENA_HEIGHT + 1) / 2});
}

bool Snake::setDirection(std::pair<int, int> direction)
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

bool Snake::move(std::pair<int, int> goalPos)
{
    int old_x = _body[0].x;
    int old_y = _body[0].y;

    _readyToRotate = true;
    if (_body[0].x + _direction.first ==  goalPos.first && _body[0].y + _direction.second == goalPos.second) {
        grow(goalPos.first, goalPos.second, 1);
        return true;
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
    return false;
}

void Snake::grow(int x, int y, std::size_t size)
{
    for (size_t i = 0; i < size; i++)
        _body.insert(_body.begin(), Snake::BodyPart{x, y});
}

std::vector<std::pair<Snake::BodyPart, std::string>> Snake::dump() const
{
    std::vector<std::pair<Snake::BodyPart, std::string>> res;
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

// Privates Member Functions

bool Snake::checkCollision(int oldX, int oldY)
{
    if (_body[0].x == oldX && _body[0].y == oldY)
        return true;
    for (std::size_t i = 1; i < _body.size(); i++) {
        if (_body[0].x == _body[i].x && _body[0].y == _body[i].y)
            return true;
    }
    return false;
}

std::pair<Snake::BodyPart, std::string> Snake::getDumpHead() const
{
    return std::make_pair(_body[0], _headTextures.at(std::make_tuple(
        _direction.first,
        _direction.second
    )));
}

std::pair<Snake::BodyPart, std::string> Snake::getDumpTail(std::size_t len) const
{
    return std::make_pair(_body[len - 1], _tailTextures.at(std::make_tuple(
            _body[len - 1].x - _body[len - 2].x,
            _body[len - 1].y - _body[len - 2].y
    )));
}

std::pair<Snake::BodyPart, std::string> Snake::getDumpBody(std::size_t i) const
{
    return std::make_pair(_body[i], _bodyTextures.at(std::make_tuple(
        _body[i].x - _body[i - 1].x,
        _body[i].x - _body[i + 1].x,
        _body[i].y - _body[i - 1].y,
        _body[i].y - _body[i + 1].y
    )));
}
