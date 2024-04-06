/*
** EPITECH PROJECT, 2024
** *
** File description:
** Champion
*/

#pragma once

#include "Vector.hpp"
#include "ILibrary.hpp"

class Champion {
    public:
        Champion();
        ~Champion();

        void draw(arc::ILibrary& lib) const;
        void input(uint8_t xaxis, bool jump);
        void update(float dt);

    protected:
    private:
        const float _acceleration = 1.f;
        const float _maxspeed = 1.f;
        const float _jumpforce = 3.f;

        arc::Color _color = { 255, 0, 0, 255 };
        fVector _postion = {0.f, 0.f};
        fVector _velocity = {0.f, 0.f};
        bool _accelerating = false;
};
