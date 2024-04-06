/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Champion
*/

#include "Champion.hpp"

Champion::Champion()
{
}

Champion::~Champion()
{
}

void Champion::draw(arc::ILibrary& lib) const
{
    lib.display().draw(lib.textures().get(""), this->_postion.x, this->_postion.y);
}

void Champion::input(uint8_t xaxis, bool jump)
{
    if (xaxis != 0) {
        // Do not accelerate if you're going max speed
        this->_velocity.x += std::abs(this->_velocity.x) < this->_maxspeed ? xaxis * this->_acceleration : 0;
        this->_accelerating = true;
    }

    if (jump)
        this->_velocity.y = this->_jumpforce;
}

void Champion::update(float dt)
{
    this->_postion.x += this->_velocity.x * dt;
    this->_postion.y += this->_velocity.y * dt;

    this->_velocity.y -= 0.5f;
    // do not fall under a certain height
    if (this->_postion.y <= 2.f) {
        this->_postion.y = 2.f;
        this->_velocity.y = 0.f;
    }

    if (!this->_accelerating)
        this->_velocity.x -= this->_velocity.x > 0 ? 0.5f : -0.5f;
    this->_accelerating = false;
}
