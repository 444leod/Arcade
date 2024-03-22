/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** AGameObject
*/

#include "SnakeLib/GameObject/IGameObject.hpp"

#pragma once

class AGameObject : public IGameObject {
    public:
        AGameObject(Vec2i pos) : _pos(pos) {}

        virtual ~AGameObject() = default;

        virtual std::pair<Vec2i, std::string> dumpTexture() const {return std::make_pair(_pos, _textureName);}

        virtual IGameObject::Effects getEffects() const {return _effects;}

        virtual void setPos(Vec2i pos) {_pos = pos;}

        virtual Vec2i getPos() const {return _pos;}

        virtual void applyEffect(SnakeObject &snake);

    protected:
        std::string _textureName;
        IGameObject::Effects _effects;
        Vec2i _pos;
        bool _autoRespawn;
        bool _destroyable;

    private:
};
