/*
** EPITECH PROJECT, 2024
** JAM2
** File description:
** Map
*/

#pragma once

#include "PathFinder.hpp"
#include "../include/Vec2.hpp"
#include "ghosts/Blinky.hpp"
#include "ghosts/Pinky.hpp"
#include "ghosts/Inky.hpp"
#include "ghosts/Clyde.hpp"
#include <iostream>
#include <vector>
#include <map>

class Map {
    public:
        Map() = default;
        Map(Vec2i position, Vec2i size, arc::ITextureManager&,
            std::vector<std::shared_ptr<pacman::IEntity>>&);
        ~Map();

        Vec2i size() const { return _size; }
        Vec2i position() const { return _position; }
        std::vector<std::vector<int>> tiles() const { return _tiles; }
        int tileAtAbsPos(Vec2i) const;
        void setAtAbsPos(Vec2i, int);

        std::vector<std::pair<Vec2i, std::string>> dump() const;
        Vec2i getCenterSafePos() const;
        void setTile(Vec2i pos, int value);

    protected:
    private:
        Vec2i _position = {};
        Vec2i _size = {};
        std::vector<std::vector<int>> _tiles = {};
};
