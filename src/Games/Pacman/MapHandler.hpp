/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** MapHandler
*/

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <map>
#include <cstdint>
#include "CSVParser.hpp"
#include "Pacman.hpp"

using pacman::TileType;

namespace pacman {
    class MapHandler {
        public:
            MapHandler();
            ~MapHandler() = default;

            uint16_t getMapSizeX() const;
            uint16_t getMapSizeY() const;

            std::vector<std::pair<Vec2i, std::string>> dumpTextures() const;

            bool isTileWalkable(Vec2i pos) const;
            bool isTileWalkable(int x, int y) const;
            TileType getTileType(Vec2i pos);

            Vec2i getPlayerPos();
            pacman::player::State processPlayerPos(Vec2i newPos, Vec2i direction);

        protected:
        private:
            std::vector<std::vector<int>> _map;
            Vec2i _playerPos = {-1, -1};
            Vec2i _nextPlayerPos = {-1, -1};
            std::map<Vec2i, Vec2i> _teleporters = {
                {Vec2i(0, 10), Vec2i(18, 10)},
            };
            std::map<int, std::string> _textures = {};
            std::map<int, pacman::TileType> _tileTypes = {};

            void findPlayerPos();
            void parseMap();

    };

}
