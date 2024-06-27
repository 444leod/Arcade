/*
** EPITECH PROJECT, 2024
** SFML.cpp
** File description:
** SFML.cpp
*/

#include "ILibrary.hpp"
#include "SharedLibraryType.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <cmath>
#include <memory>
#include <iostream>

class SFMLTexture : public arc::ITexture {
public:
    SFMLTexture() = default;
    virtual ~SFMLTexture() = default;

    void load(
        const arc::TextureSpecification& spec,
        const std::shared_ptr<sf::Texture>& texture,
        std::optional<arc::Rect<uint32_t>> rect
    )
    {
        this->_spec = spec;
        this->_texture = texture;

        if (rect.has_value()) {
            this->_rect = sf::IntRect(
                rect.value().x,
                rect.value().y,
                rect.value().width,
                rect.value().height
            );
        } else {
            this->_rect = sf::IntRect(
                0,
                0,
                texture->getSize().x,
                texture->getSize().y
            );
        }
    }

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

    virtual bool load(const std::string& name, const arc::TextureSpecification& specification)
    {
        auto texture = std::make_shared<SFMLTexture>();

        if (std::holds_alternative<arc::TextureImage>(specification.graphical)) {
            auto image = std::get<arc::TextureImage>(specification.graphical);

            if (this->_cache.find(image.path) != this->_cache.end()) {
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

    virtual std::shared_ptr<arc::ITexture> get(const std::string& name)
    {
        if (this->_textures.find(name) == this->_textures.end())
            return nullptr;
        return this->_textures.at(name);
    }

    virtual std::map<std::string, arc::TextureSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::TextureSpecification>{};

        for (const auto& [name, texture] : this->_textures)
            specs[name] = texture->specification();

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> _cache;
    std::map<std::string, std::shared_ptr<SFMLTexture>> _textures;
};

class SFMLFont : public arc::IFont {
public:
    SFMLFont() = default;
    virtual ~SFMLFont() = default;

    bool init(const arc::FontSpecification& spec)
    {
        this->_spec = spec;
        if (!this->_font.loadFromFile(spec.path))
            return false;
        this->_color =  sf::Color(spec.color.red, spec.color.green, spec.color.blue, spec.color.alpha);
        this->_size = spec.size;
        return true;
    }

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

    virtual bool load(const std::string& name, const arc::FontSpecification& spec)
    {
        auto attribute = std::make_shared<SFMLFont>();

        if (!attribute->init(spec))
            return false;
        this->_fonts[name] = attribute;
        return true;
    }

    virtual std::shared_ptr<arc::IFont> get(const std::string &name)
    {
        if (this->_fonts.find(name) == this->_fonts.end())
            return nullptr;
        return this->_fonts.at(name);
    }

    virtual std::map<std::string, arc::FontSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::FontSpecification>{};

        for (const auto& [name, font] : this->_fonts)
            specs[name] = font->specification();

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<SFMLFont>> _fonts;
};

class SFMLSound : public arc::ISound {
public:
    SFMLSound() = default;
    virtual ~SFMLSound() = default;

    bool init(const arc::SoundSpecification& spec)
    {
        this->_spec = spec;
        if (!_buffer.loadFromFile(spec.path)) {
            const int sampleRate = 44100;

            std::vector<sf::Int16> samples(sampleRate);
            for (size_t i = 0; i < samples.size(); ++i) {
                samples[i] = 0;
            }

            _buffer.loadFromSamples(&samples[0], samples.size(), 1, sampleRate);
        }
        return true;
    }

    void setBuffer(void)
    {
        _sound.setBuffer(_buffer);
    }

    virtual void play() { _sound.play(); }
    virtual void stop() { this->_sound.stop(); }
    virtual sf::Sound::Status getStatus() const { return this->_sound.getStatus(); }
    virtual void setVolume(float volume) { this->_sound.setVolume(volume); }

    virtual const arc::SoundSpecification& specification() const { return this->_spec; }
    const sf::Sound& sound() const { return this->_sound; }

private:
    sf::Sound _sound = {};
    sf::SoundBuffer _buffer = {};
    arc::SoundSpecification _spec = {};
};

class SFMLSoundManager : public arc::ISoundManager {
public:
    SFMLSoundManager() = default;
    virtual ~SFMLSoundManager() = default;

    virtual bool load(const std::string& name, const arc::SoundSpecification& spec)
    {
        auto sound = std::make_shared<SFMLSound>();

        if (!sound->init(spec))
            return false;

        this->_sounds[name] = sound;
        this->_sounds[name]->setBuffer();
        return true;
    }

    virtual std::shared_ptr<arc::ISound> get(const std::string &name)
    {
        return this->_sounds.at(name);
    }

    virtual std::map<std::string, arc::SoundSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::SoundSpecification>{};

        for (auto& [name, sound] : this->_sounds) {
            specs[name] = sound->specification();
        }

        return specs;
    }

    virtual void play(const std::string& name, const float volume)
    {
        this->_sounds.at(name)->setVolume(volume);
        this->_sounds.at(name)->play();
    }

    virtual void stop(const std::string& name)
    {
        this->_sounds.at(name)->stop();
    }

    virtual bool isPlaying(const std::string& name)
    {
        return this->_sounds.at(name)->getStatus() == sf::Sound::Playing;
    }

private:
    std::map<std::string, std::shared_ptr<SFMLSound>> _sounds;
};

class SFMLMusic : public arc::IMusic {
public:
    SFMLMusic() = default;
    virtual ~SFMLMusic() = default;

    bool init(const arc::MusicSpecification& spec)
    {
        this->_spec = spec;
        if (!this->_music.openFromFile(spec.path))
            return false;

        this->_music.setLoop(spec.loop);
        if (spec.startOffset != -1)
            this->_music.setPlayingOffset(sf::seconds(spec.startOffset));
        if (spec.isPlaying)
            this->_music.play();
        return true;
    }

    virtual void play() {
        this->_music.play();
    }
    virtual void stop() { this->_music.stop(); }
    virtual void setVolume(float volume) { this->_music.setVolume(volume); }
    virtual sf::Music::Status getStatus() const { return this->_music.getStatus(); }

    virtual const arc::MusicSpecification& specification() const { return this->_spec; }
    const sf::Music& music() const { return this->_music; }

private:
    sf::Music _music = {};
    arc::MusicSpecification _spec = {};
};

class SFMLMusicManager : public arc::IMusicManager {
public:
    SFMLMusicManager() = default;
    virtual ~SFMLMusicManager() = default;

    virtual bool load(const std::string& name, const arc::MusicSpecification& spec)
    {
        auto music = std::make_shared<SFMLMusic>();

        if (!music->init(spec))
            return false;

        this->_musics[name] = music;
        return true;
    }

    virtual std::shared_ptr<arc::IMusic> get(const std::string &name)
    {
        return this->_musics.at(name);
    }

    virtual std::map<std::string, arc::MusicSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::MusicSpecification>{};

        for (auto& [name, music] : this->_musics) {
            arc::MusicSpecification spec = music->specification();
            spec.isPlaying = music->getStatus() == sf::Music::Playing;
            if (spec.isPlaying)
                spec.startOffset = music->music().getPlayingOffset().asSeconds();

            specs[name] = spec;
        }

        return specs;
    }

    virtual void play(const std::string& name, const float volume)
    {
        this->_musics.at(name)->setVolume(volume);
        this->_musics.at(name)->play();
    }

    virtual void stop(const std::string& name)
    {
        this->_musics.at(name)->stop();
    }

    virtual bool isPlaying(const std::string& name)
    {
        return this->_musics.at(name)->getStatus() == sf::Music::Playing;
    }

private:
    std::map<std::string, std::shared_ptr<SFMLMusic>> _musics;
};

class SFMLDisplay : public arc::IDisplay {
public:
    SFMLDisplay()
    {
        this->_tileSize = 16;
        this->_width = 80;
        this->_height = 60;
        this->_framerate = 0;
        this->_title = "Arcade";

        sf::VideoMode mode;
        mode.width = this->_width * this->_tileSize;
        mode.height = this->_height * this->_tileSize;
        mode.bitsPerPixel = 32;
        this->_window.create(mode, this->_title, sf::Style::Titlebar | sf::Style::Close);
        this->_window.setKeyRepeatEnabled(false);
    }

