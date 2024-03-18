/*
** EPITECH PROJECT, 2024
** Snake.cpp
** File description:
** Snake.cpp
*/

#include "arcade/IGame.hpp"
#include "Snake.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <unordered_map>

struct vec2 {
    int x;
    int y;
};

class Snake : public arc::IGame {
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
        lib.display().setWidth(ARENA_WIDTH);
        lib.display().setHeight(ARENA_HEIGHT + 1);

        resetGoal();

        initTextures(lib);

        // Fonts
        arc::FontSpecification text {
            .color = arc::Color {200, 200, 200, 255},
            .size = 16,
            .path = "regular.ttf"
        };
        lib.fonts().load("font", text);

        // Sounds
        arc::SoundSpecification sound;
        sound.path = "woosh.wav";
        lib.sounds().load("woosh", sound);

        // Musics
        arc::MusicSpecification music;
        music.path = "pacman-theme.wav";
        music.loop = true;
        music.isPlaying = false;
        lib.musics().load("pacman-theme", music);
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::Key key)
    {
        switch (key) {
            case arc::Key::Z: _playerDir = {0, -1}; lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
            case arc::Key::Q: _playerDir = {-1, 0}; lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
            case arc::Key::S: _playerDir = {0, 1};  lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
            case arc::Key::D: _playerDir = {1, 0};  lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
            case arc::Key::A:
                if (lib.display().isMusicPlaying(lib.musics().get("pacman-theme")))
                    lib.display().stopMusic(lib.musics().get("pacman-theme"));
                else
                    lib.display().playMusic(lib.musics().get("pacman-theme"), 50.0f);
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

    virtual void update([[maybe_unused]] arc::ILibrary& lib, float deltaTime)
    {
        _elapsed += deltaTime;

        while (_elapsed > UPDATE_TIME) {
            if ((_playerPos.x > 0 && _playerDir.x < 0) ||
                (_playerPos.x < ARENA_WIDTH - 1 && _playerDir.x > 0))
                _playerPos.x += _playerDir.x;

            if ((_playerPos.y > 0 && _playerDir.y < 0) ||
                (_playerPos.y < ARENA_HEIGHT - 1 && _playerDir.y > 0))
                _playerPos.y += _playerDir.y;

            if (_playerPos.x == _goalPos.x && _playerPos.y == _goalPos.y) {
                _score += 1;
                resetGoal();
            }

            _elapsed -= UPDATE_TIME;
        }
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;

        score << "Score: " << _score;

        lib.display().clear(arc::Color{0, 0, 255, 0});
        lib.display().draw(lib.textures().get("head_0_east"), 0, 0);
        lib.display().draw(lib.textures().get("head_1_east"), 0, 1);
        lib.display().draw(lib.textures().get("head_1_north"), 1, 1);
        lib.display().draw(lib.textures().get("head_0_north"), 1, 0);
        lib.display().draw(lib.textures().get("head_0_south"), 2, 0);
        lib.display().draw(lib.textures().get("head_1_south"), 2, 1);
        lib.display().draw(lib.textures().get("head_0_west"), 3, 0);
        lib.display().draw(lib.textures().get("head_1_west"), 3, 1);
        lib.display().draw(lib.textures().get("tail_east"), 0, 2);
        lib.display().draw(lib.textures().get("tail_north"), 1, 2);
        lib.display().draw(lib.textures().get("tail_south"), 2, 2);
        lib.display().draw(lib.textures().get("tail_west"), 3, 2);
        lib.display().draw(lib.textures().get("body_horizontal"), 0, 3);
        lib.display().draw(lib.textures().get("body_vertical"), 1, 3);
        lib.display().draw(lib.textures().get("body_north_west"), 0, 4);
        lib.display().draw(lib.textures().get("body_north_east"), 1, 4);
        lib.display().draw(lib.textures().get("body_south_west"), 2, 4);
        lib.display().draw(lib.textures().get("body_south_east"), 3, 4);

        lib.display().draw(lib.textures().get("Super-Candy"), _goalPos.x, _goalPos.y);

        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("font"), 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(score.str(), lib.fonts().get("font"), center, ARENA_HEIGHT );
        lib.display().flush();
    }

private:
    void resetGoal() {
        _goalPos.x = rand() % ARENA_WIDTH;
        _goalPos.y = rand() % ARENA_HEIGHT;
    }

    void initTextures(arc::ILibrary& lib)
    {
        //Onix Tileset
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
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{196, 0, 64, 64}};
        lib.textures().load("head_0_west", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{196, 64, 64, 64}};
        lib.textures().load("head_1_west", spec);

        //Onix Tail
        spec.textual.character = '*';
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 128, 64, 64}};
        lib.textures().load("tail_east", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 128, 64, 64}};
        lib.textures().load("tail_north", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{128, 128, 64, 64}};
        lib.textures().load("tail_south", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{196, 128, 64, 64}};
        lib.textures().load("tail_west", spec);

        //Onix Straight Body
        spec.textual.character = 'o';
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 196, 64, 64}};
        lib.textures().load("body_horizontal", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 196, 64, 64}};
        lib.textures().load("body_vertical", spec);

        //Onix Corner Body
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{0, 256, 64, 64}};
        lib.textures().load("body_north_west", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{64, 256, 64, 64}};
        lib.textures().load("body_north_east", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{128, 256, 64, 64}};
        lib.textures().load("body_south_west", spec);
        spec.graphical = arc::TextureImage{TILESET_ONIX, arc::Rect<uint32_t>{196, 256, 64, 64}};
        lib.textures().load("body_south_east", spec);


        //Super-Candy
        spec.textual.character = 'X';
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::Color{255, 255, 0, 255 };
        lib.textures().load("Super-Candy", spec);
    }

private:
    float _elapsed = 0;
    uint32_t _score = 0;
    vec2 _playerDir = {0, 0};
    vec2 _playerPos = {0, 0};
    vec2 _goalPos = {0, 0};
};

extern "C" arc::IGame* entrypoint()
{
    return new Snake;
}
