/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** HitBox
*/

#pragma once

#include "Vector.hpp"

class HitBox {
    public:
        HitBox() = default;
        HitBox(dVector position, double radius);
        ~HitBox() = default;

        const dVector& position() const { return this->_position; }
        double radius() const { return this->_radius; }
        bool overlaps(const HitBox& other) const;
        bool overlaps(dVector pos, dVector size) const;

    protected:
    private:
        dVector _position = dVector(0.0, 0.0);
        double _radius = 0.0;
};
