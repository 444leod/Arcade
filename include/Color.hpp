/*
** EPITECH PROJECT, 2024
** Arcade-Commons
** File description:
** Datatypes
*/

#pragma once

#include <cstdint>

namespace arc {
    /**
     * @brief Represents a color
     */
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;

        static const Color WHITE;
        static const Color BLACK;
        static const Color GREEN;
        static const Color BLUE;
        static const Color RED;
        static const Color ORANGE;
        static const Color YELLOW;
        static const Color PURPLE;
        static const Color PINK;
        static const Color CYAN;
        static const Color BROWN;
        static const Color GREY;
        static const Color TRANSPARENT;
    };

    inline const Color Color::WHITE = {255, 255, 255, 255};
    inline const Color Color::BLACK = {0, 0, 0, 255};
    inline const Color Color::GREEN = {0, 255, 0, 255};
    inline const Color Color::BLUE = {0, 0, 255, 255};
    inline const Color Color::RED = {255, 0, 0, 255};
    inline const Color Color::ORANGE = {255, 165, 0, 255};
    inline const Color Color::YELLOW = {255, 255, 0, 255};
    inline const Color Color::PURPLE = {128, 0, 128, 255};
    inline const Color Color::PINK = {255, 192, 203, 255};
    inline const Color Color::CYAN = {0, 255, 255, 255};
    inline const Color Color::BROWN = {165, 42, 42, 255};
    inline const Color Color::GREY = {128, 128, 128, 255};
    inline const Color Color::TRANSPARENT = {0, 0, 0, 0};
}
