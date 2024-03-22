/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Arcade
*/

#pragma once

class Vec2f {
    public:
        Vec2f(float x, float y) : x(x), y(y) {}
        Vec2f() : x(0), y(0) {}
        ~Vec2f() = default;

        float x;
        float y;

        Vec2f operator+(const Vec2f& other) const
        {
            return Vec2f(x + other.x, y + other.y);
        }

        Vec2f operator-(const Vec2f& other) const
        {
            return Vec2f(x - other.x, y - other.y);
        }

        Vec2f operator*(const float& other) const
        {
            return Vec2f(x * other, y * other);
        }

        Vec2f operator/(const float& other) const
        {
            return Vec2f(x / other, y / other);
        }

        bool operator==(const Vec2f& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vec2f& other) const
        {
            return x != other.x || y != other.y;
        }

        bool operator<(const Vec2f& other) const
        {
            return x < other.x && y < other.y;
        }

        bool operator>(const Vec2f& other) const
        {
            return x > other.x && y > other.y;
        }

        bool operator<=(const Vec2f& other) const
        {
            return x <= other.x && y <= other.y;
        }

        bool operator>=(const Vec2f& other) const
        {
            return x >= other.x && y >= other.y;
        }

        Vec2f& operator+=(const Vec2f& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2f& operator-=(const Vec2f& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

};

class Vec2i {
    public:
        Vec2i(int x, int y) : x(x), y(y) {}
        Vec2i() : x(0), y(0) {}
        ~Vec2i() = default;

        int x;
        int y;

        Vec2i operator+(const Vec2i& other) const
        {
            return Vec2i(x + other.x, y + other.y);
        }

        Vec2i operator-(const Vec2i& other) const
        {
            return Vec2i(x - other.x, y - other.y);
        }

        Vec2i operator*(const int& other) const
        {
            return Vec2i(x * other, y * other);
        }

        Vec2i operator/(const int& other) const
        {
            return Vec2i(x / other, y / other);
        }

        bool operator==(const Vec2i& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vec2i& other) const
        {
            return x != other.x || y != other.y;
        }

        bool operator<(const Vec2i& other) const
        {
            return x < other.x && y < other.y;
        }

        bool operator>(const Vec2i& other) const
        {
            return x > other.x && y > other.y;
        }

        bool operator<=(const Vec2i& other) const
        {
            return x <= other.x && y <= other.y;
        }

        bool operator>=(const Vec2i& other) const
        {
            return x >= other.x && y >= other.y;
        }

        Vec2i& operator+=(const Vec2i& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2i& operator-=(const Vec2i& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }
};
