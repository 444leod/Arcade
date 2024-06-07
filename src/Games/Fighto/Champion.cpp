/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Champion
*/

#include "Champion.hpp"
#include "Physics.hpp"

#include <cmath>
#include <iostream>

Champion::Champion(arc::Color color) : _color(color)
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
    lib.display().print(str, lib.fonts().get("font"), center, this->_position.y - this->_size.y * 1.5);
}

void Champion::debug(arc::ILibrary& lib) const
{
    if (!this->_moveQueue.empty()) {
        this->_moveQueue.front()->debug(lib);
    }
}

void Champion::input(dVector input)
{
    if (!this->_alive || !this->_moveQueue.empty() || this->_stagger > 0)
        return;
    this->_input = input;
    if (input.x != 0.0) this->_direction = input.x;
}

void Champion::input(arc::JoystickButton button)
{
    if (_moveQueue.size() >= 2)
        return;
    switch (button)
    {
        case arc::JoystickButton::Cross:
            if (this->_grounded)
                this->_velocity.y = this->_jumpforce;
            break;
        case arc::JoystickButton::Square:
            this->_moveQueue.push(std::make_shared<Jab>());
            break;
        case arc::JoystickButton::Circle:
            if (this->_grounded)
                this->_moveQueue.push(std::make_shared<Kick>());
            else {
                this->_moveQueue.push(std::make_shared<Spike>());
                this->_speed = this->_maxspeed * 0.1;
                this->_velocity.y = GRAVITY * -5;
            }
        default:
            break;
    }
}

void Champion::update(double dt)
{
    if (!this->_alive) return;
    if (this->_stagger > 0) this->_stagger -= dt;

    // Can always fall
    this->_position.y -= this->_velocity.y * dt;
    this->_velocity.y -= GRAVITY; // falling faster and faster
    // do not fall under a certain height
    if (this->_position.y >= FLOOR) {
        this->_position.y = FLOOR;
        this->_velocity.y = 0.f;
    }
    // if approximately at ground level
    this->_grounded = std::abs(_position.y - FLOOR) < 0.01f;
    this->_speed = this->_grounded ? this->_maxspeed : this->_maxspeed * 0.5;

    if (!this->_moveQueue.empty() && this->_stagger <= 0.0) {

        // Update attack move
        bool pop = !this->_moveQueue.front()->update(
            this->_direction, this->_position + this->_size * 0.5,
            this->_grounded, dt);
        if (pop) this->_moveQueue.pop();

    } else {

        double t = this->_acceleration;
        if (this->_stagger > 0 && this->_grounded)  t = 0.10;
        else if (this->_stagger > 0)                t = 0.01;

        this->_velocity.x = std::lerp(this->_velocity.x, this->_speed * this->_input.x, t);
        this->_position.x += this->_velocity.x * dt;

    }
}

void Champion::damage(double damage, dVector knockback, double stagger)
{
    // Take damage
    this->_lifepoints -= damage;
    // Cancel all moves
    while (!this->_moveQueue.empty()) // could add super-armour here
        this->_moveQueue.pop();
    // Get knockback
    this->_velocity = knockback;
    this->_input = dVector(0.0, 0.0);
    this->_stagger = stagger;
    if (this->_lifepoints <= 0.f)
        this->_alive = false;
}

std::shared_ptr<AMove> Champion::move() const
{
    if (this->_moveQueue.empty())
        return nullptr;
    return this->_moveQueue.front();
}
