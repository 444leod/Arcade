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
#include "Animations/AAnimation.hpp"
#include <queue>

class Champion {
    public:
        Champion() = delete;
        Champion(std::uint32_t id, const std::string& texture);
        ~Champion() = default;

        void draw(arc::ILibrary& lib) const;
        void debug(arc::ILibrary& lib) const;

        void input(dVector input);
        void input(arc::JoystickButton button);

        void update(double dt);
        void damage(double damage, dVector knockback, double stagger);

        double id() const { return this->_id; }
        bool alive() const { return this->_alive; }
        double life() const { return this->_lifepoints; }
        std::shared_ptr<AMove> move() const;
        double direction() const { return this->_direction; }
        const dVector position() const { return this->_position; }
        const dVector size() const { return this->_size; }

    private: // Movement related
        dVector _position = dVector(10.0, 5.0);
        dVector _velocity = dVector(0.0, 0.0);
        double _speed = 0.0;
        const double _maxspeed = 12.0;
        const double _acceleration = 0.5;
        const double _jumpforce = 19.0;
        bool _grounded = false;
        dVector _input = dVector(0.0, 0.0);
        double _direction = 1.0;

    private: // Combat related
        std::uint32_t _id;
        bool _alive = true;
        double _lifepoints = 100.0;
        double _stagger = 0.0;
        mutable std::queue<std::shared_ptr<AMove>> _moveQueue = {};

    private: // Display related
        std::string _texture;
        const dVector _size = dVector(1.0, 1.0);
        std::shared_ptr<AAnimation> _animation;
};
