/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** AGameObject
*/

#pragma once

#include "SnakeLib/GameObject/IGameObject.hpp"

class AGameObject : public IGameObject {
    public:
        AGameObject(Vec2i pos) : _pos(pos) {}

        virtual ~AGameObject() = default;

        virtual std::pair<Vec2i, std::string> dumpTexture() const {return std::make_pair(_pos, _textureName);}

        virtual bool getRespawn() const {return _respawn;}

        virtual void setPos(Vec2i pos) {_pos = pos;}

        virtual Vec2i getPos() const {return _pos;}

        virtual IGameObject::Type getType() const {return _type;}

        virtual void applyEffect(SnakeObject &snake);

    protected:
        std::string _textureName;
        IGameObject::Effects _effects;
        IGameObject::Type _type;
        Vec2i _pos;
        bool _respawn;

    private:
};
