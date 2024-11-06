/*
** EPITECH PROJECT, 2024
** Rect.hpp
** File description:
** Rect.hpp
*/

#pragma once

#include "Shape.hpp"

namespace arc {
    /**
     * @brief Represents a rectangle
     */
    template<typename T>
    struct Rect {
        T x;
        T y;
        T width;
        T height;
    };

    namespace shape {

        /**
         * @brief Represents a rectangle shape
         */
        struct Rectangle {
            double width;
            double height;
            arc::Color color = arc::Color::WHITE;
            double rotation = 0;
            struct Outline outline = {0, arc::Color::WHITE};
        };
    }
}
