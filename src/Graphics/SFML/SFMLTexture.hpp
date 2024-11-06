/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLTexture
*/

#pragma once

#include "ITextureManager.hpp"

#include <SFML/Graphics.hpp>
#include <map>

class SFMLTexture : public arc::ITexture {
public:
    SFMLTexture() = default;
    virtual ~SFMLTexture() = default;

    void load(
        const arc::TextureSpecification& spec,
        const std::shared_ptr<sf::Texture>& texture,
        std::optional<arc::Rect<uint32_t>> rect);

    virtual const arc::TextureSpecification& specification() const { return this->_spec; }
    const std::shared_ptr<sf::Texture>& raw() const { return this->_texture; }
    const sf::IntRect subrect() const { return this->_rect; }

private:
    std::shared_ptr<sf::Texture> _texture;
    sf::IntRect _rect;
    arc::TextureSpecification _spec;
};

class SFMLTextureManager : public arc::ITextureManager {
public:
    SFMLTextureManager() = default;
    virtual ~SFMLTextureManager() = default;

    virtual bool load(const std::string& name, const arc::TextureSpecification& specification);
    virtual std::shared_ptr<arc::ITexture> get(const std::string& name);
    virtual std::map<std::string, arc::TextureSpecification> dump() const;

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> _cache;
    std::map<std::string, std::shared_ptr<SFMLTexture>> _textures;
};
