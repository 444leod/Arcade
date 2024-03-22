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

using pacman::vec2i;
using pacman::vec2f;
using pacman::TileType;

namespace pacman {
    class MapHandler {
        public:
            MapHandler();
            ~MapHandler() = default;

            uint16_t getMapSizeX() const;
            uint16_t getMapSizeY() const;

            std::vector<std::pair<vec2i, std::string>> dumpTextures() const;

            bool isTileWalkable(vec2i pos) const;
            bool isTileWalkable(int x, int y) const;
            TileType getTileType(vec2i pos);

            vec2i getPlayerPos();
            pacman::player::State processPlayerPos(vec2i newPos, vec2i direction, uint32_t& score, std::vector<vec2f> ghostsPos, vec2f pacmanPos);

        protected:
        private:
            std::vector<std::vector<int>> _map;
            vec2i _playerPos = {-1, -1};
            vec2i _nextPlayerPos = {-1, -1};
            std::map<vec2i, vec2i> _teleporters = {
                {vec2i(0, 10), vec2i(18, 10)},
            };
            std::map<int, std::string> _textures = {};
            std::map<int, pacman::TileType> _tileTypes = {};

            void findPlayerPos();
            void parseMap();

    };

}
