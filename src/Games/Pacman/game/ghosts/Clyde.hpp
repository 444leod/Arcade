/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Clyde
*/

#pragma once

#include "../Ghost.hpp"

namespace pacman {
    namespace ghosts {
        class Clyde : public Ghost {
            public:
                Clyde();
                ~Clyde() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
