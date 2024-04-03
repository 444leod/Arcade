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
#include "SharedLibraryType.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>

// using pacman::MapHandler;
// using pacman::player::Player;

class Pacman : public arc::IGame {
public:
    virtual void initialize(arc::ILibrary& lib)
    {
        lib.display().setTitle("Arcade");
        lib.display().setFramerate(60);
        lib.display().setTileSize(32);

        // Textures
        arc::TextureSpecification spec;
        spec.textual.character = 'P';
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::TextureImage{"assets/tileset.png", arc::Rect<uint32_t>{0, 0, 16, 16}};
        lib.textures().load("player", spec);

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
            .path = "assets/regular.ttf"
        };
        lib.fonts().load("font", text);

        lib.display().setWidth(_mapHandler.getMapSizeX());
        lib.display().setHeight(_mapHandler.getMapSizeY() + 5);
        _player->setPos(_mapHandler.getPlayerPos());
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
        _steps++;
        _player->move(deltaTime, _mapHandler);
        _mapHandler.processPlayerPos(_player->getPos(), _player->getDirection());
        _player->setPos(_mapHandler.getPlayerPos());
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;

        score << "Score: " << _score;

        lib.display().clear(arc::Color{0, 0, 0, 0});

        for (auto [pos, texture] : _mapHandler.dumpTextures()) {
            lib.display().draw(lib.textures().get(texture), pos.x, pos.y);
        }

        // Vec2i initialPos = _player->getPos();
        // Vec2f playerPos = _player->getPosf();
        // playerPos.x = initialPos.x + playerPos.x;
        // playerPos.y = initialPos.y + playerPos.y;
        Vec2i playerPos = _player->getPos();
        lib.display().draw(lib.textures().get("player"), playerPos.x, playerPos.y);
        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("font"), 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(score.str(), lib.fonts().get("font"), center, _mapHandler.getMapSizeX() + 3);

        lib.display().flush();
    }

    virtual uint64_t score() const
    {
        return _score;
    }

private:
    float _elapsed = 0;
    uint64_t _score = 0;
    uint32_t _steps = 0;

    MapHandler _mapHandler;
    std::unique_ptr<pacman::IEntity> _player = std::make_unique<pacman::player::Player>();
};

std::ostream& operator<<(std::ostream& os, const Vec2i& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vec2f& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

extern "C" arc::IGame* entrypoint()
{
    return new Pacman;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::GAME;
}

extern "C" const char *name()
{
    return "Pacman";
}
