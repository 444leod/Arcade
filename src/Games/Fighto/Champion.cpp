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
    lib.display().draw(lib.textures().get("player"), this->_position.x, this->_position.y);

    const std::string& str = std::to_string(static_cast<int>(this->_lifepoints)) + "%";
    float width = lib.display().measure(str, lib.fonts().get("font"), 0, 0).width;
    float center = this->_position.x + this->_size.x / 2.f - width / 2.f;
    lib.display().print(str, lib.fonts().get("font"), center, this->_position.y - this->_size.y);
}

void Champion::input(float xaxis, int yaxis)
{
    if (!this->_alive) return;

    this->_velocity.x = xaxis * this->_maxspeed;
    if (yaxis > 0 && this->_grounded)
        this->_velocity.y = this->_jumpforce;
    if (yaxis < 0 && this->_grounded)
        this->_velocity.x = 0;
}

void Champion::input(HitResolver& hits)
{
    if (!this->_alive) return;
    if (this->_inputlag > 0.f) return;

    float normalized = this->_velocity.x == 0.f ? 0.f : this->_velocity.x / std::abs(this->_velocity.x);
    fVector offset = { this->_size.x * normalized, 0.f };
    if (normalized == 0.f) offset.y -= this->_size.y;

    Hit hit(25.f, this->_position + offset, this->_size, *this);
    hits.add(hit);
    this->_inputlag = 0.25f;
}

void Champion::update(float dt)
{
    if (!this->_alive) return;

    this->_position.x += this->_velocity.x * dt;
    this->_position.y -= this->_velocity.y * dt;

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
