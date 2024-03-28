/*
** EPITECH PROJECT, 2024
** SnakeGame.cpp
** File description:
** SnakeGame.cpp
*/

#include "IGame.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include "GameObjects/SuperCandy.hpp"
#include "GameObjects/SnakeObjectManager.hpp"
#include "SharedLibraryType.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>

class SnakeGame : public arc::IGame {
public:
    virtual std::string name() const
    {
        return "Snake";
    }

    virtual void initialize(arc::ILibrary& lib)
    {
        lib.display().setTitle("Snake");
        lib.display().setFramerate(60);
        lib.display().setTileSize(64);
        lib.display().setWidth(ARENA_WIDTH + 2);
        lib.display().setHeight(ARENA_HEIGHT + 1 + 2);

        // Textures
        initTextures(lib);

        // Fonts
        arc::FontSpecification text {
            .color = arc::Color {200, 200, 200, 255},
            .size = 32,
            .path = FONT_POKEMON
        };
        lib.fonts().load("Pokemon", text);

        // Sounds
        // arc::SoundSpecification sound;
        // sound.path = "woosh.wav";
        // lib.sounds().load("woosh", sound);
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::Key key)
    {
        bool playSound = false;
        switch (key) {
            case arc::Key::Z: playSound = _snake.setDirection({0, -1}); break;
            case arc::Key::Q: playSound = _snake.setDirection({-1, 0}); break;
            case arc::Key::S: playSound = _snake.setDirection({0, 1}); break;
            case arc::Key::D: playSound = _snake.setDirection({1, 0}); break;
            default: break;
        }
        (void)playSound;
        // if (playSound)
            // lib.display().playSound(lib.sounds().get("woosh"), 50.0f);
    }

    virtual void onMouseButtonPressed(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::MouseButton button,
        [[maybe_unused]] int32_t x,
        [[maybe_unused]] int32_t y
    )
    {
    }

    virtual void update([[maybe_unused]] arc::ILibrary& lib, float deltaTime)
    {
        Vec2i objectCollided = _snake.update(_snakeManager.getPos(), deltaTime);
        _snakeManager.update(objectCollided, _snake, deltaTime);
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;

        score << "Score: " << _snake.getScore();

        lib.display().clear(arc::Color{0, 0, 255, 0});
        draw_arena(lib);
        if (_snake.getAlive()) {
            for (auto &part : _snake.dump()) {
                lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
            }
        }
        for (auto &part : _snakeManager.dump()) {
                lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
            }

        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("Pokemon"), 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(score.str(), lib.fonts().get("Pokemon"), center, ARENA_HEIGHT + 2);
        lib.display().flush();
    }

