/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Blinky
*/

#pragma once

#include "../Ghost.hpp"

namespace pacman {
    namespace ghosts {
        class Blinky : public Ghost {
            public:
                Blinky();
                ~Blinky() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