    virtual ~SFMLDisplay() = default;

    virtual void setTitle(const std::string& title)
    {
        this->_title = title;
        this->_window.setTitle(title);
    }

    virtual void setFramerate(uint32_t framerate)
    {
        this->_framerate = framerate;
        this->_window.setFramerateLimit(framerate);
    }

    virtual void setKeyDownDelay(arc::KeyCode key, float delay)
    {
        this->_keyDownDelays[key] = delay;
    }

    virtual void setTileSize(std::size_t size)
    {
        this->_tileSize = size;
        this->_resizeWindow();
    }

    virtual void setWidth(std::size_t width)
    {
        this->_width = width;
        this->_resizeWindow();
    }

    virtual void setHeight(std::size_t height)
    {
        this->_height = height;
        this->_resizeWindow();
    }

    virtual std::string title() const
    {
        return this->_title;
    }

    virtual uint32_t framerate() const
    {
        return this->_framerate;
    }

    virtual std::size_t tileSize() const
    {
        return this->_tileSize;
    }

    virtual std::size_t width() const
    {
        return this->_width;
    }

    virtual std::size_t height() const
    {
        return this->_height;
    }

    static arc::KeyCode MapSFMLKey(sf::Keyboard::Key key)
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

    static sf::Keyboard::Key MapArcKey(arc::KeyCode key)
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

