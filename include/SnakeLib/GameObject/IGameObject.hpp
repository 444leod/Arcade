/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** IGameObject
*/

#include <string>
#include "SnakeLib/SnakeObject/SnakeObject.hpp"

#pragma once

class IGameObject {
    public:
        struct pos {
            int x;
            int y;
        };

        struct Effects {
            int deltaScore;
            float deltaSpeed;
            int deltaGrowth;
            bool killPlayer;
        };

        virtual ~IGameObject() = default;

        virtual std::pair<position, std::string> dumpTexture() const = 0;

        virtual IGameObject::Effects getEffects() const = 0;

        virtual void setPos(position pos) = 0;

        virtual position getPos() const = 0;

        virtual void applyEffect(SnakeObject &snake) = 0;

    protected:
    private:
};
