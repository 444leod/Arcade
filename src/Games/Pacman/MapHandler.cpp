/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** MapHandler
*/

#include "MapHandler.hpp"
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

using pacman::MapHandler;

MapHandler::MapHandler()
{
    _textures[0] = "empty";
    _tileTypes[0] = TileType::VOID;
    _textures[1] = "coin";
    _tileTypes[1] = TileType::COIN;
    for (int i = 2; i <= 33; ++i) {
        std::stringstream ss;
        ss << "wall_" << i;
        _textures[i] = ss.str();
        _tileTypes[i] = TileType::WALL;
    }
    _textures[34] = "fruit";
    _tileTypes[34] = TileType::FRUIT;
    this->parseMap();
}

uint16_t MapHandler::getMapSizeX() const
{
    return _map[0].size();
}

uint16_t MapHandler::getMapSizeY() const
{
    return _map.size();
}

std::vector<std::pair<Vec2i, std::string>> MapHandler::dumpTextures() const
{
    std::vector<std::pair<Vec2i, std::string>> res;
    for (uint16_t y = 0; y < _map.size(); ++y) {
        for (uint16_t x = 0; x < _map[y].size(); ++x) {
            res.push_back({{x, y}, _textures.at(_map[y][x])});
        }
    }
    return res;
}

bool MapHandler::isTileWalkable(int x, int y) const
{
    if (x < 0 || y < 0 || y >= static_cast<int>(_map.size()) || x >= static_cast<int>(_map[y].size()))
        return false;
    return _tileTypes.at(_map[y][x]) != TileType::WALL;
}

bool MapHandler::isTileWalkable(Vec2i pos) const
{
    return isTileWalkable(pos.x, pos.y);
}

TileType MapHandler::getTileType(Vec2i pos)
{
    return _tileTypes.at(_map[pos.y][pos.x]);
}

Vec2i MapHandler::getPlayerPos()
{
    return _playerPos;
}

pacman::player::State MapHandler::processPlayerPos(Vec2i newPos, Vec2i direction, uint32_t& score, std::vector<Vec2f> ghostPos, Vec2f pacmanPos)
{
    if (_nextPlayerPos != Vec2i(-1, -1)) {
        _playerPos = _nextPlayerPos;
        _nextPlayerPos = Vec2i(-1, -1);
        return pacman::player::State::ALIVE;
    } else
        _playerPos = newPos;

    for (auto &teleporter : _teleporters) {
        if (_playerPos == teleporter.first && direction == Vec2i(-1, 0))
            _nextPlayerPos = teleporter.second;
        if (_playerPos == teleporter.second && direction == Vec2i(1, 0))
            _nextPlayerPos = teleporter.first;
    }
    for (auto &ghost : ghostPos) {
        float tolerance = 0.4f;
        if (std::abs(pacmanPos.x - ghost.x) <= tolerance && std::abs(pacmanPos.y - ghost.y) <= tolerance)
            return pacman::player::State::DEAD;
    }
    TileType tile = _tileTypes.at(_map[_playerPos.y][_playerPos.x]);
    switch (tile) {
        case TileType::COIN:
            _map[_playerPos.y][_playerPos.x] = static_cast<int>(TileType::VOID);
            score += 10;
            return pacman::player::State::ALIVE;
        case TileType::FRUIT:
            _map[_playerPos.y][_playerPos.x] = static_cast<int>(TileType::VOID);
            score += 100;
            return pacman::player::State::HUNGRY;
        default:
            break;
    }
    return pacman::player::State::ALIVE;
}

void MapHandler::findPlayerPos()
{
    for (uint16_t y = 0; y < _map.size(); ++y) {
        for (uint16_t x = 0; x < _map[y].size(); ++x) {
            if (_map[y][x] == -1) {
                _playerPos = {x, y};
                _map[y][x] = 0;
                return;
            }
        }
    }
    _playerPos = {-1, -1};
}

void MapHandler::parseMap()
{
    CSVParser<int> parser("./assets/pacman/map.csv");
    parser.parse();
    _map = parser.getData();

    uint16_t lineSize = 0;
    uint16_t lineCount = 0;

    if (_map.size() == 0)
        throw std::runtime_error("Invalid map: empty map found");
    for (auto &line : _map) {
        if (line.size() == 0)
            throw std::runtime_error("Invalid map: empty line found");
        else if (lineSize == 0)
            lineSize = line.size();
        else if (lineSize != line.size())
            throw std::runtime_error("Invalid map: lines have different sizes");
        lineCount++;
    }
    this->findPlayerPos();
    if (_playerPos.x == -1 && _playerPos.y == -1)
        throw std::runtime_error("Invalid map: no player position found");
}
