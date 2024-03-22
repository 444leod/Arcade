/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AEntity
*/

#include "IEntity.hpp"
#include "AEntity.hpp"
#include "MapHandler.hpp"
#include "Vec2.hpp"

using pacman::Direction;
using pacman::player::State;
using pacman::AEntity;

Vec2i AEntity::getPos() const
{
    return _pos;
}

// Vec2f AEntity::getPosf() const
// {
//     return _posf;
// }

void AEntity::setPos(Vec2f pos)
{
    _pos = Vec2i(pos.x, pos.y);
    _posf = Vec2f(pos.x, pos.y);
}

void AEntity::setPos(Vec2i pos)
{
    _pos.x = pos.x;
    _pos.y = pos.y;
    _posf.x = pos.x;
    _posf.y = pos.y;
}

void AEntity::setPos(float x, float y)
{
    _pos.x = x;
    _pos.y = y;
    _posf.x = x;
    _posf.y = y;
}

void AEntity::setDirection(Vec2i direction)
{
    _direction = direction;
}

void AEntity::setDirection(Direction direction)
{
    _direction = pacman::DirectionToVec2[direction];
}

Vec2i AEntity::getDirection() const
{
    return _direction;
}

void AEntity::move(float deltaTime, [[maybe_unused]]pacman::MapHandler& map)
{
    _elapsed += deltaTime * _speed;
    while (_elapsed >= 0.2) {
        _elapsed -= 0.2;
        if (_moveQueue.size()) {
            Vec2i nextMove = _moveQueue.front();
            if (map.isTileWalkable(_pos + nextMove)) {
                _pos += nextMove;
                _direction = nextMove;
                _moveQueue.erase(_moveQueue.begin());
                return;
            }
        }
        if (map.isTileWalkable(_pos + _direction)) {
            _pos += _direction;
            return;
        }
    }
}

// void AEntity::movef(float deltaTime, [[maybe_unused]]pacman::MapHandler& map)
// {
//     _elapsedf += deltaTime * _speed;
//     while (_elapsedf >= 0.2) {
//         _elapsedf -= 0.2;
//         if (map.isTileWalkable(_pos + _direction)) {
//             _posf.x += _direction.x * 0.1;
//             _posf.y += _direction.y * 0.1;
//             return;
//         }
//     }
// }

void AEntity::setMoveQueue(std::vector<Vec2i> moveQueue)
{
    _moveQueue = moveQueue;
}

void AEntity::queueMove(Vec2i move)
{
    _moveQueue.push_back(move);
}

void AEntity::queueMove(Direction direction)
{
    _moveQueue.push_back(pacman::DirectionToVec2[direction]);
}

size_t AEntity::getSpeed() const
{
    return _speed;
}
