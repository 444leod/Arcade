/*
** EPITECH PROJECT, 2024
** *
** File description:
** Champion
*/

#pragma once

#include "HitResolver.hpp"
#include "Vector.hpp"
#include "ILibrary.hpp"

class HitResolver;

class Champion {
    public:
        Champion();
        ~Champion();

        void draw(arc::ILibrary& lib) const;
        void input(float xaxis, bool jump); // mouvement reserved
        void input(HitResolver& hits); // combat reserved
        void update(float dt);
        void damage(float amount);

        const fVector position() const { return this->_postion; }
        const fVector size() const { return this->_size; }

    protected:
    private:
        const float _maxspeed = 8.f;
        const float _jumpforce = 16.f;
        const fVector _size = {1.f, 1.f};

        float _lifepoints = 100.f;
        arc::Color _color = { 255, 0, 0, 255 };
        fVector _postion = {0.f, 0.f};
        fVector _velocity = {0.f, 0.f};
        bool _grounded = false;
};
