/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AAnimation
*/

#include "AAnimation.hpp"
#include <iostream>

AAnimation::AAnimation(const std::string& texture)
    : _texture(texture)
{
    _frame = _texture + "_0";
}

void AAnimation::draw(arc::ILibrary& lib, const dVector& position, double direction) const
{
    if (_direction.value_or(direction) < 0)
        lib.display().draw(lib.textures().get(_frame), position.x + 2 - 0.5f, position.y - 1 + 0.3f, -2, 2);
    else
        lib.display().draw(lib.textures().get(_frame), position.x - 0.5f, position.y - 1 + 0.3f, 2, 2);
}

void AAnimation::debug([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]]const dVector& position) const
{
    // lib.display().draw(lib.textures().get("debug"), position.x, position.y, 1, 1);
}

bool AAnimation::update([[maybe_unused]] double dt)
{
    return true;
}
