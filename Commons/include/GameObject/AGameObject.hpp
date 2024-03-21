/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** AGameObject
*/

#include "GameObject/IGameObject.hpp"

#pragma once

class AGameObject : public IGameObject {
    public:
        AGameObject(position pos) : _pos(pos) {}

        virtual ~AGameObject() = default;

        virtual std::pair<position, std::string> dumpTexture() const {return std::make_pair(_pos, _textureName);}

        virtual IGameObject::Effects getEffects() const {return _effects;}

        virtual void setPos(position pos) {_pos = pos;}

        virtual position getPos() const {return _pos;}

        virtual void applyEffect(SnakeObject &snake);

    protected:
        std::string _textureName;
        IGameObject::Effects _effects;
        position _pos;
        bool _autoRespawn;
        bool _destroyable;

    private:
};
