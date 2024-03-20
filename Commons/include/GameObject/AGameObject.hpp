/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** AGameObject
*/

#include "GameObject/IGameObject.hpp"

#pragma once

class AGameObject : public IGameObject{
    public:
        AGameObject(std::string textureName, IGameObject::pos pos) : _textureName(textureName), _pos(pos) {}

        virtual ~AGameObject() = default;

        virtual std::pair<IGameObject::pos, std::string> dumpTexture() {return std::make_pair(_pos, _textureName);}

        virtual IGameObject::Effects getEffects() {return _effects;}

        virtual void setPos(IGameObject::pos pos) {_pos = pos;}

        virtual IGameObject::pos getPos() const {return _pos;}

    protected:
        std::string _textureName;
        IGameObject::Effects _effects;
        IGameObject::pos _pos;

    private:
};
