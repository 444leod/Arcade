/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** position
*/

#pragma once

class position {
    public:
        int x;
        int y;

        bool operator== (position &rightPos) const 
        {
            return (x == rightPos.x && y == rightPos.y);
        }
        bool operator!= (position &rightPos) const 
        {
            return !(x == rightPos.x && y == rightPos.y);
        }
};
