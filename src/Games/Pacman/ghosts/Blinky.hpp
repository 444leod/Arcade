/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Blinky
*/

#pragma once

#include "../AEntity.hpp"

namespace pacman {
    namespace ghosts {
        class Blinky : public AEntity {
            public:
                Blinky();
                ~Blinky() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
