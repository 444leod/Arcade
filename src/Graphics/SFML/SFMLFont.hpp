/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLFont
*/

#pragma once

#include "IFontManager.hpp"
#include <SFML/Graphics.hpp>

class SFMLFont : public arc::IFont {
public:
    SFMLFont() = default;
    virtual ~SFMLFont() = default;

    bool init(const arc::FontSpecification& spec);

    virtual const arc::FontSpecification& specification() const { return this->_spec; }
    const sf::Color& color() const { return this->_color; }
    std::size_t size() const { return this->_size; }
    const sf::Font& font() const { return this->_font; }

private:
    sf::Color _color = {};
    std::size_t _size = 0;
    sf::Font _font = {};
    arc::FontSpecification _spec = {};
};

class SFMLFontManager : public arc::IFontManager {
public:
    SFMLFontManager() = default;
    virtual ~SFMLFontManager() = default;

    virtual bool load(const std::string& name, const arc::FontSpecification& spec);
    virtual std::shared_ptr<arc::IFont> get(const std::string &name);
    virtual std::map<std::string, arc::FontSpecification> dump() const;

private:
    std::map<std::string, std::shared_ptr<SFMLFont>> _fonts;
};
