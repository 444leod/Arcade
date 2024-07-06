/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AAnimation
*/

#pragma once

#include "ILibrary.hpp"
#include "Vector.hpp"

class AAnimation {
    public:
        AAnimation(const std::string& texture);
        virtual ~AAnimation() = default;

        virtual void update(double dt);
        virtual void draw(arc::ILibrary& lib, const dVector& position, double direction) const;
        virtual void debug(arc::ILibrary& lib, const dVector& position) const;

    protected:
        const std::string _texture;
        std::string _frame;
        uint32_t _frameIndex = 0;
};
