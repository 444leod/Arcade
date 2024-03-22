/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Ghost
*/

#pragma once

#include "Pacman.hpp"
#include "./AEntity.hpp"

namespace pacman {
    namespace ghosts {
        class Ghost : public pacman::AEntity {
            public:
                Ghost();
                ~Ghost();

                // void move(float deltaTime, MapHandler& map) override;

                void queueMove(Direction direction) override;
                void queueMove(Vec2i move) override;
                void setMoveQueue(std::vector<Vec2i> moveQueue) override;

            protected:
            private:
                uint16_t _elapsed1 = 0;
        };
    };
};
