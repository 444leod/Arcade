/*
** EPITECH PROJECT, 2024
** MyGame.cpp
** File description:
** MyGame.cpp
*/

#include "IGame.hpp"
#include "MapHandler.hpp"
#include "Player.hpp"
#include "IEntity.hpp"
#include "ghosts/Blinky.hpp"
#include "ghosts/Pinky.hpp"
#include "ghosts/Inky.hpp"
#include "ghosts/Clyde.hpp"
#include "RandomNumberGenerator.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>

class MyGame : public arc::IGame {
public:
    virtual std::string name() const
    {
        return "MyGame";
    }


    virtual void initialize(arc::ILibrary& lib)
    {
        lib.display().setTitle("Arcade");
        lib.display().setFramerate(60);
        lib.display().setTileSize(32);

        arc::TextureSpecification spec;
        spec.textual.character = '.';
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::TextureImage{"assets/pacman/board.png", arc::Rect<uint32_t>{1024, 0, 32, 32}};
        lib.textures().load("coin", spec);

        spec.textual.character = 'O';
        spec.textual.color = {255, 0, 0, 255};
        spec.graphical = arc::TextureImage{"assets/pacman/board.png", arc::Rect<uint32_t>{1056, 0, 32, 32}};
        lib.textures().load("fruit", spec);

        spec.textual.character = ' ';
        spec.textual.color = {255, 255, 255, 255};
        for (uint16_t i = 0; i <= 33; ++i) {
            std::stringstream ss;
            ss << "wall_" << (i + 2);
            spec.graphical = arc::TextureImage{"assets/pacman/board.png", arc::Rect<uint32_t>{static_cast<uint16_t>(i * 32), 0, 32, 32}};
            lib.textures().load(ss.str(), spec);
        }

        spec.textual.character = ' ';
        spec.textual.color = {0, 0, 0, 255};
        spec.graphical = arc::Color{0, 0, 0, 255};
        lib.textures().load("empty", spec);

        // Fonts
        arc::FontSpecification text {
            .color = arc::Color {200, 200, 200, 255},
            .size = 16,
            .path = "assets/pacman/emulogic.ttf"
        };
        lib.fonts().load("emulogic", text);

        lib.display().setWidth(_mapHandler.getMapSizeX());
        lib.display().setHeight(_mapHandler.getMapSizeY() + 5);
        _player->setPos(_mapHandler.getPlayerPos());
        _player->setPosf(_mapHandler.getPlayerPos());
        _player->initTextures(lib.textures());

        for (auto& ghost : _ghosts) {
            ghost->initTextures(lib.textures());
        }

        rng::RandomNumberGenerator rng;
        for (auto &ghost : _ghosts) {
            Vec2i ghostPos;
            do {
                ghostPos = {rng.generate() % _mapHandler.getMapSizeX(), rng.generate() % _mapHandler.getMapSizeY()};
            } while (_mapHandler.isTileWalkable(ghostPos) == false);
            ghost->setPos(ghostPos);
            ghost->setPosf(ghostPos);
        }
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::Key key)
    {
        switch (key) {
            case arc::Key::Z:
                _player->queueMove({0, -1});
                break;
            case arc::Key::Q:
                _player->queueMove({-1, 0});
                break;
            case arc::Key::S:
                _player->queueMove({0, 1});
                break;
            case arc::Key::D:
                _player->queueMove({1, 0});
                break;
            case arc::Key::A:
                break;
            default: break;
        }
    }

    virtual void onMouseButtonPressed(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::MouseButton button,
        [[maybe_unused]] int32_t x,
        [[maybe_unused]] int32_t y
    )
    {
    }

    virtual void update([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]]float deltaTime)
    {
        _elapsed += deltaTime;
        _elapsed1 += deltaTime;
        Vec2i playerPos = _player->getPos();

        _player->move(deltaTime, _mapHandler);
        for (auto& ghost : _ghosts) {
            ghost->move(deltaTime, _mapHandler);
        }
        if (_elapsed1 >= 0.2) {
            rng::RandomNumberGenerator rng;
            for (auto& ghost : _ghosts) {
                pacman::Direction direction = pacman::Direction(rng.generate() % 4);
                ghost->setMoveQueue({pacman::DirectionToVec2[direction]});
            }
            _elapsed1 -= 0.2;
        }
        if (_elapsed >= 0.1) {
            _fruitVisibility = !_fruitVisibility;
            _playerState = (_playerState + 1) % 2;
            _elapsed -= 0.1;
        }

        _player->movef(deltaTime, _mapHandler);
        std::vector<Vec2f> ghostPos;
        for (auto& ghost : _ghosts) {
            ghost->movef(deltaTime, _mapHandler);
            ghostPos.push_back(ghost->getPosf());
        }
        _pacmanState = _mapHandler.processPlayerPos(_player->getPos(), _player->getDirection(), _score, ghostPos, _player->getPosf());
        _player->setPos(_mapHandler.getPlayerPos());
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;

        score << "Score: " << _score;

        lib.display().clear(arc::Color{0, 0, 0, 0});

        for (auto [pos, texture] : _mapHandler.dumpTextures()) {
            if (texture == "fruit" && !_fruitVisibility)
                continue;
            lib.display().draw(lib.textures().get(texture), pos.x, pos.y);
        }

        std::vector<std::shared_ptr<pacman::IEntity>> entities;
        entities.push_back(_player);
        for (auto& ghost : _ghosts) {
            entities.push_back(ghost);
        }

        for (auto& entity : entities) {
            std::string texture = entity->getTexture(_playerState);
            if (texture.length() == 0)
                continue;
            lib.display().draw(lib.textures().get(entity->getTexture(_playerState)), entity->getPosf().x, entity->getPosf().y);
        }

        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("emulogic"), 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(score.str(), lib.fonts().get("emulogic"), center, _mapHandler.getMapSizeX() + 3);
        lib.display().flush();
        if (_pacmanState == pacman::player::State::DEAD) {
            lib.display().close();
        }
    }

private:
    float _elapsed = 0;
    float _elapsed1 = 0;
    uint32_t _score = 0;
    uint32_t _steps = 0;
    bool _fruitVisibility = true;
    uint32_t _playerState = 0;
    pacman::player::State _pacmanState = pacman::player::State::ALIVE;

    MapHandler _mapHandler;
    std::shared_ptr<pacman::IEntity> _player = std::make_shared<pacman::player::Player>();
    std::vector<std::shared_ptr<pacman::IEntity>> _ghosts = {
        std::make_shared<pacman::ghosts::Blinky>(),
        std::make_shared<pacman::ghosts::Pinky>(),
        std::make_shared<pacman::ghosts::Inky>(),
        std::make_shared<pacman::ghosts::Clyde>()
    };
};

extern "C" arc::IGame* entrypoint()
{
    return new MyGame;
}

