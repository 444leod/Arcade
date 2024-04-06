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
        void input(float xaxis, bool jump);
        void update(float dt);

    protected:
    private:
        const float _maxspeed = 8.f;
        const float _jumpforce = 16.f;

        arc::Color _color = { 255, 0, 0, 255 };
        fVector _postion = {0.f, 0.f};
        fVector _velocity = {0.f, 0.f};
        bool _grounded = false;
};
