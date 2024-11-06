/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Map
*/

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <cstdint>
#include "ILibrary.hpp"
#include "IEntity.hpp"
#include "CSVParser.hpp"
#include "Vec2.hpp"
#include "Pacman.hpp"


namespace pacman {
class MapTexturer {
    public:
        MapTexturer();
        ~MapTexturer() = default;

        std::string getTexture(int tile) const;
        std::map<pacman::TileType, std::function<std::string(int)>> _texturers;
        std::map<int, pacman::TileType> _tileToTileType;
        std::map<pacman::TileType, int> _typeToTile;
};


class Map {
    public:
        Map(std::vector<std::vector<int>> map);
        Map(std::string path);
        Map() = delete;
        ~Map() = default;

        void initTextures(arc::ITextureManager& manager);

        std::vector<std::vector<int>> getMap() const { return _map; }

        void setCellType(int x, int y, int type);
        void setCellType(Vec2i pos, int type);
        void setCellType(int x, int y, pacman::TileType type);
        void setCellType(Vec2i pos, pacman::TileType type);

        pacman::TileType getCellType(int x, int y) const;
        pacman::TileType getCellType(Vec2i pos) const;
        bool isCellType(int x, int y, int type) const;
        bool isCellType(Vec2i pos, int type) const;
        bool isCellType(int x, int y, pacman::TileType type) const;
        bool isCellType(Vec2i pos, pacman::TileType type) const;
        bool isCellValid(int x, int y) const;
        bool isCellValid(Vec2i pos) const;

        Vec2i getPlayerPos() const;
        std::vector<Vec2i> getGhostSpawnPoints() const;
        Vec2i getDoorPos() const;

        std::vector<std::pair<Vec2i, std::string>> getTextures() const;

        std::vector<std::vector<int>> getMap();

        std::vector<std::pair<Vec2i, Vec2i>> getTeleporters() const;

        uint16_t getMapSizeX() const { return _mapSizeX; }
        uint16_t getMapSizeY() const { return _mapSizeY; }

        uint32_t getFruitCount() const { return _fruitCount; }
        uint32_t getCoinCount() const { return _coinCount; }

    protected:
    private:
        MapTexturer _texturer;

        std::vector<std::vector<int>> _map;
        std::vector<std::vector<pacman::TileType>> _tileMap;

        Vec2i _playerPos;
        std::vector<Vec2i> _ghostSpawnPoints;
        std::vector<std::pair<Vec2i, Vec2i>> _teleporters = {
            {{0, 10}, {18, 10}},
            {{18, 10}, {0, 10}}
        };

        uint16_t _mapSizeX;
        uint16_t _mapSizeY;
        uint32_t _fruitCount = 0;
        uint32_t _coinCount = 0;

        void _checkMapValidity() const;
        void _convertMap();

};
class Orientation {
    public:
        Orientation(bool n, bool s, bool e, bool w)
            : north(n), south(s), east(e), west(w) {}
        Orientation() = default;
        ~Orientation() = default;

        bool north = false;
        bool south = false;
        bool east = false;
        bool west = false;

        bool operator==(const Orientation &other) const
        {
            return north == other.north && south == other.south && east == other.east && west == other.west;
        }
};
}
