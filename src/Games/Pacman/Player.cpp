/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Player
*/

#include "Player.hpp"

using pacman::Direction;
using pacman::player::Player;

void Player::queueMove(Direction direction)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = pacman::DirectionToVec2[direction];
        return;
    }
    _moveQueue = {pacman::DirectionToVec2[direction]};
}

void Player::queueMove(Vec2i move)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = move;
        return;
    }
    _moveQueue = {move};
}

void Player::setMoveQueue(std::vector<Vec2i> moveQueue)
{
    _moveQueue = moveQueue;
}

void Player::setPos(const Vec2i pos)
{
    _pos = pos;
}
