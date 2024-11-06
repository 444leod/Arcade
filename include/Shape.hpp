/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Shape
*/

#pragma once

#include "Color.hpp"

namespace arc::shape {
    struct Outline {
        double thickness;
        arc::Color color = arc::Color::WHITE;
    };
}
