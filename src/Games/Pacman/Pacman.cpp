/*
** EPITECH PROJECT, 2024
** MyGame.cpp
** File description:
** MyGame.cpp
*/

#include "IGame.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>

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
        lib.display().setTileSize(32);

        // Textures
        arc::TextureSpecification spec;
        spec.textual.character = 'P';
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::TextureImage{"assets/tileset.png", arc::Rect<uint32_t>{0, 0, 16, 16}};
        lib.textures().load("player", spec);

        spec.textual.character = '.';
        spec.textual.color = {255, 255, 0, 255};
        spec.graphical = arc::Color{255, 255, 0, 255 };
        lib.textures().load("coin", spec);

        spec.textual.character = 'O';
        spec.textual.color = {255, 0, 0, 255};
        spec.graphical = arc::Color{255, 0, 0, 255 };
        lib.textures().load("fruit", spec);

        spec.textual.character = ' ';
        spec.textual.color = {255, 255, 255, 255};
        spec.graphical = arc::Color{255, 255, 255, 255 };
        lib.textures().load("wall", spec);

        spec.textual.character = ' ';
        spec.textual.color = {0, 0, 0, 255};
        spec.graphical = arc::Color{0, 0, 0, 255 };
        lib.textures().load("void", spec);

        // Fonts
        arc::FontSpecification text {
            .color = arc::Color {200, 200, 200, 255},
            .size = 16,
            .path = "assets/regular.ttf"
        };
        lib.fonts().load("font", text);

        // Sounds
        // arc::SoundSpecification sound;
        // sound.path = "assets/woosh.wav";
        // lib.sounds().load("woosh", sound);

        // // Musics
        // arc::MusicSpecification music;
        // music.path = "assets/pacman-theme.wav";
        // music.loop = true;
        // lib.musics().load("pacman-theme", music);

        std::ifstream file("src/Games/Pacman/pacman.txt");
        if (!file.is_open())
            throw std::runtime_error("Error: can't open the map.\n");

        std::string line;
        int y = 0;
        size_t teleportersNumber = 0;
        size_t lineSize = 0;
        while (std::getline(file, line)) {
            if (lineSize == 0)
                lineSize = line.size();
            else if (line.size() != lineSize)
                throw std::runtime_error("Error: map not rectangular\n");
            for (size_t x = 0; x < line.size(); x++) {
                if (line[x] == 'P') {
                    _playerPos.x = x;
                    _playerPos.y = y;
                    line[x] = ' ';
                } else if (line[x] == 'T') {
                    if (teleportersNumber >= 2)
                        throw std::runtime_error("Error: too many teleporters\n");
                    if (teleportersNumber == 0) {
                        _teleporters.first.first = x;
                        _teleporters.first.second = y;
                        teleportersNumber++;
                    } else {
                        _teleporters.second.first = x;
                        _teleporters.second.second = y;
                        teleportersNumber++;
                    }
                }
            }
            _map.push_back(line);
            y++;
        }
        if (teleportersNumber != 2 && teleportersNumber != 0)
            throw std::runtime_error("Error: not enough teleporters\n");
        if (_playerPos.x == -1 || _playerPos.y == -1)
            throw std::runtime_error("Error: player not found\n");
        lib.display().setWidth(lineSize);
        lib.display().setHeight(_map.size() + 1);
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::Key key)
    {
        switch (key) {
            case arc::Key::Z:
                _playerDir = {0, -1};
                // lib.display().playSound(lib.sounds().get("woosh"), 50.0f);
                break;
            case arc::Key::Q:
                _playerDir = {-1, 0};
                // lib.display().playSound(lib.sounds().get("woosh"), 50.0f);
                break;
            case arc::Key::S:
                _playerDir = {0, 1};
                // lib.display().playSound(lib.sounds().get("woosh"), 50.0f);
                break;
            case arc::Key::D:
                _playerDir = {1, 0};
                // lib.display().playSound(lib.sounds().get("woosh"), 50.0f);
                break;
            case arc::Key::A:
                // if (lib.display().isMusicPlaying(lib.musics().get("pacman-theme")))
                    // lib.display().stopMusic(lib.musics().get("pacman-theme"));
                // else
                    // lib.display().playMusic(lib.musics().get("pacman-theme"), 50.0f);
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
        while (_elapsed > 0.1) {
            if (((_playerPos.x > 0 && _playerDir.x < 0) || ((size_t)_playerPos.x < _map[0].size() - 1 && _playerDir.x > 0)) && _map[_playerPos.y][_playerPos.x + _playerDir.x] != '#')
                _playerPos.x += _playerDir.x;

            if (((_playerPos.y > 0 && _playerDir.y < 0) || ((size_t)_playerPos.y < _map.size() - 1 && _playerDir.y > 0)) && _map[_playerPos.y + _playerDir.y][_playerPos.x] != '#')
                _playerPos.y += _playerDir.y;

            if (_map[_playerPos.y][_playerPos.x] == '.') {
                _score += 10;
                _map[_playerPos.y][_playerPos.x] = ' ';
            }
            if (_map[_playerPos.y][_playerPos.x] == 'o') {
                _score += 100;
                _map[_playerPos.y][_playerPos.x] = ' ';
            }
            if (_map[_playerPos.y][_playerPos.x] == 'T') {
                _score += 10;
                _map[_playerPos.y][_playerPos.x] = 't';
            }
            if (_map[_playerPos.y][_playerPos.x] == 't') {
                if ((size_t)_playerPos.x == _teleporters.first.first && (size_t)_playerPos.y == _teleporters.first.second) {
                    _playerPos.x = _teleporters.second.first;
                    _playerPos.y = _teleporters.second.second;
                } else {
                    _playerPos.x = _teleporters.first.first;
                    _playerPos.y = _teleporters.first.second;
                }
                if (_map[_playerPos.y][_playerPos.x] == 'T') {
                    _score += 10;
                    _map[_playerPos.y][_playerPos.x] = 't';
                }
            }

            _elapsed -= 0.1;
        }
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;

        score << "Score: " << _score;

        lib.display().clear(arc::Color{255, 255, 255, 0});
        size_t y = 1;
        std::pair<uint32_t, uint32_t> teleporter1;
        for (auto &line : _map) {
            for (size_t x = 0; x < line.size(); x++) {
                switch (line[x]) {
                    case 'P':
                        lib.display().draw(lib.textures().get("void"), x, y);
                        break;
                    case 'T':
                        lib.display().draw(lib.textures().get("coin"), x, y);
                        break;
                    case '.':
                        lib.display().draw(lib.textures().get("coin"), x, y);
                        break;
                    case 'o':
                        lib.display().draw(lib.textures().get("fruit"), x, y);
                        break;
                    case '#':
                        lib.display().draw(lib.textures().get("wall"), x, y);
                        break;
                    default:
                        lib.display().draw(lib.textures().get("void"), x, y);
                        break;
                }
            }
            y++;
        }
        lib.display().draw(lib.textures().get("player"), _playerPos.x, _playerPos.y + 1);
        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("font"), 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(score.str(), lib.fonts().get("font"), center, 0);

        std::stringstream currentPos;
        currentPos << "X: " << _playerPos.x << " Y: " << _playerPos.y << " \"" << _map[_playerPos.y][_playerPos.x] << "\"";
        lib.display().print(currentPos.str(), lib.fonts().get("font"), 30, 30);

        lib.display().flush();
    }

private:
    float _elapsed = 0;
    uint32_t _score = 0;
    vec2 _playerDir = {0, 0};
    vec2 _playerPos = {-1, -1};
    std::vector<std::string> _map;
    std::pair<std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>> _teleporters;
};

extern "C" arc::IGame* entrypoint()
{
    return new MyGame;
}
