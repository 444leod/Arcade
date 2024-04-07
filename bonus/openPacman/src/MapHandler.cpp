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
#include "../include/OpenPacman.hpp"
#include "Player.hpp"
#include "Ghost.hpp"
#include "PathFinder.hpp"
#include "RandomNumberGenerator.hpp"

using pacman::TileType;
using rng::RandomNumberGenerator;
using pacman::MapHandler;

MapHandler::MapHandler(arc::ITextureManager& texs, std::vector<std::shared_ptr<pacman::IEntity>>& ghosts) :
    _texs(texs), _ghosts(ghosts)
{
    _textures[0] = "empty";
    _tileTypes[0] = TileType::VOID;
    _textures[1] = "wall";
    _tileTypes[1] = TileType::WALL;
    _textures[2] = "coin";
    _tileTypes[2] = TileType::COIN;

    for (int y = -1; y <= 1; y++)
        for (int x = -1; x <= 1; x++)
            _chunks.push_back(Map({x, y}, {21, 21}, texs, ghosts));
    _playerPos = _chunks[4].getCenterSafePos();
}

int MapHandler::idx(Vec2i pos) const
{
    for (std::size_t i = 0; i < this->_chunks.size(); i++) {
        if (_chunks[i].position() == pos)
            return i;
    }
    return -1;
}


static Vec2i playerToChunk(Vec2i pos)
{
    if (pos.x < 0)
        pos.x -= 21;
    if (pos.y < 0)
        pos.y -= 21;
    return Vec2i(pos.x / 21, pos.y / 21);
}

static Vec2i playerToChunk(int x, int y)
{
    if (x < 0)
        x -= 21;
    if (y < 0)
        y -= 21;
    return Vec2i(x / 21, y / 21);
}

bool MapHandler::isTileWalkable(int x, int y) const
{
    auto i = idx(playerToChunk(x, y));
    if (i < 0)
        return false;
    auto chunk = _chunks[i];
    return _tileTypes.at(chunk.tileAtAbsPos({x, y})) != TileType::WALL;
}

bool MapHandler::isTileWalkable(Vec2i pos) const
{
    return isTileWalkable(pos.x, pos.y);
}

Vec2i MapHandler::getPlayerPos()
{
    return _playerPos;
}

void MapHandler::processPlayerPos(std::shared_ptr<pacman::IEntity> player, [[maybe_unused]]std::vector<std::shared_ptr<pacman::IEntity>> &ghosts, uint32_t& score)
{
    Vec2f pacmanPos = player->getPosf();

    // Process the tile the player is on
    Vec2i playerPos = player->getPos();
    auto chunk = _chunks[idx(playerToChunk(playerPos))];
    TileType tile = _tileTypes.at(chunk.tileAtAbsPos({playerPos.x, playerPos.y}));

    switch (tile) {
        case TileType::COIN:
            _chunks[idx(playerToChunk(playerPos))].setAtAbsPos(playerPos, static_cast<int>(TileType::VOID));
            score += 10;
            break;
        case TileType::PACGUM:
            _chunks[idx(playerToChunk(playerPos))].setAtAbsPos(playerPos, static_cast<int>(TileType::VOID));
            score += 100;
            break;
        default:
            break;
    }
}

std::vector<Vec2i> MapHandler::getfastestPath([[maybe_unused]]Vec2i start, [[maybe_unused]]Vec2i end)
{
    std::vector<Vec2i> res;
    return res;
}

void MapHandler::collideGhost(std::shared_ptr<pacman::IEntity> player, std::vector<std::shared_ptr<pacman::IEntity>> &ghosts, uint32_t tick)
{
    Vec2f pacmanPos = player->getPosf();

    if (_isInvicible == true){
        if (tick - _currentick < 20)
            return;
        _isInvicible = false;
    }
    if (player->getDirection() == Vec2i(0, 0))
        return;
    // Check if the player is on a ghost
    for (auto &ghost : ghosts) {
        float tolerance = 0.4f;
        Vec2f ghostPos = ghost->getPosf();
        if (std::abs(pacmanPos.x - ghostPos.x) <= tolerance && std::abs(pacmanPos.y - ghostPos.y) <= tolerance) {
            float health = player->getHealth();
            float dammage = ghost->getDmg();
            health = health - dammage;
            player->setHealth(health);
            _currentick = tick;
            _isInvicible = !_isInvicible;
            if (health <= 0) {
                player->setStatus(pacman::entity::status::DEAD);
                return;
            }
        }
    }
}

std::vector<std::pair<Vec2i, std::string>> MapHandler::dumpTexturesByCenterPos(int x, int y) const
{
    Vec2i chunk = playerToChunk(x, y);
    std::vector<std::pair<Vec2i, std::string>> res = {};

    for (int y = chunk.y - 1; y <= chunk.y + 1; y++) {
        for (int x = chunk.x - 1; x <= chunk.x + 1; x++) {
            int i = idx({x, y});
            if (i < 0)
                continue;
            for (auto t : _chunks[i].dump())
                res.push_back(t);
        }
    }
    return res;
}

void MapHandler::checkChunks(Vec2i pos)
{
    pos = playerToChunk(pos);
    for (int y = pos.y - 1; y <= pos.y + 1; y++) {
        for (int x = pos.x - 1; x <= pos.x + 1; x++) {
            if (idx(Vec2i(x, y)) < 0) {
                // std::cout << "Found unbuilt chunk" << std::endl;
                _chunks.push_back(Map({x, y}, {21, 21}, _texs, _ghosts));
            }
        }
    }
}
