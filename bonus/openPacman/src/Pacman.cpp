/*
** EPITECH PROJECT, 2024
** Pacman.cpp
** File description:
** Pacman.cpp
*/

#include "IGame.hpp"
#include "MapHandler.hpp"
#include "Player.hpp"
#include "IEntity.hpp"
#include "RandomNumberGenerator.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>

class Pacman : public arc::IGame {
public:
    virtual void initialize(arc::ILibrary& lib)
    {
        std::srand(std::time(nullptr));

        lib.display().setTitle("Open-PACMAN");
        lib.display().setFramerate(60);
        lib.display().setTileSize(32);

        arc::TextureSpecification spec;
        spec.textual.character = '.';
        //yellow
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::TextureImage{"assets/pacman/board.png", arc::Rect<uint32_t>{1024, 0, 32, 32}};
        lib.textures().load("coin", spec);

        spec.textual.character = 'O';
        spec.textual.color = {255, 0, 0, 255};
        spec.graphical = arc::TextureImage{"assets/pacman/board.png", arc::Rect<uint32_t>{1056, 0, 32, 32}};
        lib.textures().load("pacgum", spec);

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

        spec.textual.character = ' ';
        spec.textual.color = {255, 255, 255, 255};
        spec.graphical = arc::Color{0, 0, 255, 255};
        lib.textures().load("wall", spec);

        // Fonts
        arc::FontSpecification text;
        text.color = arc::Color{200, 200, 200, 255};
        text.size = 16;
        text.path = "assets/pacman/emulogic.ttf";
        lib.fonts().load("emulogic", text);

        lib.display().setHeight(24);
        lib.display().setWidth(21);

        _player->initTextures(lib.textures());

        spec.textual.character = 'G';
        spec.textual.color = {0, 0, 0, 255};
        for (int i = 0; i < 4; i++) {
            std::stringstream ss;
            ss << "deadghost_" << i;
            spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 20), 200, 20, 20}};
            lib.textures().load(ss.str(), spec);
        }
}

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::KeyCode key, [[maybe_unused]]bool shift)
    {
        switch (key) {
            case arc::KeyCode::Z:
                _player->queueMove({0, -1});
                break;
            case arc::KeyCode::UP:
                _player->queueMove({0, -1});
                break;
            case arc::KeyCode::Q:
                _player->queueMove({-1, 0});
                break;
            case arc::KeyCode::LEFT:
                _player->queueMove({-1, 0});
                break;
            case arc::KeyCode::S:
                _player->queueMove({0, 1});
                break;
            case arc::KeyCode::DOWN:
                _player->queueMove({0, 1});
                break;
            case arc::KeyCode::D:
                _player->queueMove({1, 0});
                break;
            case arc::KeyCode::RIGHT:
                _player->queueMove({1, 0});
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
        if (_mapHandler == nullptr)
            return;
        _elapsed += deltaTime;
        _elapsed1 += deltaTime;

        Vec2i playerPos = _player->getPos();

        // allow players & ghosts to move to their next cell
        _player->move(deltaTime, *_mapHandler);
        for (auto& ghost : _ghosts)
            ghost->move(deltaTime, *_mapHandler);

        // Random movement for each ghost
        rng::RandomNumberGenerator rng;
        if (_elapsed1 >= 0.2) {
            for (auto& ghost : _ghosts) {
                pacman::Direction direction = pacman::Direction(rng.generate() % 4);
                ghost->setMoveQueue({pacman::DirectionToVec2[direction]});
            }
            _elapsed1 -= 0.2;
        }

        // Update a tick for animations, each 0.1s
        if (_elapsed >= 0.1) {
            _tick++;
            _elapsed -= 0.1;
        }

        // get the float position of entities for smooth rendering
        _player->movef(deltaTime, *_mapHandler);
        for (auto& ghost : _ghosts)
            ghost->movef(deltaTime, *_mapHandler);

        // make the player & the ghosts interact with the map
        _mapHandler->processPlayerPos(_player, _ghosts, _score);
        _mapHandler->collideGhost(_player, _ghosts, _tick);

        if (_player->getStatus() == pacman::entity::status::DEAD) {
            _pacmanState = pacman::player::State::DEAD;
        }
        _mapHandler->checkChunks(playerPos);
    }

    virtual void draw(arc::ILibrary& lib)
    {
        lib.display().clear(arc::Color{0, 0, 0, 0});

        if (_mapHandler == nullptr) {
            lib.display().print("Loading...", lib.fonts().get("emulogic"), 0, 0);
            lib.display().flush();
            _mapHandler = std::make_shared<pacman::MapHandler>(lib.textures(), _ghosts);
            _player->setPosf(_mapHandler->getPlayerPos());
            _player->setPos(_mapHandler->getPlayerPos());
        }

        Vec2f playerPos = _player->getPosf();

        // Calculate the offset
        Vec2f offset = playerPos - Vec2f(10, 10);

        // Render the map
        for (auto [pos, texture] : _mapHandler->dumpTexturesByCenterPos(_player->getPos().x, _player->getPos().y)) {
            if (texture == "pacgum" && _tick % 2 == 0)
                continue;
            // Subtract the offset from the position
            lib.display().draw(lib.textures().get(texture), pos.x - offset.x, pos.y - offset.y);
        }

        // Render the entities
        std::vector<std::shared_ptr<pacman::IEntity>> entities = {_player};
        for (auto& ghost : _ghosts)
            entities.push_back(ghost);

        for (auto& entity : entities) {
            std::string texture = entity->getTexture(_tick);
            if (texture.length() == 0)
                continue;
            // Subtract the offset from the position
            Vec2f pos = entity->getPosf();
            float x = pos.x;
            float y = pos.y;
            if (std::abs(x - playerPos.x) <= 11 && std::abs(y - playerPos.y) <= 11)
            lib.display().draw(lib.textures().get(entity->getTexture(_tick)), entity->getPosf().x - offset.x, entity->getPosf().y - offset.y);
        }
        //render the score in the middle of the screen, below the map
        std::stringstream score;
        score << "Score: " << _score;
        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("emulogic"), 0, 0).width;
        auto center = (width - textWidth) / 2;
        lib.display().print(score.str(), lib.fonts().get("emulogic"), center, 23);

        lib.display().flush();
        if (_pacmanState == pacman::player::State::DEAD) {
            lib.display().close();
        }
    }

    virtual uint64_t score() const
    {
        return _score;
    }

private:
    float _elapsed = 0;
    float _elapsed1 = 0;
    uint32_t _score = 0;
    uint32_t _steps = 0;
    std::vector<std::vector<int>> _map;
    std::vector<Vec2i> _path;
    bool _pacgumVisibility = true;
    uint32_t _tick = 0;
    pacman::player::State _pacmanState = pacman::player::State::ALIVE;

    std::shared_ptr<pacman::MapHandler> _mapHandler = nullptr;
    std::shared_ptr<pacman::IEntity> _player = std::make_shared<pacman::player::Player>();
    std::vector<std::shared_ptr<pacman::IEntity>> _ghosts = {
    };
};

extern "C" arc::IGame* entrypoint()
{
    return new Pacman;
}

extern "C" const char *name()
{
    return "OpenPacman";
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::GAME;
}
