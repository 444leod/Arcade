/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IEntity
*/

#pragma once

#include <utility>
#include <vector>
#include "Pacman.hpp"
#include "MapHandler.hpp"

using pacman::MapHandler;

namespace pacman {
    class IEntity {
        public:
            IEntity() = default;
            ~IEntity() = default;

            virtual vec2i getPos() const = 0;
            // virtual vec2f getPosf() const = 0;
            virtual void setPos(vec2f pos) = 0;
            virtual void setPos(vec2i pos) = 0;
            virtual void setPos(float x, float y) = 0;

            virtual void setDirection(vec2i direction) = 0;
            virtual void setDirection(Direction direction) = 0;
            virtual vec2i getDirection() const = 0;

            virtual void move(float deltaTime, MapHandler& map) = 0;
            // virtual void movef(float deltaTime, MapHandler& map) = 0;

            virtual void setMoveQueue(std::vector<vec2i> moveQueue) = 0;
            virtual void queueMove(vec2i move) = 0;
            virtual void queueMove(Direction direction) = 0;

            virtual size_t getSpeed() const = 0;

        protected:
        private:
    };
}
