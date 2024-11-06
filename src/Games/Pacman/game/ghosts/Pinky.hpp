/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Pinky
*/

#pragma once

#include "../Ghost.hpp"

namespace pacman {
    namespace ghosts {
        class Pinky : public Ghost {
            public:
                Pinky();
                ~Pinky() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
