/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IEntity
*/

#pragma once

#include <utility>
#include <vector>
#include "../include/OpenPacman.hpp"
#include "ITextureManager.hpp"

namespace pacman {
    class IEntity {
        public:
            IEntity() = default;
            ~IEntity() = default;

            virtual Vec2i getPos() const = 0;
            virtual Vec2f getPosf() const = 0;
            virtual void setPos(Vec2f pos) = 0;
            virtual void setPos(Vec2i pos) = 0;
            virtual void setPos(float x, float y) = 0;
            virtual void setPosf(Vec2i pos) = 0;

            virtual void setDirection(Vec2i direction) = 0;
            virtual void setDirection(Direction direction) = 0;
            virtual Vec2i getDirection() const = 0;

            virtual void move(float deltaTime, pacman::MapHandler& map) = 0;
            virtual void movef(float deltaTime, pacman::MapHandler& map) = 0;

            virtual void setMoveQueue(std::vector<Vec2i> moveQueue) = 0;
            virtual void queueMove(Vec2i move) = 0;
            virtual void queueMove(Direction direction) = 0;

            virtual size_t getSpeed() const = 0;

            virtual void initTextures(arc::ITextureManager& manager) = 0;
            virtual std::map<pacman::Direction, std::vector<std::string>> getTextures() const = 0;
            virtual std::string getTexture(uint16_t tick) = 0;

            virtual void setHealth(float health) = 0; 
            virtual void setDmg(float dmg) = 0;

            virtual float getHealth() = 0;
            virtual float getDmg() = 0;

            virtual std::string getName() const = 0;

            virtual pacman::entity::status getStatus() const = 0;
            virtual void setStatus(pacman::entity::status status) = 0;
        protected:
        private:
    };
}
