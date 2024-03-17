/*
** EPITECH PROJECT, 2024
** MyGame.cpp
** File description:
** MyGame.cpp
*/

#include "arcade/IGame.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>

struct vec2 {
    int x;
    int y;
};

class MyGame : public arc::IGame {
public:
    virtual std::string name() const
    {
        return "MyGame";
    }

    virtual void initialize(arc::ILibrary& lib)
    {
        lib.display().setTitle("Arcade");
        lib.display().setFramerate(30);
        lib.display().setTileSize(16);
        lib.display().setWidth(25);
        lib.display().setHeight(25);

        resetGoal();

        // Textures
        arc::TextureSpecification spec;
        spec.textual.character = '#';
        spec.textual.color = {255, 0, 0, 255};
        spec.graphical = arc::TextureImage{"tileset.png", arc::Rect<uint32_t>{0, 0, 16, 16}};
        lib.textures().load("player", spec);

        spec.textual.character = 'O';
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::Color{255, 255, 0, 255 };
        lib.textures().load("goal", spec);

        // Fonts
        arc::FontSpecification text {
            .color = arc::Color {200, 200, 200, 255},
            .size = 16,
            .path = "regular.ttf"
        };
        lib.fonts().load("font", text);

        arc::SoundSpecification sound;
        sound.path = "test.ogg";
        lib.sounds().load("woosh", sound);

        // arc::MusicSpecification music;
        // music.path = "pacman-theme.wav";
        // music.loop = true;
        // lib.musics().load("pacman-theme", music);
        // lib.display().playMusic(lib.musics().get("pacman-theme"), 50.0f);
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::Key key)
    {
        switch (key) {
            case arc::Key::Z: _playerDir = {0, -1}; lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
            case arc::Key::Q: _playerDir = {-1, 0}; lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
            case arc::Key::S: _playerDir = {0, 1}; lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
            case arc::Key::D: _playerDir = {1, 0}; lib.display().playSound(lib.sounds().get("woosh"), 50.0f); break;
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

        while (_elapsed > 0.1) {
            if ((_playerPos.x > 0 && _playerDir.x < 0) ||
                (_playerPos.x < 24 && _playerDir.x > 0))
                _playerPos.x += _playerDir.x;

            if ((_playerPos.y > 0 && _playerDir.y < 0) ||
                (_playerPos.y < 24 && _playerDir.y > 0))
                _playerPos.y += _playerDir.y;

            if (_playerPos.x == _goalPos.x && _playerPos.y == _goalPos.y) {
                _score += 100;
                resetGoal();
            }

            _elapsed -= 0.1;
        }
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;

        score << "Score: " << _score;

        lib.display().clear(arc::Color{0, 0, 255, 0});
        lib.display().draw(lib.textures().get("player"), _playerPos.x, _playerPos.y);
        lib.display().draw(lib.textures().get("goal"), _goalPos.x, _goalPos.y);

        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("font"), 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(score.str(), lib.fonts().get("font"), center, 1);
        lib.display().flush();
    }

private:
    void resetGoal() {
        _goalPos.x = rand() % 25;
        _goalPos.y = rand() % 25;
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
    return new MyGame;
}
