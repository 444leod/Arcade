/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Pinky
*/

#include "Pinky.hpp"

using pacman::ghosts::Pinky;

Pinky::Pinky()
{
    _name = "pinky";
    _speed = 1;
}

void Pinky::initTextures(arc::ITextureManager& manager)
{
    arc::TextureSpecification spec;
    spec.textual.character = 'P';
    spec.textual.color = {255, 0, 255, 255};
    pacman::Direction dir = pacman::Direction::LEFT;
    for (uint32_t i = 0; i < 4; i++) {
        _textures[dir] = {};
        std::stringstream ss;
        ss << "pinky_" << i;
        for (uint32_t j = 0; j < 2; j++) {
            std::stringstream ss1;
            ss1 << ss.str() << "_" << j;
            #if V2
            spec.graphical = arc::TextureImage{"assets/pacman/images/pokemon_spritesheet.png", arc::Rect<uint32_t>{(i * 48 + j * 24), 72, 24, 24}};
            #else
            spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{(i * 40 + j * 20), 100, 20, 20}};
            #endif
            manager.load(ss1.str(), spec);
            _textures[dir].push_back(ss1.str());
        }
        dir = static_cast<pacman::Direction>(static_cast<int>(dir) + 1);
    }
    _textures[pacman::Direction::NONE] = {"pinky_0_0"};
    #if V2
    spec.textual.character = 'D';
    spec.textual.color = {0, 0, 255, 255};
    for (uint32_t i = 0; i < 4; i++) {
        std::stringstream name_dir;
        name_dir << "scaredpinky_" << i;
        for (uint32_t j = 0; j < 2; j++) {
            std::stringstream name_dir_frame;
            name_dir_frame << name_dir.str() << "_" << j;
            spec.graphical = arc::TextureImage{"assets/pacman/images/pokemon_spritesheet.png", arc::Rect<uint32_t>{192 + (i * 48 + j * 24), 72, 24, 24}};
            manager.load(name_dir_frame.str(), spec);
        }
    }
    #endif
}
