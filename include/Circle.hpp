/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Circle
*/

#pragma once

#include "Shape.hpp"

namespace arc::shape {

    /**
     * @brief Represents a circle shape
     */
    struct Circle {
        double radius;
        arc::Color color = arc::Color::WHITE;
        double rotation = 0;
        struct Outline outline = {0, arc::Color::WHITE};
    };

    namespace advanced {
        class Circle {};
    }
}
