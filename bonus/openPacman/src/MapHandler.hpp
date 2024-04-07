/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** MapHandler
*/

#pragma once

#include "Map.hpp"
#include "../include/OpenPacman.hpp"
#include "CSVParser.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <map>
#include <cstdint>
#include <memory>

using pacman::TileType;

namespace pacman {
    class MapHandler {
        public:
            MapHandler(arc::ITextureManager&, std::vector<std::shared_ptr<pacman::IEntity>>&);
            ~MapHandler() = default;

            int idx(Vec2i) const;
            std::vector<std::pair<Vec2i, std::string>> dumpTexturesByCenterPos(int x, int y) const;

            bool isTileWalkable(Vec2i pos) const;
            bool isTileWalkable(int x, int y) const;
            void checkChunks(Vec2i pos);

            Vec2i getPlayerPos();
            void processPlayerPos(std::shared_ptr<pacman::IEntity> player, std::vector<std::shared_ptr<pacman::IEntity>> &ghosts, uint32_t& score);
            std::vector<Vec2i> getfastestPath(Vec2i start, Vec2i end);

            void collideGhost(std::shared_ptr<pacman::IEntity> player, std::vector<std::shared_ptr<pacman::IEntity>> &ghosts, uint32_t tick);

        protected:
        private:
            Vec2i _playerPos = {-1, -1};
            bool _isInvicible = false;
            uint32_t _currentick = 0;
            //std::vector<std::vector<int>> _map;
            std::vector<Map> _chunks = {};
            std::map<int, std::string> _textures = {};
            std::map<int, pacman::TileType> _tileTypes = {};

            arc::ITextureManager& _texs;
            std::vector<std::shared_ptr<pacman::IEntity>>& _ghosts;

            //uint16_t _mapHeight = 101;
            //uint16_t _mapWidth = 101;

            std::vector<Vec2i> _directions = {
                {0, 1},
                {1, 0},
                {0, -1},
                {-1, 0},
                {1, 1},
                {1, -1},
                {-1, 1},
                {-1, -1}
            };

    };

}
