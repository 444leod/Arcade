/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#pragma once

#include <map>
#include <string>

namespace pacman {
    enum class TileType {
        VOID,
        COIN,
        WALL,
        FRUIT,
        PLAYER
    };
    class vec2f {
        public:
            vec2f(float x, float y) : x(x), y(y) {}
            vec2f() : x(0), y(0) {}
            ~vec2f() = default;

            float x;
            float y;

            vec2f operator+(const vec2f& other) const
            {
                return vec2f(x + other.x, y + other.y);
            }

            vec2f operator-(const vec2f& other) const
            {
                return vec2f(x - other.x, y - other.y);
            }

            vec2f operator*(const float& other) const
            {
                return vec2f(x * other, y * other);
            }

            vec2f operator/(const float& other) const
            {
                return vec2f(x / other, y / other);
            }

            bool operator==(const vec2f& other) const
            {
                return x == other.x && y == other.y;
            }

            bool operator!=(const vec2f& other) const
            {
                return x != other.x || y != other.y;
            }

            bool operator<(const vec2f& other) const
            {
                return x < other.x && y < other.y;
            }

            bool operator>(const vec2f& other) const
            {
                return x > other.x && y > other.y;
            }

            bool operator<=(const vec2f& other) const
            {
                return x <= other.x && y <= other.y;
            }

            bool operator>=(const vec2f& other) const
            {
                return x >= other.x && y >= other.y;
            }

            vec2f& operator+=(const vec2f& other)
            {
                x += other.x;
                y += other.y;
                return *this;
            }

            vec2f& operator-=(const vec2f& other)
            {
                x -= other.x;
                y -= other.y;
                return *this;
            }

    };

    class vec2i {
        public:
            vec2i(int x, int y) : x(x), y(y) {}
            vec2i() : x(0), y(0) {}
            ~vec2i() = default;

            int x;
            int y;

            vec2i operator+(const vec2i& other) const
            {
                return vec2i(x + other.x, y + other.y);
            }

            vec2i operator-(const vec2i& other) const
            {
                return vec2i(x - other.x, y - other.y);
            }

            vec2i operator*(const int& other) const
            {
                return vec2i(x * other, y * other);
            }

            vec2i operator/(const int& other) const
            {
                return vec2i(x / other, y / other);
            }

            bool operator==(const vec2i& other) const
            {
                return x == other.x && y == other.y;
            }

            bool operator!=(const vec2i& other) const
            {
                return x != other.x || y != other.y;
            }

            bool operator<(const vec2i& other) const
            {
                return x < other.x && y < other.y;
            }

            bool operator>(const vec2i& other) const
            {
                return x > other.x && y > other.y;
            }

            bool operator<=(const vec2i& other) const
            {
                return x <= other.x && y <= other.y;
            }

            bool operator>=(const vec2i& other) const
            {
                return x >= other.x && y >= other.y;
            }

            vec2i& operator+=(const vec2i& other)
            {
                x += other.x;
                y += other.y;
                return *this;
            }

            vec2i& operator-=(const vec2i& other)
            {
                x -= other.x;
                y -= other.y;
                return *this;
            }
    };

    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    inline std::map<Direction, vec2i> DirectionToVec2 = {
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
