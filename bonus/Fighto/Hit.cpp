/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Hit
*/

#include "Hit.hpp"

Hit::Hit(float damage, fVector position, fVector size, Champion& source) :
    _damage(damage), _position(position), _size(size), _source(source),
    _cornerA(position), _cornerB(position + size)
{
}

Hit::~Hit()
{
}

bool Hit::overlaps(const Champion& other) const
{
    if (this->_source == other)
        return false;
    auto a = other.position();
    auto b = other.position() + other.size();

    if (b.x < this->_cornerA.x) // Body is too far left
        return false;
    if (a.x > this->_cornerB.x) // Body is too far right
        return false;

    if (b.y < this->_cornerA.y) // Body is too high
        return false;
    if (a.y > this->_cornerB.y) // Body is too low
        return false;

    return true;
}
