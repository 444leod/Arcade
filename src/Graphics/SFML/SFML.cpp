/*
** EPITECH PROJECT, 2024
** SFML.cpp
** File description:
** SFML.cpp
*/

#include "SFML.hpp"

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
