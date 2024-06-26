/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLDisplay
*/

#pragma once

#include "IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <deque>

class SFMLDisplay : public arc::IDisplay {
public:
    SFMLDisplay();
    virtual ~SFMLDisplay() = default;

    virtual void setTitle(const std::string& title);
    virtual void setFramerate(uint32_t framerate);
    virtual void setTileSize(std::size_t size);
    virtual void setWidth(std::size_t width);
    virtual void setHeight(std::size_t height);

    virtual std::string title() const { return this->_title; }
    virtual uint32_t framerate() const { return this->_framerate; }
    virtual std::size_t tileSize() const { return this->_tileSize; }
    virtual std::size_t width() const { return this->_width; }
    virtual std::size_t height() const { return this->_height; }

    virtual void update([[maybe_unused]] float deltaTime);

    virtual bool pollEvent(arc::Event& event);
    virtual const arc::Joystick& joystick(std::uint16_t id) const;

    virtual void close();
    virtual bool opened() const { return this->_window.isOpen(); }

    virtual void clear(arc::Color color);

    virtual void draw(std::shared_ptr<arc::ITexture> texture, float x, float y);
    virtual void draw(std::shared_ptr<arc::ITexture> texture, float x, float y, float scale);

    virtual void print(const std::string& string, std::shared_ptr<arc::IFont> font, float x, float y);
    virtual arc::Rect<float> measure(const std::string& string, std::shared_ptr<arc::IFont> font, float x, float y);

    virtual void flush();

private:
    virtual void _resizeWindow();
    static arc::KeyCode _mapSFMLKey(sf::Keyboard::Key key);
    static sf::Keyboard::Key _mapArcKey(arc::KeyCode key);
    static arc::MouseButton _mapSFMLMouseButton(sf::Mouse::Button button);
    static sf::Mouse::Button _mapArcMouseButton(arc::MouseButton button);

private:
    sf::RenderWindow _window;
    sf::VideoMode _mode;
    sf::Vector2f _offset;
    std::string _title;
    uint32_t _framerate;
    std::size_t _width;
    std::size_t _height;
    std::size_t _tileSize;
    std::deque<arc::Event> _events;
    arc::Joystick _joysticks[sf::Joystick::Count];
};
