/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Champion
*/

#include "Champion.hpp"
#include "Physics.hpp"

Champion::Champion()
{
}

Champion::~Champion()
{
}

void Champion::draw(arc::ILibrary& lib) const
{
    lib.display().draw(lib.textures().get("player"), this->_postion.x, this->_postion.y);
}

void Champion::input(float xaxis, bool jump)
{
    if (xaxis != 0)
        this->_velocity.x = xaxis * this->_maxspeed;
    if (jump && this->_grounded)
        this->_velocity.y = this->_jumpforce;
}

void Champion::update(float dt)
{
    this->_postion.x += this->_velocity.x * dt;
    this->_postion.y -= this->_velocity.y * dt; // -= because down is technically inverted

    this->_velocity.y -= GRAVITY; // falling faster and faster
    // do not fall under a certain height
    if (this->_postion.y >= FLOOR) {
        this->_postion.y = FLOOR;
        this->_velocity.y = 0.f;
    }
    // if approximately at ground level
    this->_grounded = std::abs(_postion.y - 14.f) < 0.01f;
}
