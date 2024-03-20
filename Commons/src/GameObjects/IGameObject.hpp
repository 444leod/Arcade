/*
** EPITECH PROJECT, 2024
** Commons
** File description:
** IGameObject
*/

#include <string>

#pragma once

class IGameObject {
    public:
        struct pos {
            int x;
            int y;
        };

        struct Effects {
            int deltaScore;
            int deltaSpeed;
            int deltaGrowth;
        };

        virtual ~IGameObject() = default;

        virtual std::pair<IGameObject::pos, std::string> dumpTexture() = 0;

        virtual IGameObject::Effects getEffects() = 0;

    protected:
    private:
};
