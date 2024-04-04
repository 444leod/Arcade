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
        EMPTY,
        COIN,
        FRUIT,
        WALL,
        PLAYER,
        DOOR,
        GHOST
    };

    inline std::map<TileType, std::string> TileTypeToString = {
        {TileType::VOID, "VOID"},
        {TileType::EMPTY, "EMPTY"},
        {TileType::COIN, "COIN"},
        {TileType::WALL, "WALL"},
        {TileType::FRUIT, "FRUIT"},
        {TileType::PLAYER, "PLAYER"},
        {TileType::DOOR, "DOOR"}
    };

    enum class Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };
    inline std::map<Direction, Vec2i> DirectionToVec2 = {
        {Direction::UP, {0, -1}},
        {Direction::DOWN, {0, 1}},
        {Direction::LEFT, {-1, 0}},
        {Direction::RIGHT, {1, 0}}
    };
    inline std::map<Vec2i, Direction> Vec2ToDirection = {
        {{0, -1},   Direction::UP},
        {{0, 1},    Direction::DOWN},
        {{-1, 0},   Direction::LEFT},
        {{1, 0},    Direction::RIGHT}
    };

    inline std::map<Direction, std::string> DirectionToString = {
        {Direction::UP, "UP"},
        {Direction::DOWN, "DOWN"},
        {Direction::LEFT, "LEFT"},
        {Direction::RIGHT, "RIGHT"},
        {Direction::NONE, "NONE"}
    };

    enum class EntityType {
        GHOST,
        PLAYER
    };
    namespace entity {
        enum class status {
            ALIVE,
            DEAD,
            HUNGRY,
            SCARED
        };
    }
    namespace ghost {
        enum class state {
            CHASE,
            SCATTER,
            FRIGHTENED,
            EATEN,
            DEAD,
        };
        enum class type {
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
    class MapTexturer;
    class Map;

    inline std::ostream& operator<<(std::ostream& os, const Direction& direction) {
        return os << static_cast<int>(direction);
    }
}
