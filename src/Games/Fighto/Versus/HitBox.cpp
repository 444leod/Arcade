/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** HitBox
*/

#include "HitBox.hpp"

HitBox::HitBox(dVector position, double radius)
    : _position(position), _radius(radius)
{
}

bool HitBox::overlaps(const HitBox& other) const
{
    dVector pos = this->_position - other.position();
    double r = this->_radius + other.radius();
    return (r * r > pos.x * pos.x + pos.y * pos.y);
}

bool HitBox::overlaps(dVector pos, dVector size) const
{
    dVector edge = this->_position;

    if (this->_position.x < pos.x) edge.x = pos.x;
    else if (this->_position.x > pos.x + size.x) edge.x = pos.x + size.x;

    if (this->_position.y < pos.y) edge.y = pos.y;
    else if (this->_position.y > pos.y + size.y) edge.y = pos.y + size.y;

    auto delta = this->_position - edge;
    auto dist = delta.x * delta.x + delta.y * delta.y;
    return dist < (this->_radius * this->_radius);
}
