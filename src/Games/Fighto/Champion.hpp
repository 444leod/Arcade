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
        Champion(id_t id);
        ~Champion();

        void draw(arc::ILibrary& lib) const;
        void input(float xaxis, int yaxis); // mouvement reserved
        void input(HitResolver& hits); // combat reserved
        void update(float dt);
        void damage(float amount);

        const fVector position() const { return this->_position; }
        const fVector size() const { return this->_size; }

        bool operator==(const Champion& other) const { return this->_id == other._id; }

    protected:
    private:
        const id_t _id;
        const float _maxspeed = 8.f;
        const float _jumpforce = 16.f;
        const fVector _size = {1.f, 1.f};

        bool _alive = true;
        float _lifepoints = 100.f;
        arc::Color _color = { 255, 0, 0, 255 };
        fVector _position = {0.f, 0.f};
        fVector _velocity = {0.f, 0.f};
        bool _grounded = false;
};
