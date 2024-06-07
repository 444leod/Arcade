/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AMove
*/

#include "AMove.hpp"

AMove::AMove(double dmg, double kb, double stu, double act, double lag, bool air)
    : _damage(dmg), _knockback(kb), _startup(stu), _active(act), _lag(lag), _air(air)
{
}

bool AMove::update(double direction, dVector pos, bool grounded, double dt)
{
    this->_time += dt;
    if (this->_time >= this->_startup + this->_active + this->_lag)
        return false;
    if (this->_time >= this->_startup + this->_active)
        return true;
    if (this->_time <= this->_startup)
        return true;
    if (grounded && this->_air)
        { this->interrupt(); return true; }
    for (const auto& hb : this->_hitboxes) {
        dVector p(hb.position().x * direction, hb.position().y);
        this->_poll.push_back(HitBox(p + pos, hb.radius()));
    }
    return true;
}

bool AMove::poll(HitBox& hitbox)
{
    if (this->_time >= this->_startup + this->_active + this->_lag)
        return false;
    if (this->_time <= this->_startup)
        return false;
    if (this->_poll.empty())
        return false;
    hitbox = this->_poll.back();
    this->_poll.pop_back();
    return true;
}

void AMove::debug(arc::ILibrary& lib) const
{
    for (const auto& hb : this->_poll) {
        lib.display().draw(lib.textures().get("hit"),
            hb.position().x - hb.radius(),
            hb.position().y - hb.radius(),
            hb.radius() * 2.f);
    }
}

void AMove::interrupt()
{
    this->_time = this->_startup + this->_active;
}

bool AMove::hasHit(std::uint32_t id) const
{
    auto f = std::find(this->_hitIds.begin(), this->_hitIds.end(), id);
    return f != this->_hitIds.end();
}

