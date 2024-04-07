/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Map
*/

#include "Map.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

pacman::Map::Map(std::vector<std::vector<int>> map)
{
    _map = map;

    _checkMapValidity();
    _convertMap();
}

pacman::Map::Map(std::string path)
{
    CSVParser<int> parser(path);
    parser.parse();
    _map = parser.getData();

    _checkMapValidity();
    _convertMap();
}

void pacman::Map::initTextures(arc::ITextureManager& manager)
{
    #if V2
    std::string path = "assets/pacman/images/snow_tileset.png";
    uint32_t size = 24;
    #else
    std::string path = "assets/pacman/board.png";
    uint32_t size = 32;
    #endif

    arc::TextureSpecification spec;
    spec.textual.character = '.';
    spec.textual.color = {255, 255, 0, 255};
    spec.graphical = arc::TextureImage{path, arc::Rect<uint32_t>{(32 * size), 0, size, size}};
    manager.load("coin", spec);

    spec.textual.character = 'O';
    spec.textual.color = {255, 0, 0, 255};
    spec.graphical = arc::TextureImage{path, arc::Rect<uint32_t>{(33 * size), 0, size, size}};
    manager.load("fruit", spec);

    spec.textual.character = ' ';
    spec.textual.color = {1, 2, 3, 255};
    for (uint16_t i = 0; i <= 33; ++i) {
        std::stringstream ss;
        ss << "wall_" << 100 + i;
        spec.graphical = arc::TextureImage{path, arc::Rect<uint32_t>{static_cast<uint16_t>(i * size), 0, size, size}};
        manager.load(ss.str(), spec);
    }

    spec.textual.character = ' ';
    spec.textual.color = {0, 0, 0, 255};
    #if V2
    spec.graphical = arc::TextureImage{path, arc::Rect<uint32_t>{(34 * size), 0, size, size}};
    #else
    spec.graphical = arc::Color{0, 0, 0, 255};
    #endif
    manager.load("empty", spec);
    spec.textual.character = '_';
    spec.textual.color = {255, 255, 0, 255}; //yellow
    spec.graphical = arc::TextureImage{path, arc::Rect<uint32_t>{(34 * size), 0, size, size}};
    manager.load("door", spec);
}

void pacman::Map::_checkMapValidity() const
{
    bool _isPlayerSet = false;
    bool _isDoorSet = false;
    bool _isGhostSpawnSet = false;

    uint16_t lineSize = 0;
    uint16_t lineCount = 0;

    if (_map.size() == 0)
        throw std::runtime_error("Invalid map: empty map found");
    for (auto &line : _map) {
        if (line.size() == 0)
            throw std::runtime_error("Invalid map: empty line found (line " + std::to_string(lineCount) + ")");
        else if (lineSize == 0)
            lineSize = line.size();
        else if (lineSize != line.size())
            throw std::runtime_error("Invalid map: lines have different sizes (line " + std::to_string(lineCount) + ")");
        lineCount++;
        for (auto &cell : line) {
            if (_texturer._tileToTileType.find(cell) == _texturer._tileToTileType.end())
                throw std::runtime_error("Invalid tile type (" + std::to_string(cell) + ")");
            if (!_isPlayerSet && _texturer._tileToTileType.at(cell) == pacman::TileType::PLAYER) {
                _isPlayerSet = true;
                continue;
            }
            if (!_isDoorSet && _texturer._tileToTileType.at(cell) == pacman::TileType::DOOR) {
                _isDoorSet = true;
                continue;
            }
            if (!_isGhostSpawnSet && _texturer._tileToTileType.at(cell) == pacman::TileType::GHOST) {
                _isGhostSpawnSet = true;
                continue;
            }
        }
    }
    if (!_isPlayerSet)
        throw std::runtime_error("Invalid map: no player position found");
    if (!_isDoorSet)
        throw std::runtime_error("Invalid map: no door found");
    if (!_isGhostSpawnSet)
        throw std::runtime_error("Invalid map: no ghost spawn point found");
}

