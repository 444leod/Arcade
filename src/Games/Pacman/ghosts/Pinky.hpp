/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Pinky
*/

#pragma once

#include "../AEntity.hpp"

namespace pacman {
    namespace ghosts {
        class Pinky : public AEntity {
            public:
                Pinky();
                ~Pinky() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
