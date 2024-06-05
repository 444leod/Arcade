/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Hit
*/

#pragma once

#include "Champion.hpp"
#include "Vector.hpp"

class Champion;

class Hit {
    public:
        Hit(float _damage, fVector position, fVector size, Champion& source);
        ~Hit();

        fVector position() const { return this->_position; }
        fVector size() const { return this->_size; }
        const Champion& source() const { return this->_source; }
        float damage() const { return this->_damage; }

        bool overlaps(const Champion& other) const;

    protected:
    private:
        const float _damage;
        const fVector _position;
        const fVector _size;
        const Champion& _source;
        const fVector _cornerA;
        const fVector _cornerB;
};
