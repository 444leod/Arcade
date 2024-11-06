/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#pragma once

#include "ILibrary.hpp"
#include "SFMLDisplay.hpp"
#include "SFMLTexture.hpp"
#include "SFMLFont.hpp"
#include "SFMLAudio.hpp"

class SFMLLibrary : public arc::ILibrary {
public:
    SFMLLibrary() = default;
    virtual ~SFMLLibrary() = default;

    virtual arc::IDisplay& display() { return this->_display; }
    virtual arc::ITextureManager& textures() { return this->_textures; }
    virtual arc::IFontManager& fonts() { return this->_fonts; }
    virtual arc::ISoundManager& sounds() { return this->_sounds; }
    virtual arc::IMusicManager& musics() { return this->_musics; }

private:
    SFMLDisplay _display;
    SFMLTextureManager _textures;
    SFMLFontManager _fonts;
    SFMLSoundManager _sounds;
    SFMLMusicManager _musics;
};
