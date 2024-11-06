/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLFont
*/

#include "SFMLFont.hpp"

bool SFMLFont::init(const arc::FontSpecification &spec)
{
    this->_spec = spec;
    if (!this->_font.loadFromFile(spec.path))
        return false;
    this->_color = sf::Color(spec.color.red, spec.color.green, spec.color.blue, spec.color.alpha);
    this->_size = spec.size;
    return true;
}

bool SFMLFontManager::load(const std::string &name, const arc::FontSpecification &spec)
{
    auto attribute = std::make_shared<SFMLFont>();

    if (!attribute->init(spec))
        return false;
    this->_fonts[name] = attribute;
    return true;
}

std::shared_ptr<arc::IFont> SFMLFontManager::get(const std::string &name)
{
    if (this->_fonts.find(name) == this->_fonts.end())
        return nullptr;
    return this->_fonts.at(name);
}

std::map<std::string, arc::FontSpecification> SFMLFontManager::dump() const
{
    auto specs = std::map<std::string, arc::FontSpecification>{};

    for (const auto &[name, font] : this->_fonts)
        specs[name] = font->specification();

    return specs;
}