/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLDisplay
*/

#include "SFMLDisplay.hpp"
#include "SFMLTexture.hpp"
#include "SFMLFont.hpp"

SFMLDisplay::SFMLDisplay()
{
    this->_tileSize = 16;
    this->_width = 80;
    this->_height = 60;
    this->_framerate = 0;
    this->_title = "Arcade";

    this->_mode = sf::VideoMode::getFullscreenModes()[0];
    this->_resizeWindow();
    this->_window.create(this->_mode, this->_title, sf::Style::Fullscreen);
    this->_window.setKeyRepeatEnabled(false);
}

void SFMLDisplay::setTitle(const std::string &title)
{
    this->_title = title;
    this->_window.setTitle(title);
}

void SFMLDisplay::setFramerate(uint32_t framerate)
{
    this->_framerate = framerate;
    this->_window.setFramerateLimit(framerate);
}

void SFMLDisplay::setTileSize(std::size_t size)
{
    this->_tileSize = size;
    this->_resizeWindow();
}

void SFMLDisplay::setWidth(std::size_t width)
{
    this->_width = width;
    this->_resizeWindow();
}

void SFMLDisplay::setHeight(std::size_t height)
{
    this->_height = height;
    this->_resizeWindow();
}

void SFMLDisplay::update([[maybe_unused]] float deltaTime)
{
    sf::Event event;
    arc::Event e;

    for (std::uint32_t id = 0; id < sf::Joystick::Count; id++)
    {
        if (!sf::Joystick::isConnected(id))
            continue;
        double x = sf::Joystick::getAxisPosition(id, sf::Joystick::Axis::X) / 100.0;
        double y = sf::Joystick::getAxisPosition(id, sf::Joystick::Axis::Y) / 100.0;
        this->_joysticks[id].setAxis(x, y);
    }

    while (this->_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->_window.close();
            break;
        case sf::Event::KeyPressed:
            e.type = arc::EventType::KEY_PRESSED;
            e.key.code = SFMLDisplay::_mapSFMLKey(event.key.code);
            e.key.shift = event.key.shift;
            this->_events.push_back(std::move(e));
            break;
        case sf::Event::MouseButtonPressed:
            e.type = arc::EventType::MOUSE_BUTTON_PRESSED;
            e.mouse.button = SFMLDisplay::_mapSFMLMouseButton(event.mouseButton.button);
            e.mouse.x = event.mouseButton.x / this->_tileSize;
            e.mouse.y = event.mouseButton.y / this->_tileSize;
            this->_events.push_back(std::move(e));
            break;
        case sf::Event::JoystickButtonPressed:
            e.type = arc::EventType::JOYSTICK_BUTTON_PRESSED;
            e.joystick.button = static_cast<arc::JoystickButton>(event.joystickButton.button);
            e.joystick.id = event.joystickButton.joystickId;
            this->_events.push_back(std::move(e));
            break;
        default:
            break;
        }
    }
}

bool SFMLDisplay::pollEvent(arc::Event &event)
{
    if (this->_events.empty())
        return false;

    event = this->_events.front();
    this->_events.pop_front();
    return true;
}

const arc::Joystick &SFMLDisplay::joystick(std::uint16_t id) const
{
    return this->_joysticks[id];
}

void SFMLDisplay::close()
{
    this->_window.close();
}

void SFMLDisplay::clear(arc::Color color)
{
    this->_window.clear(sf::Color{color.red, color.green, color.blue, color.alpha});
}

void SFMLDisplay::draw(std::shared_ptr<arc::ITexture> texture, float x, float y)
{
    if (texture == nullptr)
        return;

    auto rect = sf::RectangleShape{sf::Vector2f{static_cast<float>(this->_tileSize), static_cast<float>(this->_tileSize)}};
    auto tex = std::dynamic_pointer_cast<SFMLTexture>(texture);

    rect.setTexture(tex->raw().get());
    rect.setTextureRect(tex->subrect());
    rect.setPosition(
        x * this->_tileSize + this->_offset.x,
        y * this->_tileSize + this->_offset.y);
    this->_window.draw(rect);
}

void SFMLDisplay::draw(std::shared_ptr<arc::ITexture> texture, float x, float y, float scale)
{
    if (texture == nullptr)
        return;

    auto rect = sf::RectangleShape{sf::Vector2f{static_cast<float>(this->_tileSize), static_cast<float>(this->_tileSize)}};
    auto tex = std::dynamic_pointer_cast<SFMLTexture>(texture);

    rect.setTexture(tex->raw().get());
    rect.setTextureRect(tex->subrect());
    rect.setPosition(
        x * this->_tileSize + this->_offset.x,
        y * this->_tileSize + this->_offset.y);
    rect.setScale(scale, scale);
    this->_window.draw(rect);
}

