/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Hit
*/

#pragma once

#include "Champion.hpp"
#include "Vector.hpp"

class Hit {
    public:
        Hit(fVector position, fVector size, Champion& source);
        ~Hit();

        const fVector position() const { return this->_position; }
        const fVector size() const { return this->_size; }
        const Champion& source() const { return this->_source; }

        bool overlaps(Champion& other) const;

    protected:
    private:
        const fVector _position;
        const fVector _size;
        const Champion& _source;
        const fVector _cornerA;
        const fVector _cornerB;
};
