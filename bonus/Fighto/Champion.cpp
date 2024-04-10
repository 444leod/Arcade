/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Champion
*/

#include "Champion.hpp"
#include "Physics.hpp"

Champion::Champion(id_t id) : _id(id)
{
}

Champion::~Champion()
{
}

void Champion::draw(arc::ILibrary& lib) const
{
    if (!this->_alive) return;
    lib.display().draw(lib.textures().get("player" + std::to_string(this->_id)), this->_position.x, this->_position.y);

    const std::string& str = std::to_string(static_cast<int>(this->_lifepoints)) + "%";
    float width = lib.display().measure(str, lib.fonts().get("font"), 0, 0).width;
    float center = this->_position.x + this->_size.x / 2.f - width / 2.f;
    lib.display().print(str, lib.fonts().get("font"), center, this->_position.y - 1.5f);
}

#include <iostream>

void Champion::input()
{
    if (!this->_alive || !this->_grounded) return;

    this->_velocity.y = this->_jumpforce;
}

void Champion::input(float xaxis, bool remove)
{
    if (!this->_alive) return;

    float acceleration = xaxis * this->_maxspeed * (remove ? -1 : +1);
    if (this->_velocity.x != acceleration)
    this->_velocity.x += acceleration;

    if (this->_velocity.x != 0.f)
        this->_facing = this->_velocity.x / std::abs(this->_velocity.x);
}

void Champion::input(HitResolver& hits)
{
    if (!this->_alive) return;
    if (this->_inputlag > 0.f) return;

    fVector offset = { this->_size.x * this->_facing, 0.f };

    Hit hit(25.f, this->_position + offset, this->_size, *this);
    hits.add(hit);
    this->_inputlag = 0.25f;
}

void Champion::update(float dt)
{
    if (!this->_alive) return;

    this->_position.x += this->_velocity.x * dt;
    this->_position.y -= this->_velocity.y * dt; // -= because down is technically inverted

    this->_velocity.y -= GRAVITY; // falling faster and faster
    // do not fall under a certain height
    if (this->_position.y >= FLOOR) {
        this->_position.y = FLOOR;
        this->_velocity.y = 0.f;
    }
    // if approximately at ground level
    this->_grounded = std::abs(_position.y - 14.f) < 0.01f;

    if (this->_inputlag > 0.f) this->_inputlag -= dt;
}

void Champion::damage(float amount)
{
    this->_lifepoints -= amount;
    if (this->_lifepoints <= 0.f)
        this->_alive = false;
}
