/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Inky
*/

#include "Inky.hpp"

using pacman::ghosts::Inky;

Inky::Inky()
{
    _name = "inky";
    _speed = 0.6f;
}

void Inky::initTextures(arc::ITextureManager& manager)
{
    arc::TextureSpecification spec;
    spec.textual.character = 'I';
    spec.textual.color = {0, 255, 255, 255};
    pacman::Direction dir = pacman::Direction::LEFT;
    for (int i = 0; i < 4; i++) {
        _textures[dir] = {};
        std::stringstream ss;
        ss << "inky_" << i;
        for (int j = 0; j < 2; j++) {
            std::stringstream ss1;
            ss1 << ss.str() << "_" << j;
            spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 40 + j * 20), 120, 20, 20}};
            manager.load(ss1.str(), spec);
            _textures[dir].push_back(ss1.str());
        }
        dir = static_cast<pacman::Direction>(static_cast<int>(dir) + 1);
    }
    spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{0, 120, 20, 20}};
    manager.load("inky_start", spec);
    _textures[pacman::Direction::NONE] = {"inky_start"};
}
