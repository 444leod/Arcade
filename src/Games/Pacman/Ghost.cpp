/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Ghost
*/

#include "Ghost.hpp"
#include "Player.hpp"

using pacman::ghosts::Ghost;

Ghost::Ghost()
{
    _name = "ghost";
}

Ghost::~Ghost()
{
}

void Ghost::queueMove(Direction direction)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = pacman::DirectionToVec2[direction];
        return;
    }
    _moveQueue = {pacman::DirectionToVec2[direction]};
}

void Ghost::queueMove(Vec2i move)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = move;
        return;
    }
    _moveQueue = {move};
}

void Ghost::setMoveQueue(std::vector<Vec2i> moveQueue)
{
    _moveQueue = moveQueue;
}

// void Ghost::move(float deltaTime, MapHandler& map)
// {
//     _elapsed += deltaTime * _speed;
//     _elapsed1 += deltaTime * _speed;
//     while (_elapsed >= 0.2) {
//         _elapsed -= 0.2;
//         if (_elapsed1 >= 1) {
//             Vec2i nextMove = 
//             if (map.isTileWalkable(_pos + nextMove)) {
//                 _lastPos = _pos;
//                 _pos += nextMove;
//                 _direction = nextMove;
//                 _moveQueue.erase(_moveQueue.begin());
//                 return;
//             }
//         }
//         if (map.isTileWalkable(_pos + _direction)) {
//             _lastPos = _pos;
//             _pos += _direction;
//             _posf = Vec2f(_lastPos.x, _lastPos.y);
//         } else {
//             _lastPos = _pos;
//         }
//     }
// }


        // if (_elapsed1 >= 1) {
        //     RandomNumberGenerator rng;
        //     for (auto& ghost : _ghosts) {
        //         ghost->setDirection(pacman::DirectionToVec2[pacman::Direction(rng.generate() % 4)]);
        //     }
        //     _elapsed1 -= 1;
        // }

