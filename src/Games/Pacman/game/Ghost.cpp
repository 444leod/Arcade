/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Ghost
*/

#include "Ghost.hpp"
#include "Player.hpp"

using pacman::ghosts::Ghost;

Ghost::Ghost()
{
    _name = "ghost";
}

Ghost::~Ghost()
{
}

void Ghost::queueMove(Direction direction)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = pacman::DirectionToVec2[direction];
        return;
    }
    _moveQueue = {pacman::DirectionToVec2[direction]};
}

void Ghost::queueMove(Vec2i move)
{
    if (_direction == Vec2i(0, 0)) {
        _direction = move;
        return;
    }
    _moveQueue = {move};
}

void Ghost::setMoveQueue(std::vector<Vec2i> moveQueue)
{
    _moveQueue = moveQueue;
}

void Ghost::initTextures(arc::ITextureManager& manager)
{
    arc::TextureSpecification spec;
    spec.textual.character = 'G';
    spec.textual.color = {255, 0, 0, 255};
    pacman::Direction dir = pacman::Direction::LEFT;
    for (int i = 0; i < 4; i++) {
        _textures[dir] = {};
        std::stringstream ss;
        ss << "ghost_" << i;
        spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 20), 200, 20, 20}};
        manager.load(ss.str(), spec);
        _textures[dir].push_back(ss.str());
        dir = static_cast<pacman::Direction>(static_cast<int>(dir) + 1);
    }
    spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{0, 0, 20, 20}};
    manager.load("ghost_start", spec);
    _textures[pacman::Direction::NONE] = {"ghost_start"};
}

std::string Ghost::getTexture(uint16_t tick)
{
    pacman::Direction direction;
    Vec2f pos;
    if (this->getDirection() == Vec2i(0, 0))
        return this->_name + "_start";

    for (auto [dir, vec] : pacman::DirectionToVec2) {
        if (vec == this->getDirection()) {
            direction = dir;
            break;
        }
    }
    auto entityTextures = this->getTextures();
    if (this->getStatus() == pacman::entity::status::DEAD) {
        return "deadghost_" + std::to_string(static_cast<int>(direction));
    } else if (this->getStatus() == pacman::entity::status::SCARED) {
        std::stringstream ss;
        ss << "scaredghost_" << (tick % 2 + 1);
        return ss.str();
    }
    auto entityTexture = entityTextures[direction];
    if (entityTexture.size() == 0)
        return "";
    return entityTexture[tick % entityTexture.size()];
}

std::vector<pacman::Direction> Ghost::getAvailableDirections()
{
    return {pacman::Direction::UP, pacman::Direction::DOWN, pacman::Direction::LEFT, pacman::Direction::RIGHT};
}
