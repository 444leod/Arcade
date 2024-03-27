/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** AEntity
*/

#pragma once

#include "IEntity.hpp"
#include "IGame.hpp"
#include "ITextureManager.hpp"

namespace pacman {
    class AEntity : public IEntity {
        public:
            AEntity() : _id(_idCounter++) {};
            ~AEntity() = default;

            virtual Vec2i getPos() const override;
            virtual Vec2f getPosf() const override;
            virtual void setPos(Vec2f pos) override;
            virtual void setPos(Vec2i pos) override;
            virtual void setPos(float x, float y) override;
            virtual void setPosf(Vec2i pos) override;

            virtual void setDirection(Vec2i direction) override;
            virtual void setDirection(Direction direction) override;
            virtual Vec2i getDirection() const override;

            virtual void move(float deltaTime, std::shared_ptr<pacman::Map> map) override;
            virtual void movef(float deltaTime) override;

            virtual void setMoveQueue(std::vector<Vec2i> moveQueue) override;
            virtual void queueMove(Vec2i move) override;
            virtual void queueMove(Direction direction) override;

            virtual float getSpeed() const override;
            virtual void setSpeed(float speed) override;

            virtual void initTextures(arc::ITextureManager& manager) override;
            virtual std::map<pacman::Direction, std::vector<std::string>> getTextures() const override;
            virtual std::string getTexture(uint16_t tick) override;

            virtual std::string getName() const override;
            virtual uint64_t getId() const override;

            virtual pacman::entity::status getStatus() const override;
            virtual void setStatus(pacman::entity::status status) override;

            virtual void updateWalkableTiles(pacman::TileType type, bool walkable) override;

            virtual bool operator==(const IEntity& other) const override;
        protected:
            static uint64_t _idCounter;
            uint64_t _id = 0;
            std::string _name = "entity";
            Vec2i _pos = {0, 0};
            Vec2i _lastPos = {0, 0};
            Vec2i _nextPos = {0, 0};
            Vec2f _posf = {0, 0};
            Vec2i _direction = {0, 0};
            std::vector<Vec2i> _moveQueue = {};
            float _speed = 1;
            float _elapsed = 0;
            float _elapsedf = 0;
            std::map<pacman::Direction, std::vector<std::string>> _textures = {};
            pacman::entity::status _status = pacman::entity::status::ALIVE;
            std::map<pacman::TileType, bool> _walkableTiles = {
                {pacman::TileType::COIN, true},
                {pacman::TileType::EMPTY, true},
                {pacman::TileType::FRUIT, true},
                {pacman::TileType::DOOR, false},
                {pacman::TileType::VOID, false},
                {pacman::TileType::WALL, false}
            };
        private:
    };
    inline uint64_t pacman::AEntity::_idCounter = 0;
};
