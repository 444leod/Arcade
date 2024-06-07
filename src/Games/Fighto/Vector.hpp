/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Vector
*/

#pragma once

template<typename T>
class Vector
{
    public:
        Vector(T _x, T _y) : x(_x), y(_y) {}
        ~Vector() = default;
        T x;
        T y;

    public:
        Vector<T> operator+(const Vector<T>& b) const
        { return Vector<T>(this->x + b.x, this->y + b.y); }

        Vector<T> operator-(const Vector<T>& b) const
        { return Vector<T>(this->x - b.x, this->y - b.y); }

        Vector<T> operator*(double factor) const
        { return Vector<T>(this->x * factor, this->y * factor); }
};

#define iVector Vector<int>
#define dVector Vector<double>