    static arc::MouseButton MapSFMLMouseButton(sf::Mouse::Button button)
    {
        if (button == sf::Mouse::Left) return arc::MouseButton::LEFT;
        if (button == sf::Mouse::Right) return arc::MouseButton::RIGHT;
        if (button == sf::Mouse::Middle) return arc::MouseButton::MIDDLE;
        return arc::MouseButton::UNKNOWN;
    }

    static sf::Mouse::Button MapArcMouseButton(arc::MouseButton button)
    {
        if (button == arc::MouseButton::LEFT) return sf::Mouse::Left;
        if (button == arc::MouseButton::RIGHT) return sf::Mouse::Right;
        if (button == arc::MouseButton::MIDDLE) return sf::Mouse::Middle;
        return sf::Mouse::ButtonCount;
    }

    virtual void update([[maybe_unused]] float deltaTime)
    {
        sf::Event event;
        arc::Event e;
        static float elapsed = 0;
        elapsed += deltaTime;

        for (std::uint32_t id = 0; id < sf::Joystick::Count; id++) {
            #ifndef NO_JOY
            if (!sf::Joystick::isConnected(id)) continue;
            double x = sf::Joystick::getAxisPosition(id, sf::Joystick::Axis::X) / 100.0;
            double y = sf::Joystick::getAxisPosition(id, sf::Joystick::Axis::Y) / 100.0;

            #else
            if (id != 0) break;
            double x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
            double y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
            #endif
            if (_joystickAxis[id].x == x && _joystickAxis[id].y == y) continue;
            _joystickAxis[id] = {x, y};
            e.eventType = arc::EventType::MOVE;
            e.keyType = arc::KeyType::JOYSTICK;
            e.joystick.id = id;
            e.joystick.axis = {x, y};
            this->_events.push_back(std::move(e));
        }

        while (this->_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    this->_window.close();
                    break;
                }
                case sf::Event::KeyPressed: {
                    e.eventType = arc::EventType::PRESSED;
                    e.keyType = arc::KeyType::KEY;
                    e.key.code = SFMLDisplay::MapSFMLKey(event.key.code);
                    e.key.shift = event.key.shift;

                    this->_events.push_back(std::move(e));
                    float delay = 0;
                    if (this->_keyDownDelays.find(e.key.code) != this->_keyDownDelays.end())
                        delay = this->_keyDownDelays[e.key.code];
                    this->_downKeys.push_back({e.key.code, delay, elapsed});
                    #ifdef NO_JOY
                    e.type = arc::EventType::JOYSTICK_BUTTON_PRESSED;
                    e.joystick.button = static_cast<arc::JoystickButton>(e.key.code);
                    e.joystick.id = 0;
                    this->_events.push_back(std::move(e));
                    #endif
                    break;
                }
                case sf::Event::KeyReleased: {
                    e.eventType = arc::EventType::RELEASED;
                    e.keyType = arc::KeyType::KEY;
                    e.key.code = SFMLDisplay::MapSFMLKey(event.key.code);
                    e.key.shift = event.key.shift;
                    this->_events.push_back(std::move(e));
                    for (auto it = this->_downKeys.begin(); it != this->_downKeys.end(); it++) {
                        if (std::get<0>(*it) == e.key.code) {
                            this->_downKeys.erase(it);
                            break;
                        }
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    e.eventType = arc::EventType::PRESSED;
                    e.keyType = arc::KeyType::MOUSE_BUTTON;
                    e.mouse.button = SFMLDisplay::MapSFMLMouseButton(event.mouseButton.button);
                    e.mouse.x = event.mouseButton.x;
                    e.mouse.y = event.mouseButton.y;
                    this->_events.push_back(std::move(e));
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    e.eventType = arc::EventType::RELEASED;
                    e.keyType = arc::KeyType::MOUSE_BUTTON;
                    e.mouse.button = SFMLDisplay::MapSFMLMouseButton(event.mouseButton.button);
                    e.mouse.x = event.mouseButton.x;
                    e.mouse.y = event.mouseButton.y;
                    this->_events.push_back(std::move(e));
                    for (auto it = this->_downMouseButtons.begin(); it != this->_downMouseButtons.end(); it++) {
                        if (std::get<0>(*it) == e.mouse.button) {
                            this->_downMouseButtons.erase(it);
                            break;
                        }
                    }
                    break;
                }
                case sf::Event::JoystickButtonPressed:
                {
                    e.eventType = arc::EventType::PRESSED;
                    e.keyType = arc::KeyType::JOYSTICK_BUTTON;
                    e.joystick.button = static_cast<arc::JoystickButton>(event.joystickButton.button);
                    e.joystick.id = event.joystickButton.joystickId;
                    this->_events.push_back(std::move(e));
                    break;
                }
                case sf::Event::JoystickButtonReleased:
                {
                    e.eventType = arc::EventType::RELEASED;
                    e.keyType = arc::KeyType::JOYSTICK_BUTTON;
                    e.joystick.button = static_cast<arc::JoystickButton>(event.joystickButton.button);
                    e.joystick.id = event.joystickButton.joystickId;
                    this->_events.push_back(std::move(e));
                    for (auto it = this->_downJoystickButtons.begin(); it != this->_downJoystickButtons.end(); it++) {
                        if (std::get<0>(*it) == e.joystick.button && std::get<1>(*it) == e.joystick.id) {
                            this->_downJoystickButtons.erase(it);
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        auto mousePos = sf::Mouse::getPosition();
        for (auto key : _downKeys) {
            if (elapsed - std::get<1>(key) <= std::get<2>(key)) {
                continue;
            }
            e.eventType = arc::EventType::DOWN;
            e.keyType = arc::KeyType::KEY;
            e.key.code = std::get<0>(key);
            e.key.shift = false;
            this->_events.push_back(std::move(e));
        }
        for (auto button : _downMouseButtons) {
            if (elapsed - std::get<1>(button) <= std::get<2>(button)) {
                continue;
            }
            e.eventType = arc::EventType::DOWN;
            e.keyType = arc::KeyType::MOUSE_BUTTON;
            e.mouse.button = std::get<0>(button);
            e.mouse.x = mousePos.x;
            e.mouse.y = mousePos.y;
        }
        for (auto button : _downJoystickButtons) {
            if (elapsed - std::get<2>(button) <= std::get<3>(button)) {
                continue;
            }
            e.eventType = arc::EventType::DOWN;
            e.keyType = arc::KeyType::JOYSTICK_BUTTON;
            e.joystick.button = std::get<0>(button);
            e.joystick.id = std::get<1>(button);
            this->_events.push_back(std::move(e));
        }
    }

    virtual bool pollEvent(arc::Event& event)
    {
        if (this->_events.empty())
            return false;

        event = this->_events.front();
        this->_events.pop_front();
        return true;
    }

    virtual const arc::Joystick& joystick(std::uint16_t id) const
    {
        return this->_joysticks[id];
    }

    virtual const std::pair<int32_t, int32_t> mousePosition() const
    {
        auto pos = sf::Mouse::getPosition(this->_window);
        return std::pair<int32_t, int32_t>{pos.x, pos.y};
    }

    virtual void close()
    {
        this->_window.close();
    }

    virtual bool opened() const
    {
        return this->_window.isOpen();
    }

    virtual void clear(arc::Color color)
    {
        this->_window.clear(sf::Color{color.red, color.green, color.blue, color.alpha});
    }

    virtual void draw(std::shared_ptr<arc::ITexture> texture, float x, float y)
    {
        if (texture == nullptr)
            return;

        auto rect = sf::RectangleShape{sf::Vector2f{static_cast<float>(this->_tileSize), static_cast<float>(this->_tileSize)}};
        auto tex = std::dynamic_pointer_cast<SFMLTexture>(texture);

        rect.setTexture(tex->raw().get());
        rect.setTextureRect(tex->subrect());
        rect.setPosition(x * this->_tileSize, y * this->_tileSize);
        this->_window.draw(rect);
    }

    virtual void draw(std::shared_ptr<arc::ITexture> texture, float x, float y, float scale)
    {
        if (texture == nullptr)
            return;

        auto rect = sf::RectangleShape{sf::Vector2f{static_cast<float>(this->_tileSize), static_cast<float>(this->_tileSize)}};
        auto tex = std::dynamic_pointer_cast<SFMLTexture>(texture);

        rect.setTexture(tex->raw().get());
        rect.setTextureRect(tex->subrect());
        rect.setPosition(x * this->_tileSize, y * this->_tileSize);
        rect.setScale(scale, scale);
        this->_window.draw(rect);
    }

    virtual void print(const std::string& string, std::shared_ptr<arc::IFont> font, float x, float y)
    {
        if (font == nullptr)
            return;

        auto attr = std::dynamic_pointer_cast<SFMLFont>(font);
        auto text = sf::Text(sf::String(string), attr->font(), attr->size());
        text.setFillColor(attr->color());
        text.setPosition(x * this->_tileSize, y * this->_tileSize);
        this->_window.draw(text);
    }

    virtual arc::Rect<float> measure(const std::string& string, std::shared_ptr<arc::IFont> font, float x, float y)
    {
        if (font == nullptr)
            return arc::Rect<float> { 0.f, 0.f, 0.f, 0.f };

        auto attr = std::dynamic_pointer_cast<SFMLFont>(font);
        auto text = sf::Text(sf::String(string), attr->font(), attr->size());
        text.setFillColor(attr->color());
        text.setPosition(x, y);
        auto bounds = text.getLocalBounds();
        return {bounds.left, bounds.top, bounds.width / this->_tileSize, bounds.height / this->_tileSize};
    }

    virtual void flush()
    {
        this->_window.display();
    }

private:
    virtual void _resizeWindow()
    {
        sf::Vector2u size;
        size.x = this->_width * this->_tileSize;
        size.y = this->_height * this->_tileSize;

        this->_window.setSize(size);
        this->_window.setView(sf::View(sf::FloatRect(0, 0, size.x, size.y)));
    }

private:
    sf::RenderWindow _window;

    std::string _title;
    uint32_t _framerate;
    std::size_t _width;
    std::size_t _height;
    std::size_t _tileSize;
    std::deque<arc::Event> _events;
    arc::Joystick _joysticks[sf::Joystick::Count];
    std::vector<std::tuple<arc::KeyCode, float, float>> _downKeys = {};
    std::vector<std::tuple<arc::MouseButton, float, float>> _downMouseButtons = {};
    std::vector<std::tuple<arc::JoystickButton, int32_t, float, float>> _downJoystickButtons = {};
    std::map<uint32_t, arc::JoystickAxis> _joystickAxis = {};
    std::map<arc::KeyCode, float> _keyDownDelays = {};
};

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

extern "C" arc::ILibrary *entrypoint()
{
    return new SFMLLibrary;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::LIBRARY;
}

extern "C" const char *name()
{
    return "SFML";
}
