/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SnakeObject
*/

#include <vector>
#include <string>

#include "Snake.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

#include <iostream>

Snake::Snake()
{
    _direction = std::make_pair(1, 0);
    _oldDirection = std::make_pair(1, 0);
    for (int i = 0; i < 4; i++)
        _body.push_back(Vec2i {(ARENA_WIDTH + 1) / 2 - i, (ARENA_HEIGHT + 1) / 2});
}
