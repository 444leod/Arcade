/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLTexture
*/

#include "SFMLTexture.hpp"

void SFMLTexture::load(
    const arc::TextureSpecification &spec,
    const std::shared_ptr<sf::Texture> &texture,
    std::optional<arc::Rect<uint32_t>> rect
)
{
    this->_spec = spec;
    this->_texture = texture;

    if (rect.has_value())
    {
        this->_rect = sf::IntRect(
            rect.value().x,
            rect.value().y,
            rect.value().width,
            rect.value().height);
    }
    else
    {
        this->_rect = sf::IntRect(
            0,
            0,
            texture->getSize().x,
            texture->getSize().y);
    }
}

bool SFMLTextureManager::load(const std::string &name, const arc::TextureSpecification &specification)
{
    auto texture = std::make_shared<SFMLTexture>();

    if (std::holds_alternative<arc::TextureImage>(specification.graphical))
    {
        auto image = std::get<arc::TextureImage>(specification.graphical);

        if (this->_cache.find(image.path) != this->_cache.end())
        {
            texture->load(specification, this->_cache[image.path], image.subrect);
            this->_textures[name] = texture;
            return true;
        }

        auto sftex = std::make_shared<sf::Texture>();
        if (!sftex->loadFromFile(image.path))
            return false;

        this->_cache[image.path] = sftex;
        texture->load(specification, sftex, image.subrect);
        this->_textures[name] = texture;
        return true;
    }

    auto color = std::get<arc::Color>(specification.graphical);
    auto img = sf::Image{};
    img.create(1, 1, sf::Color(color.red, color.green, color.blue, color.alpha));
    auto sftex = std::make_shared<sf::Texture>();
    if (!sftex->loadFromImage(img))
        return false;
    texture->load(specification, sftex, std::nullopt);
    this->_textures[name] = texture;
    return true;
}

std::shared_ptr<arc::ITexture> SFMLTextureManager::get(const std::string &name)
{
    if (this->_textures.find(name) == this->_textures.end())
        return nullptr;
    return this->_textures.at(name);
}

std::map<std::string, arc::TextureSpecification> SFMLTextureManager::dump() const
{
    auto specs = std::map<std::string, arc::TextureSpecification>{};

    for (const auto &[name, texture] : this->_textures)
        specs[name] = texture->specification();

    return specs;
}