    virtual uint64_t score() const
    {
        return _snake.getScore();
    }

private:
    void initTextures(arc::ILibrary& lib)
    {
        arc::TextureSpecification spec;

        //Onix Head
        spec.textual.character = 'O';
        spec.textual.color = {255, 0, 0, 255};
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 0, 64, 64}};
        lib.textures().load("head_0_east", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 64, 64, 64}};
        lib.textures().load("head_1_east", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 0, 64, 64}};
        lib.textures().load("head_0_north", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 64, 64, 64}};
        lib.textures().load("head_1_north", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{128, 0, 64, 64}};
        lib.textures().load("head_0_south", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{128, 64, 64, 64}};
        lib.textures().load("head_1_south", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{192, 0, 64, 64}};
        lib.textures().load("head_0_west", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{192, 64, 64, 64}};
        lib.textures().load("head_1_west", spec);

        //Onix Tail
        spec.textual.character = '*';
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 128, 64, 64}};
        lib.textures().load("tail_east", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 128, 64, 64}};
        lib.textures().load("tail_north", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{128, 128, 64, 64}};
        lib.textures().load("tail_south", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{192, 128, 64, 64}};
        lib.textures().load("tail_west", spec);

        //Onix Straight Body
        spec.textual.character = 'o';
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 192, 64, 64}};
        lib.textures().load("body_horizontal", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 192, 64, 64}};
        lib.textures().load("body_vertical", spec);

        //Onix Corner Body
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 256, 64, 64}};
        lib.textures().load("body_north_west", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 256, 64, 64}};
        lib.textures().load("body_south_west", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{128, 256, 64, 64}};
        lib.textures().load("body_south_east", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{192, 256, 64, 64}};
        lib.textures().load("body_north_east", spec);

        //Empty
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{128, 192, 64, 64}};
        lib.textures().load("empty", spec);

        //Arena
        spec.textual.character = ' ';
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{16, 176, 16, 16}};
        lib.textures().load("arena_0", spec);
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{16, 160, 16, 16}};
        lib.textures().load("arena_north_edge", spec);

        spec.textual.character = '+';
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{16, 176, 16, 16}};
        lib.textures().load("arena_north_edge_solid", spec);
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{16, 192, 16, 16}};
        lib.textures().load("arena_south_edge", spec);
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{0, 176, 16, 16}};
        lib.textures().load("arena_west_edge", spec);
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{32, 176, 16, 16}};
        lib.textures().load("arena_east_edge", spec);

        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{48, 192, 16, 16}};
        lib.textures().load("arena_north_west_edge", spec);
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{64, 192, 16, 16}};
        lib.textures().load("arena_north_east_edge", spec);
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{48, 160, 16, 16}};
        lib.textures().load("arena_south_west_edge", spec);
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{62, 160, 16, 16}};
        lib.textures().load("arena_south_east_edge", spec);

        //Super Candy
        spec.textual.character = 'X';
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::TextureImage{SUPER_CANDY};
        lib.textures().load("super_candy", spec);
    }

    void draw_arena(arc::ILibrary& lib)
    {
        // Edges
        lib.display().draw(lib.textures().get("arena_north_edge_solid"), 0, 0);
        lib.display().draw(lib.textures().get("arena_north_edge_solid"), ARENA_WIDTH + 1, 0);
        for (int x = 1; x < ARENA_WIDTH + 1; x++) {
            lib.display().draw(lib.textures().get("arena_north_edge_solid"), x, 0);
            lib.display().draw(lib.textures().get("arena_north_edge"), x, 1);
            lib.display().draw(lib.textures().get("arena_south_edge"), x, ARENA_HEIGHT + 1);
        }
        for (int y = 2; y < ARENA_HEIGHT + 1; y++) {
            lib.display().draw(lib.textures().get("arena_west_edge"), 0, y);
            lib.display().draw(lib.textures().get("arena_east_edge"), ARENA_WIDTH + 1, y);
        }

        // Corners
        lib.display().draw(lib.textures().get("arena_north_west_edge"), 0, 1);
        lib.display().draw(lib.textures().get("arena_north_east_edge"), ARENA_WIDTH + 1, 1);
        lib.display().draw(lib.textures().get("arena_south_west_edge"), 0, ARENA_HEIGHT + 1);
        lib.display().draw(lib.textures().get("arena_south_east_edge"), ARENA_WIDTH + 1, ARENA_HEIGHT + 1);

        // Inside arena
        for (int y = 2; y < ARENA_HEIGHT + 1; y++)
            for (int x = 1; x < ARENA_WIDTH + 1; x++)
                lib.display().draw(lib.textures().get("arena_0"), x, y);
        
        // Menu background
        for (int x = 0; x < ARENA_WIDTH + 2; x++)
            lib.display().draw(lib.textures().get("arena_0"), x, ARENA_HEIGHT + 2);
    }

private:
    SnakeObject _snake = SnakeObject();
    SnakeObjectManager _snakeManager = SnakeObjectManager();
};

extern "C" arc::IGame* entrypoint()
{
    return new SnakeGame;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::GAME;
}

extern "C" const char *name()
{
    return "Snake";
}