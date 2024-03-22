/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Clyde
*/

#pragma once

#include "../AEntity.hpp"

namespace pacman {
    namespace ghosts {
        class Clyde : public AEntity {
            public:
                Clyde();
                ~Clyde() = default;

                void initTextures(arc::ITextureManager& manager) override;
        };
    }
}