void pacman::Map::_convertMap()
{
    _mapSizeX = static_cast<uint16_t>(_map[0].size());
    _mapSizeY = static_cast<uint16_t>(_map.size());

    for (auto &line : _map) {
        std::vector<pacman::TileType> tileLine;
        for (auto &cell : line) {
            pacman::TileType tileType = _texturer._tileToTileType.at(cell);
            switch (tileType) {
                case pacman::TileType::PLAYER:
                    tileType = pacman::TileType::EMPTY;
                    _map[_tileMap.size()][tileLine.size()] = _texturer._typeToTile.at(pacman::TileType::EMPTY);
                    _playerPos = {static_cast<int>(tileLine.size()), static_cast<int>(_tileMap.size())};
                    break;
                case pacman::TileType::GHOST:
                    tileType = pacman::TileType::EMPTY;
                    _map[_tileMap.size()][tileLine.size()] = _texturer._typeToTile.at(pacman::TileType::EMPTY);
                    _ghostSpawnPoints.push_back({static_cast<int>(tileLine.size()), static_cast<int>(_tileMap.size())});
                    break;
                case pacman::TileType::COIN:
                    _coinCount++;
                    break;
                case pacman::TileType::FRUIT:
                    _fruitCount++;
                    break;
                default:
                    break;
            }
            tileLine.push_back(tileType);
        }
        _tileMap.push_back(tileLine);
    }
}

void pacman::Map::setCellType(Vec2i pos, int type)
{
    setCellType(pos.x, pos.y, type);
}

void pacman::Map::setCellType(int x, int y, int type)
{
    if (_texturer._tileToTileType.find(type) == _texturer._tileToTileType.end())
        throw std::runtime_error("Invalid tile type (" + std::to_string(type) + ")");
    setCellType(x, y, _texturer._tileToTileType.at(type));
}

