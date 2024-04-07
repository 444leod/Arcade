/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Player
*/

#include "Player.hpp"

using pacman::Direction;
using pacman::player::Player;

Player::Player()
{
    _name = "player";
}

void Player::queueMove(Direction direction)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = pacman::DirectionToVec2[direction];
        return;
    }
    _moveQueue = {pacman::DirectionToVec2[direction]};
}

void Player::queueMove(Vec2i move)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = move;
        return;
    }
    _moveQueue = {move};
}

void Player::setMoveQueue(std::vector<Vec2i> moveQueue)
{
    _moveQueue = moveQueue;
}

void Player::initTextures(arc::ITextureManager &manager)
{
    pacman::Direction dir = pacman::Direction::LEFT;

    arc::TextureSpecification spec;
    spec.textual.character = 'P';
    spec.textual.color = {255, 255, 0, 255};

    _textures = {};
    for (int i = 0; i < 4; i++) {
        _textures[dir] = {};
        std::stringstream ss;
        ss << "player_" << i;
        for (int j = 0; j < 2; j++) {
            std::stringstream ss1;
            spec.textual.character = j == 0 ? 'c' : 'o';
            ss1 << ss.str() << "_" << j;
            spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(j * 20), static_cast<uint32_t>(i * 20), 20, 20}};
            manager.load(ss1.str(), spec);
            _textures[dir].push_back(ss1.str());
        }

        dir = static_cast<pacman::Direction>(static_cast<int>(dir) + 1);
    }

    spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{40, 0, 20, 20}};
    manager.load("player_start", spec);
    _textures[Direction::NONE] = {"player_start"};
}

