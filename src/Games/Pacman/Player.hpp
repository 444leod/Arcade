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
                Player() = default;
                ~Player() = default;

                void queueMove(Direction direction) override;
                void queueMove(Vec2i move) override;
                void setMoveQueue(std::vector<Vec2i> moveQueue) override;
                void setPos(const Vec2i pos) override;

            protected:
            private:
        };
    };
};
