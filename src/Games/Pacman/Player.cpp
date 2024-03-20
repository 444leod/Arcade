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
    if (_direction == vec2i(0, 0)) {
        _direction = pacman::DirectionToVec2[direction];
        return;
    }
    _moveQueue = {pacman::DirectionToVec2[direction]};
}

void Player::queueMove(vec2i move)
{
    if (_direction == vec2i(0, 0)) {
        _direction = move;
        return;
    }
    _moveQueue = {move};
}

void Player::setMoveQueue(std::vector<vec2i> moveQueue)
{
    _moveQueue = moveQueue;
}

void Player::setPos(const vec2i pos)
{
    _pos = pos;
}
