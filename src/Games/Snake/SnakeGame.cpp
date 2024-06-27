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
#include "GameObjects/Snake.hpp"

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <sstream>

class SnakeGame : public arc::IGame {
public:
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
        arc::SoundSpecification sound;
        sound.path = "assets/snake/sounds/woosh.wav";
        lib.sounds().load("woosh", sound);
        sound.path = "assets/snake/sounds/crunch.wav";
        lib.sounds().load("crunch", sound);

        arc::MusicSpecification music;
        music.path = "assets/snake/sounds/Porte.wav";
        music.loop = true;
        lib.musics().load("Porte", music);

        music.path = "assets/snake/sounds/GameOver.wav";
        lib.musics().load("GameOver", music);

        lib.musics().play("Porte", 100.0f);

        // Set the random
        std::srand(std::time(nullptr));
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::KeyCode key, [[maybe_unused]] bool shift)
    {
        bool playSound = false;
        switch (key) {
            case arc::KeyCode::Z: playSound = _snake.setDirection({0, -1}); break;
            case arc::KeyCode::Q: playSound = _snake.setDirection({-1, 0}); break;
            case arc::KeyCode::S: playSound = _snake.setDirection({0, 1}); break;
            case arc::KeyCode::D: playSound = _snake.setDirection({1, 0}); break;
            default: break;
        }
        if (playSound)
            lib.sounds().play("woosh", 30.0f);
    }

    virtual void onKeyDown([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::KeyCode key)
    {
    }

    virtual void onKeyReleased([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::KeyCode key)
    {
    }

    virtual void onMouseButtonPressed(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::MouseButton button,
        [[maybe_unused]] int32_t x,
        [[maybe_unused]] int32_t y
    )
    {
    }

    virtual void onMouseButtonDown(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::MouseButton button,
        [[maybe_unused]] int32_t x,
        [[maybe_unused]] int32_t y
    )
    {
    }

    virtual void onMouseButtonReleased(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::MouseButton button,
        [[maybe_unused]] int32_t x,
        [[maybe_unused]] int32_t y
    )
    {
    }

    virtual void onJoystickButtonPressed(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::JoystickButton button,
        [[maybe_unused]] std::uint32_t id)
    {
    }

    virtual void onJoystickButtonDown(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::JoystickButton button,
        [[maybe_unused]] std::uint32_t id)
    {
    }

    virtual void onJoystickButtonReleased(
        [[maybe_unused]] arc::ILibrary& lib,
        [[maybe_unused]] arc::JoystickButton button,
        [[maybe_unused]] std::uint32_t id)
    {
    }

    virtual void onJoystickMove(
        [[maybe_unused]] arc::ILibrary& lib,
        arc::JoystickAxis axis,
        uint32_t id)
    {
        if (id != 0)
            return;
        if (axis.x != 0 || axis.y != 0) {
            _snake.setDirection({axis.x, axis.y});
            lib.sounds().play("woosh", 30.0f);
        }

    }

    virtual void update([[maybe_unused]] arc::ILibrary& lib, float deltaTime)
    {
        Vec2i objectCollided = _snake.update(_snakeManager.getPos(), deltaTime);
        _snakeManager.update(objectCollided, _snake, deltaTime);
        if (objectCollided != Vec2i{-1, -1})
            lib.sounds().play("crunch", 100.0f);
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;
        score << "Score: " << _snake.getScore();
        std::size_t width = lib.display().width();

        lib.display().clear(arc::Color{0, 0, 0, 255});
        draw_arena(lib);
        if (_snake.getAlive()) {
            for (auto &part : _snake.dump()) {
                lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
            }
        }
        else {
            if (lib.musics().isPlaying("GameOver") == false)
                lib.musics().play("GameOver", 100.0f);
            float textWidth = lib.display().measure("Game Over", lib.fonts().get("Pokemon"), 0, 0).width;
            float center = (width - textWidth) / 2;
            lib.musics().stop("Porte");
            lib.display().print("Game Over", lib.fonts().get("Pokemon"), center, ARENA_HEIGHT / 2);
        }
        for (auto &part : _snakeManager.dump()) {
            lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
        }

        float textWidth = lib.display().measure(score.str(), lib.fonts().get("Pokemon"), 0, 0).width;
        float center = (width - textWidth) / 2;
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
        spec.textual.color = {0, 0, 0, 255};
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

        //Consumables
        spec.textual.character = 'X';
        //Super Candy
        spec.textual.color = {0, 0, 255, 255};
        spec.graphical = arc::TextureImage{SUPER_CANDY_PATH};
        lib.textures().load("super_candy", spec);

        //Tamato Berry
        spec.textual.color = {255, 0, 0, 255};
        spec.graphical = arc::TextureImage{TAMATO_BERRY_PATH};
        lib.textures().load("tamato_berry", spec);

        //Aguav Berry
        spec.textual.color = {0, 255, 0, 255};
        spec.graphical = arc::TextureImage{AGUAV_BERRY_PATH};
        lib.textures().load("aguav_berry", spec);
    }

    void draw_arena(arc::ILibrary& lib)
    {
        // Edges
        for (int x = 1; x < ARENA_WIDTH + 1; x++) {
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
    }

private:
    ASnakeObject _snake = Snake();
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
