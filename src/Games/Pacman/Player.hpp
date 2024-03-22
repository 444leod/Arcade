/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Player
*/

#pragma once

#include "Pacman.hpp"
#include "./AEntity.hpp"

namespace pacman {
    namespace player {
        class Player : public pacman::AEntity {
            public:
                Player();
                ~Player() = default;

                void queueMove(Direction direction) override;
                void queueMove(vec2i move) override;
                void setMoveQueue(std::vector<vec2i> moveQueue) override;

                void initTextures(arc::ITextureManager& manager) override;

            protected:
            private:
        };
    };
};
