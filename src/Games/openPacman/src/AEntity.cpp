/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AEntity
*/

#include "IEntity.hpp"
#include "AEntity.hpp"
#include "MapHandler.hpp"
#include "Vec2.hpp"

using pacman::Direction;
using pacman::player::State;
using pacman::AEntity;

Vec2i AEntity::getPos() const
{
    return _pos;
}

Vec2f AEntity::getPosf() const
{
    return _posf;
}

void AEntity::setPos(Vec2f pos)
{
    _pos = Vec2i(pos.x, pos.y);
    _posf = Vec2f(pos.x, pos.y);
}

void AEntity::setPos(Vec2i pos)
{
    _pos = pos;
}

void AEntity::setPos(float x, float y)
{
    _pos.x = x;
    _pos.y = y;
}

void AEntity::setPosf(Vec2i pos)
{
    _posf.x = static_cast<int>(pos.x);
    _posf.y = static_cast<int>(pos.y);
}

void AEntity::setDirection(Vec2i direction)
{
    _direction = direction;
}

void AEntity::setDirection(Direction direction)
{
    _direction = pacman::DirectionToVec2[direction];
}

Vec2i AEntity::getDirection() const
{
    return _direction;
}

void AEntity::move(float deltaTime, [[maybe_unused]]pacman::MapHandler& map)
{
    _elapsed += (deltaTime * _speed);
    while (_elapsed >= 0.2) {
        _elapsed -= 0.2;
        if (_moveQueue.size()) {
            Vec2i nextMove = _moveQueue.front();
            if (map.isTileWalkable(_pos + nextMove)) {
                _lastPos = _pos;
                _pos += nextMove;
                _direction = nextMove;
                _moveQueue.erase(_moveQueue.begin());
                return;
            }
        }
        if (map.isTileWalkable(_pos + _direction)) {
            _lastPos = _pos;
            _pos += _direction;
            _posf = Vec2f(_lastPos.x, _lastPos.y);
        } else {
            _lastPos = _pos;
        }
    }
}

void AEntity::movef(float deltaTime, [[maybe_unused]]pacman::MapHandler& map)
{
    _elapsedf += (deltaTime * _speed);
    while (_elapsedf >= 0.02) {
        _elapsedf -= 0.02;
        if (_pos != _lastPos) {
            _posf.x += (_direction.x * 0.1);
            _posf.y += (_direction.y * 0.1);
            return;
        }
    }
}

void AEntity::setMoveQueue(std::vector<Vec2i> moveQueue)
{
    _moveQueue = moveQueue;
}

void AEntity::queueMove(Vec2i move)
{
    _moveQueue.push_back(move);
}

void AEntity::queueMove(Direction direction)
{
    _moveQueue.push_back(pacman::DirectionToVec2[direction]);
}

size_t AEntity::getSpeed() const
{
    return _speed;
}

void AEntity::initTextures(arc::ITextureManager &manager)
{
    pacman::Direction dir = pacman::Direction::UP;
    arc::TextureSpecification spec;
    spec.textual.character = 'E';
    spec.textual.color = {0, 0, 0, 255};

    for (int i = 0; i < 4; i++) {
        std::stringstream ss;
        ss << "entity_" << i;

        spec.graphical = arc::TextureImage{"assets/tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 16), 0, 16, 16}};
        manager.load(ss.str(), spec);
        _textures[dir] = {ss.str()};
    }
}

std::map<pacman::Direction, std::vector<std::string>> AEntity::getTextures() const
{
    return _textures;
}

std::string AEntity::getName() const
{
    return _name;
}

std::string AEntity::getTexture(uint16_t tick)
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
    auto entityTexture = entityTextures[direction];
    if (entityTexture.size() == 0)
        return "";
    return entityTexture[tick % entityTexture.size()];
}

pacman::entity::status AEntity::getStatus() const
{
    return _status;
}

void AEntity::setStatus(pacman::entity::status status)
{
    _status = status;
}

void AEntity::setHealth(float health)
{
    _health = health;
}

void AEntity::setDmg(float dmg)
{
    _dmg = dmg;
}

float AEntity::getHealth()
{
    return _health;
}

float AEntity::getDmg()
{
    return _dmg;
}