void pacman::Map::setCellType(int x, int y, pacman::TileType type)
{
    if (x < 0 || x >= _mapSizeX || y < 0 || y >= _mapSizeY)
        throw std::runtime_error("Invalid position (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    if (type == pacman::TileType::PLAYER)
        throw std::runtime_error("Cannot set player position manually");
    if (type == pacman::TileType::GHOST)
        throw std::runtime_error("Cannot set ghost spawn point manually");
    if (type == pacman::TileType::WALL)
        throw std::runtime_error("Cannot set wall manually");

    pacman::TileType oldTileType = _tileMap[y][x];

    _tileMap[y][x] = type;
    _map[y][x] = _texturer._typeToTile.at(type);
    if (oldTileType == pacman::TileType::COIN && type != pacman::TileType::COIN)
        _coinCount--;
    else if (oldTileType == pacman::TileType::FRUIT && type != pacman::TileType::FRUIT)
        _fruitCount--;
}

void pacman::Map::setCellType(Vec2i pos, pacman::TileType type)
{
    setCellType(pos.x, pos.y, type);
}

pacman::TileType pacman::Map::getCellType(Vec2i pos) const
{
    return getCellType(pos.x, pos.y);
}

pacman::TileType pacman::Map::getCellType(int x, int y) const
{
    if (x < 0 || x >= _mapSizeX || y < 0 || y >= _mapSizeY)
        return pacman::TileType::VOID;
    return _tileMap[y][x];
}

bool pacman::Map::isCellType(Vec2i pos, int type) const
{
    return isCellType(pos.x, pos.y, type);
}

bool pacman::Map::isCellType(int x, int y, int type) const
{
    if (_texturer._tileToTileType.find(type) == _texturer._tileToTileType.end())
        throw std::runtime_error("Invalid tile type (" + std::to_string(type) + ")");
    return isCellType(x, y, _texturer._tileToTileType.at(type));
}

bool pacman::Map::isCellType(Vec2i pos, pacman::TileType type) const
{
    return isCellType(pos.x, pos.y, type);
}

bool pacman::Map::isCellType(int x, int y, pacman::TileType type) const
{
    if (x < 0 || x >= _mapSizeX || y < 0 || y >= _mapSizeY)
        return pacman::TileType::VOID == type;
    return _tileMap[y][x] == type;
}

bool pacman::Map::isCellValid(Vec2i pos) const
{
    return isCellValid(pos.x, pos.y);
}

bool pacman::Map::isCellValid(int x, int y) const
{
    return x >= 0 && x < _mapSizeX && y >= 0 && y < _mapSizeY;
}

Vec2i pacman::Map::getPlayerPos() const
{
    return _playerPos;
}

std::vector<Vec2i> pacman::Map::getGhostSpawnPoints() const
{
    return _ghostSpawnPoints;
}

std::vector<std::pair<Vec2i, std::string>> pacman::Map::getTextures() const
{
    std::vector<std::pair<Vec2i, std::string>> textures;

    for (uint16_t y = 0; y < _mapSizeY; y++) {
        for (uint16_t x = 0; x < _mapSizeX; x++) {
            textures.push_back({{x, y}, "empty"});
        }
    }
    for (uint16_t y = 0; y < _mapSizeY; y++) {
        for (uint16_t x = 0; x < _mapSizeX; x++) {
            textures.push_back({{x, y}, _texturer.getTexture(_map[y][x])});
        }
    }
    return textures;
}

pacman::MapTexturer::MapTexturer()
{
    _tileToTileType = {
        {-1, pacman::TileType::VOID},
        {0, pacman::TileType::EMPTY},
        {1, pacman::TileType::PLAYER},
        {2, pacman::TileType::COIN},
        {3, pacman::TileType::FRUIT},
        {4, pacman::TileType::DOOR},
        {5, pacman::TileType::GHOST}
    };
    _typeToTile = {
        {pacman::TileType::VOID, -1},
        {pacman::TileType::EMPTY, 0},
        {pacman::TileType::PLAYER, 1},
        {pacman::TileType::COIN, 2},
        {pacman::TileType::FRUIT, 3},
    };
    for (uint16_t i = 100; i <= 132; i++)
        _tileToTileType[i] = pacman::TileType::WALL;

    _texturers = {
        {pacman::TileType::VOID,    [] ([[maybe_unused]] int tile) { return "empty"; }},
        {pacman::TileType::EMPTY,   [] ([[maybe_unused]] int tile) { return "empty"; }},
        {pacman::TileType::COIN,    [] ([[maybe_unused]] int tile) { return "coin"; }},
        {pacman::TileType::FRUIT,   [] ([[maybe_unused]] int tile) { return "fruit"; }},
        {pacman::TileType::DOOR,    [] ([[maybe_unused]] int tile) { return "door"; }},
        {pacman::TileType::WALL,    [] ([[maybe_unused]] int tile) { return "wall_" + std::to_string(tile); }},
    };
}

std::string pacman::MapTexturer::getTexture(int tile) const
{
    if (_tileToTileType.find(tile) == _tileToTileType.end())
        throw std::runtime_error("Invalid tile type (" + std::to_string(tile) + ")");
    return _texturers.at(_tileToTileType.at(tile))(tile);
}

Vec2i pacman::Map::getDoorPos() const
{
    for (uint16_t y = 0; y < _mapSizeY; y++) {
        for (uint16_t x = 0; x < _mapSizeX; x++) {
            if (_tileMap[y][x] == pacman::TileType::DOOR)
                return {x, y};
        }
    }
    return {-1, -1};
}

std::vector<std::vector<int>> pacman::Map::getMap()
{
    std::vector<std::vector<int>> map;

    for (auto &line : _tileMap) {
        std::vector<int> newLine;
        for (auto &cell : line) {
            newLine.push_back(static_cast<int>(cell));
        }
        map.push_back(newLine);
    }

    return map;
}

std::vector<std::pair<Vec2i, Vec2i>> pacman::Map::getTeleporters() const
{
    return _teleporters;
}
