/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#pragma once

#include <map>
#include <string>
#include "Vec2.hpp"

namespace pacman {
    enum class TileType {
        VOID,
        COIN,
        WALL,
        FRUIT,
        PLAYER
    };

    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    inline std::map<Direction, Vec2i> DirectionToVec2 = {
        {Direction::UP, {0, -1}},
        {Direction::DOWN, {0, 1}},
        {Direction::LEFT, {-1, 0}},
        {Direction::RIGHT, {1, 0}}
    };

    enum class EntityType {
        GHOST,
        PLAYER
    };
    namespace Ghost {
        enum class State {
            CHASE,
            SCATTER,
            FRIGHTENED,
            EATEN,
            DEAD,
        };
        enum class Type {
            BLINKY,
            PINKY,
            INKY,
            CLYDE
        };
    }
    class IEntity;
    class AEntity;
    namespace player {
        enum class State {
            ALIVE,
            DEAD,
            HUNGRY
        };
        class Player;
    }
    class MapHandler;
}
