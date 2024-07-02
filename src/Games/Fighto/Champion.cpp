/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Champion
*/

#include "Champion.hpp"
#include "Physics.hpp"
#include "Animations/AnimationsList.hpp"

#include <cmath>
#include <iostream>

Champion::Champion(std::uint32_t id, const std::string& texture)
    : _id(id), _texture(texture), _animation(std::make_shared<animation::Idle>(texture))
{
}

void Champion::draw(arc::ILibrary& lib) const
{
    if (_animation != nullptr)
        _animation->draw(lib, this->_position, this->_direction);
    // lib.display().draw(lib.textures().get(this->_texture + std::to_string(frame)), this->_position.x, this->_position.y, (this->_direction < 0) ? -1 : 1);

    if (!this->_alive)
        return;
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

    arc::shape::Rectangle rect = {
        .width = 1,
        .height = 1,
        .color = arc::Color::TRANSPARENT,
    };
    rect.color.alpha = 50;
    rect.outline.thickness = 1;
    rect.outline.color = arc::Color::RED;
    lib.display().draw(rect, this->_position.x, this->_position.y);
}

void Champion::input(dVector input)
{
    if (!this->_alive || this->_stagger > 0.0)
        return;
    this->_input = input;
    if (input.x != 0.0) {
        this->_direction = input.x;
        if (this->_grounded)
            this->_animation = std::make_shared<animation::Run>(this->_texture);
    } else {
        if (this->_grounded)
            this->_animation = std::make_shared<animation::Idle>(this->_texture);
    }
}

void Champion::input(arc::JoystickButton button)
{
    if (_moveQueue.size() >= 2)
        return;
    switch (button)
    {
        case arc::JoystickButton::Cross:
            if (this->_grounded) {
                this->_velocity.y = this->_jumpforce;
                this->_animation = std::make_shared<animation::Jump>(this->_texture, this->_velocity);
            }
            break;
        case arc::JoystickButton::Square:
            this->_moveQueue.push(std::make_shared<move::Jab>(this->_id, this->_direction));
            this->_animation = std::make_shared<animation::Jab>(this->_texture, this->_direction);
            break;
        case arc::JoystickButton::Circle:
            if (this->_grounded)
                this->_moveQueue.push(std::make_shared<move::Kick>(this->_id, this->_direction));
            else {
                this->_moveQueue.push(std::make_shared<move::Spike>(this->_id, this->_direction));
                this->_speed = this->_maxspeed * 0.1;
                this->_velocity.y = GRAVITY * -5;
            }
        default:
            break;
    }
}

void Champion::update(double dt)
{
    bool done = this->_animation->update(dt);
    if (!this->_alive) return;
    if (this->_stagger > 0) this->_stagger -= dt;

    if (done && (!this->_animation->needGround() || this->_grounded)) {
        if (this->_input.x != 0.0) {
            this->_direction = this->_input.x;
            this->_animation = std::make_shared<animation::Run>(this->_texture);
        } else {
            this->_animation = std::make_shared<animation::Idle>(this->_texture);
        }
    }

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
    this->_speed = this->_grounded ? this->_maxspeed : this->_maxspeed * 0.75;

    if (!this->_moveQueue.empty() && this->_stagger <= 0.0) {
        // Update attack move

        // update the animation based on the current move executed
        if (!this->_moveQueue.front()->animate()) {
            this->_animation = this->_moveQueue.front()->animation(this->_texture);
            // for not implemented yet animations
            if (this->_animation == nullptr)
                this->_animation = std::make_shared<animation::Idle>(this->_texture);
        }
        bool pop = !this->_moveQueue.front()->update(
            this->_position + this->_size * 0.5, this->_grounded, dt);
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
    if (this->_lifepoints <= 0.f) {
        this->_alive = false;
        this->_animation = std::make_shared<animation::Death>(this->_texture);
    } else
        this->_animation = std::make_shared<animation::Hurt>(this->_texture);
}

std::shared_ptr<AMove> Champion::move() const
{
    if (this->_moveQueue.empty())
        return nullptr;
    return this->_moveQueue.front();
}
