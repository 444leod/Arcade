/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** IGameObject
*/

#pragma once

#include <string>
#include "SnakeLib/SnakeObject/SnakeObject.hpp"

class IGameObject {
    public:
        struct Effects {
            int deltaScore;
            float deltaSpeed;
            int deltaGrowth;
            bool killPlayer;
        };

        enum Type {
            SUPER_CANDY,
            TAMATO_BERRY
        };

        virtual ~IGameObject() = default;

        virtual std::pair<Vec2i, std::string> dumpTexture() const = 0;

        virtual bool getRespawn() const = 0;

        virtual void setPos(Vec2i pos) = 0;

        virtual Vec2i getPos() const = 0;

        virtual Type getType() const = 0;

        virtual void applyEffect(SnakeObject &snake) = 0;

    protected:
    private:
};
