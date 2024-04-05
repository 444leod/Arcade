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

class NibblerGame : public arc::IGame {
public:
    virtual void initialize(arc::ILibrary& lib)
    {
        // Map
        CSVParser<int> parser("assets/nibbler/map.csv");
        parser.parse();
        _map = parser.getData();
        _nibblerManager.initMapObjects(_map);

        _nibbler = Nibbler(_map);

        // Display
        lib.display().setTitle("Nibbler");
        lib.display().setFramerate(60);
        lib.display().setTileSize(40);
        lib.display().setWidth(_map[0].size());
        lib.display().setHeight(_map.size() + 1);

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
    }

    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::Key key)
    {
        switch (key) {
            case arc::Key::Z: _nibbler.setDirectionQueue({0, -1}); break;
            case arc::Key::Q: _nibbler.setDirectionQueue({-1, 0}); break;
            case arc::Key::S: _nibbler.setDirectionQueue({0, 1}); break;
            case arc::Key::D: _nibbler.setDirectionQueue({1, 0}); break;
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

        lib.display().clear(arc::Color{0, 0, 255, 0});
        draw_arena(lib);
        if (_nibbler.getAlive()) {
            for (auto &part : _nibbler.dump()) {
                lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
            }
        }
        for (auto &part : _nibblerManager.dump()) {
                lib.display().draw(lib.textures().get(part.second), part.first.x, part.first.y);
            }

        auto width = lib.display().width();
        auto textWidth = lib.display().measure(score.str(), lib.fonts().get("Pokemon"), 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(score.str(), lib.fonts().get("Pokemon"), center, _map.size());
        lib.display().flush();
    }

    virtual uint64_t score() const
    {
        return _nibbler.getScore();
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
        for (uint64_t i = 0; _map.size() + 1 > i; i++) {
            for (uint64_t j = 0; _map[0].size() > j; j++) {
                lib.display().draw(lib.textures().get("arena_0"), j, i);
            }
        }
    }

private:
   std::vector<std::vector<int>> _map;
   NibblerObjectManager _nibblerManager;
   Nibbler _nibbler;
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