void SFMLDisplay::print(const std::string &string, std::shared_ptr<arc::IFont> font, float x, float y)
{
    if (font == nullptr)
        return;

    auto attr = std::dynamic_pointer_cast<SFMLFont>(font);
    auto text = sf::Text(sf::String(string), attr->font(), attr->size());
    text.setFillColor(attr->color());
    text.setPosition(
        x * this->_tileSize + this->_offset.x,
        y * this->_tileSize + this->_offset.y);
    this->_window.draw(text);
}

arc::Rect<float> SFMLDisplay::measure(const std::string &string, std::shared_ptr<arc::IFont> font, float x, float y)
{
    if (font == nullptr)
        return arc::Rect<float>{0.f, 0.f, 0.f, 0.f};

    auto attr = std::dynamic_pointer_cast<SFMLFont>(font);
    auto text = sf::Text(sf::String(string), attr->font(), attr->size());
    text.setFillColor(attr->color());
    text.setPosition(x + this->_offset.x, y + this->_offset.y);
    auto bounds = text.getLocalBounds();
    return {bounds.left, bounds.top, bounds.width / this->_tileSize, bounds.height / this->_tileSize};
}

void SFMLDisplay::flush()
{
    this->_window.display();
}

arc::KeyCode SFMLDisplay::_mapSFMLKey(sf::Keyboard::Key key)
{
    if (key < 26) return static_cast<arc::KeyCode>(key);
    if (key == sf::Keyboard::Up) return arc::KeyCode::UP;
    if (key == sf::Keyboard::Down) return arc::KeyCode::DOWN;
    if (key == sf::Keyboard::Left) return arc::KeyCode::LEFT;
    if (key == sf::Keyboard::Right) return arc::KeyCode::RIGHT;
    if (key == sf::Keyboard::Space) return arc::KeyCode::SPACE;
    if (key == sf::Keyboard::Enter) return arc::KeyCode::ENTER;
    if (key == sf::Keyboard::Escape) return arc::KeyCode::ESCAPE;
    if (key == sf::Keyboard::Tab) return arc::KeyCode::TAB;
    if (key == sf::Keyboard::BackSpace) return arc::KeyCode::DELETE;
    return arc::KeyCode::UNKNOWN;
}

sf::Keyboard::Key SFMLDisplay::_mapArcKey(arc::KeyCode key)
{
    if (static_cast<uint64_t>(key) < 26) return static_cast<sf::Keyboard::Key>(key);
    if (key == arc::KeyCode::UP) return sf::Keyboard::Up;
    if (key == arc::KeyCode::DOWN) return sf::Keyboard::Down;
    if (key == arc::KeyCode::LEFT) return sf::Keyboard::Left;
    if (key == arc::KeyCode::RIGHT) return sf::Keyboard::Right;
    if (key == arc::KeyCode::SPACE) return sf::Keyboard::Space;
    if (key == arc::KeyCode::ENTER) return sf::Keyboard::Enter;
    if (key == arc::KeyCode::ESCAPE) return sf::Keyboard::Escape;
    return sf::Keyboard::Unknown;
}

arc::MouseButton SFMLDisplay::_mapSFMLMouseButton(sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left) return arc::MouseButton::LEFT;
    if (button == sf::Mouse::Right) return arc::MouseButton::RIGHT;
    if (button == sf::Mouse::Middle) return arc::MouseButton::MIDDLE;
    return arc::MouseButton::UNKNOWN;
}

sf::Mouse::Button SFMLDisplay::_mapArcMouseButton(arc::MouseButton button)
{
    if (button == arc::MouseButton::LEFT) return sf::Mouse::Left;
    if (button == arc::MouseButton::RIGHT) return sf::Mouse::Right;
    if (button == arc::MouseButton::MIDDLE) return sf::Mouse::Middle;
    return sf::Mouse::ButtonCount;
}

void SFMLDisplay::_resizeWindow()
{
    this->_offset.x = (this->_mode.width - this->_width * this->_tileSize) / 2.f;
    this->_offset.y = (this->_mode.height - this->_height * this->_tileSize) / 2.f;
}
