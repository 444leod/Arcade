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
};

template<typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b)
{
    return {a.x + b.x, a.y + b.y};
}

template<typename T>
Vector<T> operator-(const Vector<T>& a, const Vector<T>& b)
{
    return {a.x - b.x, a.y - b.y};
}

#define iVector Vector<int>
#define fVector Vector<float>
