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
    };
}
