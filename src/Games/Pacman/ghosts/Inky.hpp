/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Inky
*/

#pragma once

#include "../AEntity.hpp"

namespace pacman {
    namespace ghosts {
        class Inky : public AEntity {
            public:
                Inky();
                ~Inky() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
