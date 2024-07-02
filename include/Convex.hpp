/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Convex
*/

#pragma once

#include "Shape.hpp"
#include "Vector.hpp"
#include <vector>

namespace arc::shape {

    /**
     * @brief Represents a convex shape
     */
    struct Convex {
        std::vector<dVector> points;
        arc::Color color = arc::Color::WHITE;
        double rotation = 0;
        struct Outline outline = {0, arc::Color::WHITE};
    };
}
