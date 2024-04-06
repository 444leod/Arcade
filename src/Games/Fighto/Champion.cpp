/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Champion
*/

#include "Champion.hpp"

Champion::Champion()
{
}

Champion::~Champion()
{
}

void Champion::draw(arc::ILibrary& lib) const
{
    lib.display().draw(lib.textures().get(""), this->_postion.x, this->_postion.y);
}
