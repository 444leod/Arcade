/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** AEntity
*/

#pragma once

#include "IEntity.hpp"
#include "MapHandler.hpp"
#include "IGame.hpp"
#include "ITextureManager.hpp"

using pacman::MapHandler;

namespace pacman {
    class AEntity : public IEntity {
        public:
            AEntity() = default;
            ~AEntity() = default;

            virtual vec2i getPos() const override;
            virtual vec2f getPosf() const override;
            virtual void setPos(vec2f pos) override;
            virtual void setPos(vec2i pos) override;
            virtual void setPos(float x, float y) override;
            virtual void setPosf(vec2i pos) override;

            virtual void setDirection(vec2i direction) override;
            virtual void setDirection(Direction direction) override;
            virtual vec2i getDirection() const override;

            virtual void move(float deltaTime, MapHandler& map) override;
            virtual void movef(float deltaTime, MapHandler& map);

            virtual void setMoveQueue(std::vector<vec2i> moveQueue) override;
            virtual void queueMove(vec2i move) override;
            virtual void queueMove(Direction direction) override;

            virtual size_t getSpeed() const override;

            virtual void initTextures(arc::ITextureManager& manager) override;
            virtual std::map<pacman::Direction, std::vector<std::string>> getTextures() const override;
            virtual std::string getTexture(uint16_t tick) override;

            virtual std::string getName() const override;

        protected:
            std::string _name = "entity";
            vec2i _pos = {0, 0};
            vec2i _lastPos = {0, 0};
            vec2f _posf = {0, 0};
            vec2i _direction = {0, 0};
            std::vector<vec2i> _moveQueue = {};
            float _speed = 1;
            float _elapsed = 0;
            float _elapsedf = 0;
            std::map<pacman::Direction, std::vector<std::string>> _textures = {};
        private:
    };
}
