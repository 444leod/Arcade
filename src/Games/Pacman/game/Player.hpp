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
                void initTextures(arc::ITextureManager& manager) override;
                void queueMove(Vec2i move) override;
                void setMoveQueue(std::vector<Vec2i> moveQueue) override;

            protected:
            private:
        };
    };
};
