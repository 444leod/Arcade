/*
** EPITECH PROJECT, 2024
** *
** File description:
** Champion
*/

#pragma once

#include "ILibrary.hpp"
#include "Vector.hpp"
#include "MoveList.hpp"
#include <queue>

class Champion {
    public:
        Champion(arc::Color color);
        ~Champion();

        void draw(arc::ILibrary& lib) const;
        void debug(arc::ILibrary& lib) const;
        void input(dVector input);
        void input(arc::JoystickButton button);
        void update(double dt);
        void damage(double damage, dVector knockback, double stagger);

        double life() const { return this->_lifepoints; }
        std::shared_ptr<AMove> move() const;
        double direction() const { return this->_direction; }
        const dVector position() const { return this->_position; }
        const dVector size() const { return this->_size; }

    private:
        const double _acceleration = 0.5f;
        const double _maxspeed = 8.0;
        const double _jumpforce = 16.0;
        const dVector _size = dVector(1.0, 1.0);

    private:
        bool _alive = true;
        double _speed = 0.0;
        double _lifepoints = 100.0;
        arc::Color _color = { 255, 0, 0, 255 };
        dVector _position = dVector(10.0, 5.0);
        dVector _velocity = dVector(0.0, 0.0);
        mutable std::queue<std::shared_ptr<AMove>> _moveQueue = {};
        bool _grounded = false;
        dVector _input = dVector(0.0, 0.0);
        double _direction = 1.0;
        double _stagger = 0.0;
};
