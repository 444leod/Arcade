/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Blinky
*/

#include "Blinky.hpp"

using pacman::ghosts::Blinky;

Blinky::Blinky()
{
    _name = "blinky";
    _speed = 1;
}

void Blinky::initTextures(arc::ITextureManager& manager)
{
    arc::TextureSpecification spec;
    spec.textual.character = 'B';
    spec.textual.color = {255, 0, 0, 255};

    pacman::Direction direction = pacman::Direction::LEFT;

    for (int i = 0; i < 4; i++) {
        _textures[direction] = {};
        std::stringstream name_dir;
        name_dir << "blinky_" << i;
        for (int j = 0; j < 2; j++) {
            std::stringstream name_dir_frame;
            name_dir_frame << name_dir.str() << "_" << j;
            spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 40 + j * 20), 80, 20, 20}};
            manager.load(name_dir_frame.str(), spec);
            _textures[direction].push_back(name_dir_frame.str());
        }
        direction = static_cast<pacman::Direction>(static_cast<int>(direction) + 1);
    }
    spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{0, 80, 20, 20}};
    manager.load("blinky_start", spec);
    _textures[pacman::Direction::NONE] = {"blinky_start"};

    spec.textual.character = 'D';
    spec.textual.color = {0, 0, 255, 255};
    spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{0, 160, 20, 20}};
    manager.load("scaredghost_1", spec);
    spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{20, 160, 20, 20}};
    manager.load("scaredghost_2", spec);
}
