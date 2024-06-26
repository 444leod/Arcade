/*
** EPITECH PROJECT, 2024
** SFML.cpp
** File description:
** SFML.cpp
*/

#include "SFML.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <cmath>
#include <memory>

extern "C" arc::ILibrary *entrypoint()
{
    return new SFMLLibrary;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::LIBRARY;
}

extern "C" const char *name()
{
    return "SFML";
}
