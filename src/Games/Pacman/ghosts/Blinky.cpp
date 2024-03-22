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
    _speed = 5;
}

void Blinky::initTextures(arc::ITextureManager& manager)
{
    arc::TextureSpecification spec;
    spec.textual.character = 'B';
    spec.textual.color = {255, 0, 0, 255};
    pacman::Direction dir = pacman::Direction::LEFT;
    for (int i = 0; i < 4; i++) {
        _textures[dir] = {};
        std::stringstream ss;
        ss << "blinky_" << i;
        for (int j = 0; j < 2; j++) {
            std::stringstream ss1;
            ss1 << ss.str() << "_" << j;
            spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 40 + j * 20), 80, 20, 20}};
            manager.load(ss1.str(), spec);
            _textures[dir].push_back(ss1.str());
        }
        dir = static_cast<pacman::Direction>(static_cast<int>(dir) + 1);
    }
    spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{0, 80, 20, 20}};
    manager.load("blinky_start", spec);
    _textures[pacman::Direction::NONE] = {"blinky_start"};
}
