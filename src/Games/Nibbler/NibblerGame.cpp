/*
** EPITECH PROJECT, 2024
** NibblerGame.cpp
** File description:
** NibblerGame.cpp
*/

#include "IGame.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"
#include "Vec2.hpp"
#include "SharedLibraryType.hpp"
#include "CSVParser.hpp"
#include "GameObjects/NibblerObjectManager.hpp"
#include "GameObjects/Nibbler.hpp"

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>

class NibblerGame : public arc::IGame {
public:
    virtual void initialize(arc::ILibrary& lib)
    {
        // Map
        CSVParser<int> parser(_mapNames[0]);
        for (auto &mapName : _mapNames) {
            if (mapName.empty())
                throw(std::runtime_error("Map Empty"));
            std::ifstream file(mapName);
            if (!file.is_open())
                throw (std::runtime_error("Could not open file"));
            if (std::filesystem::exists(mapName) == false)
                throw(std::runtime_error("Map file not found"));
            parser.setFilename(mapName);
            parser.parse();
            _currentMap = parser.getData();
            maps.push_back(_currentMap);
        }

        _currentMap = maps[0];

        _nibblerManager.initMapObjects(_currentMap);

        _nibbler = Nibbler(_currentMap);

        // Display
        lib.display().setTitle("Nibbler");
        lib.display().setFramerate(60);
        lib.display().setTileSize(40);
        lib.display().setWidth(_currentMap[0].size());
        lib.display().setHeight(_currentMap.size() + 1);

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
        sound.path = "assets/nibbler/sounds/level_up.wav";
        lib.sounds().load("LevelUp", sound);

        //Music
        arc::MusicSpecification music;
        music.path = "assets/nibbler/sounds/Cieux.wav";
        music.loop = true;
        lib.musics().load("Cieux", music);

        music.path = "assets/snake/sounds/GameOver.wav";
        lib.musics().load("GameOver", music);

        lib.musics().play("Cieux", 100.0f);
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::KeyCode key, [[maybe_unused]] bool shift)
    {
        switch (key) {
            case arc::KeyCode::Z: _nibbler.setDirectionQueue({0, -1}); break;
            case arc::KeyCode::Q: _nibbler.setDirectionQueue({-1, 0}); break;
            case arc::KeyCode::S: _nibbler.setDirectionQueue({0, 1}); break;
            case arc::KeyCode::D: _nibbler.setDirectionQueue({1, 0}); break;
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
        if (_nibblerManager.checkWin(_nibbler)) {
            nextMap(deltaTime, lib);
            return;
        }
        std::vector<Vec2i> blockingPos = _nibblerManager.getBlockingPos();

        Vec2i headPos = _nibbler.getPositions()[0];
        headPos.x += _nibbler.getDirectionQueue().first;
        headPos.y += _nibbler.getDirectionQueue().second;
        if (std::find(blockingPos.begin(), blockingPos.end(), headPos) == blockingPos.end() &&
            _nibbler.getDirectionQueue() != std::make_pair(0, 0)) {
            _nibbler.setDirection(_nibbler.getDirectionQueue());
            _nibbler.setDirectionQueue({0, 0});
        }

        _nibblerManager.update(
            _nibbler.update(_nibblerManager.getPos(), deltaTime),
            _nibbler,
            deltaTime
        );
    }

    virtual void draw(arc::ILibrary& lib)
    {
        std::stringstream score;
        score << "Score: " << _nibbler.getScore();
        std::size_t width = lib.display().width();

        lib.display().clear(arc::Color{0, 0, 255, 0});
        draw_arena(lib);
        if (_nibbler.getAlive()) {
            for (auto &part : _nibbler.dump()) {
                lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
            }
        }
        else {
            if (lib.musics().isPlaying("GameOver") == false)
                lib.musics().play("GameOver", 100.0f);
            float textWidth = lib.display().measure("Game Over", lib.fonts().get("Pokemon"), 0, 0).width;
            float center = (width - textWidth) / 2;
            lib.musics().stop("Cieux");
            lib.display().print("Game Over", lib.fonts().get("Pokemon"), center, _currentMap.size() / 2);
        }
        for (auto &part : _nibblerManager.dump()) {
                lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
            }

        float textWidth = lib.display().measure(score.str(), lib.fonts().get("Pokemon"), 0, 0).width;
        float center = (width - textWidth) / 2;
        lib.display().print(score.str(), lib.fonts().get("Pokemon"), center, _currentMap.size());
        lib.display().flush();
    }

    virtual uint64_t score() const
    {
        return _nibbler.getScore();
    }

private:
    void nextMap(float deltaTime, arc::ILibrary& lib)
    {
        if (_nibbler.getPositions().size() == 4) {
            lib.sounds().play("LevelUp", 100.0f);
            uint16_t tmpScore = _nibbler.getScore();
            _currentMapIndex++;
            if (_currentMapIndex >= _mapNames.size()) {
                _currentMapIndex = 0;
            }
            _currentMap = maps[_currentMapIndex];
            _nibblerManager.initMapObjects(_currentMap);
            _nibbler = Nibbler(_currentMap);
            _nibbler.setScore(tmpScore);
            return;
        }
        _elapsed += deltaTime;
        while (_elapsed > BASE_SPEED) {
            if (_nibbler.getPositions().size() > 4)
                _nibbler.shrink(1);
            _elapsed -= BASE_SPEED;
        }
    }

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

        spec.textual.character = '+';
        spec.graphical = arc::TextureImage{TILESET_CAVE, arc::Rect<uint32_t>{3*16, 6*16, 16, 16}};
        lib.textures().load("rock", spec);

        //Consumables
        spec.textual.character = 'X';
        //Super Candy
        spec.textual.color = {0, 0, 255, 255};
        spec.graphical = arc::TextureImage{SUPER_CANDY_PATH};
        lib.textures().load("super_candy", spec);
    }

    void draw_arena(arc::ILibrary& lib)
    {
        for (uint64_t i = 0; _currentMap.size() + 1 > i; i++) {
            for (uint64_t j = 0; _currentMap[0].size() > j; j++) {
                lib.display().draw(lib.textures().get("arena_0"), j, i);
            }
        }
    }

private:
    std::vector<std::string> _mapNames = {
        "assets/nibbler/maps/map0.csv",
        "assets/nibbler/maps/map1.csv",
        "assets/nibbler/maps/map2.csv",
        "assets/nibbler/maps/map3.csv",
    };
    std::vector<std::vector<std::vector<int>>> maps;
    std::vector<std::vector<int>> _currentMap;
    NibblerObjectManager _nibblerManager;
    Nibbler _nibbler;
    float _elapsed = 0;
    uint16_t _currentMapIndex = 0;
};

extern "C" arc::IGame* entrypoint()
{
    return new NibblerGame;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::GAME;
}

extern "C" const char *name()
{
    return "Nibbler";
}