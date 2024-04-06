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

    protected:
    private:
        arc::Color _color = { 255, 0, 0, 255 };
        fVector _postion;
        fVector _velocity;
};
