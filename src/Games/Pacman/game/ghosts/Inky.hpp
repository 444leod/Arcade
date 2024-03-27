/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Inky
*/

#pragma once

#include "../Ghost.hpp"

namespace pacman {
    namespace ghosts {
        class Inky : public Ghost {
            public:
                Inky();
                ~Inky() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
