/*
** EPITECH PROJECT, 2024
** SFML.cpp
** File description:
** SFML.cpp
*/

#include "arcade/ILibrary.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <memory>

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
        auto texture = SFMLTexture{};

        if (std::holds_alternative<arc::TextureImage>(specification.graphical)) {
            auto image = std::get<arc::TextureImage>(specification.graphical);

            if (this->_cache.find(image.path) != this->_cache.end()) {
                texture.load(specification, this->_cache[image.path], image.subrect);
                this->_textures[name] = texture;
                return true;
            }

            auto sftex = std::make_shared<sf::Texture>();
            if (!sftex->loadFromFile(image.path))
                return false;

            this->_cache[image.path] = sftex;
            texture.load(specification, sftex, image.subrect);
            this->_textures[name] = texture;
            return true;
        }

        auto color = std::get<arc::Color>(specification.graphical);
        auto img = sf::Image{};
        img.create(1, 1, sf::Color(color.red, color.green, color.blue, color.alpha));
        auto sftex = std::make_shared<sf::Texture>();
        if (!sftex->loadFromImage(img))
            return false;
        texture.load(specification, sftex, std::nullopt);
        this->_textures[name] = texture;
        return true;
    }

    virtual arc::ITexture& get(const std::string& name)
    {
        return this->_textures.at(name);
    }

    virtual std::vector<std::pair<std::string, arc::TextureSpecification>> dump() const
    {
        auto specs = std::vector<std::pair<std::string, arc::TextureSpecification>>{};
        specs.reserve(_textures.size());

        for (const auto& [name, texture] : this->_textures)
            specs.push_back({name, texture.specification()});

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> _cache;
    std::map<std::string, SFMLTexture> _textures;
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
        this->_color =  sf::Color(spec.color.red, spec.color.blue, spec.color.blue, spec.color.alpha);
        this->_size = spec.size;
        return true;
    }

    virtual const arc::FontSpecification& specificiation() const { return this->_spec; }
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
        auto attribute = SFMLFont();

        if (!attribute.init(spec))
            return false;
        this->_fonts[name] = attribute;
        return true;
    }

    virtual arc::IFont& get(const std::string &name)
    {
        return this->_fonts.at(name);
    }

    virtual std::vector<std::pair<std::string, arc::FontSpecification>> dump() const
    {
        auto specs = std::vector<std::pair<std::string, arc::FontSpecification>>{};
        specs.reserve(_fonts.size());

        for (const auto& [name, font] : this->_fonts)
            specs.push_back({name, font.specificiation()});

        return specs;
    }

private:
    std::map<std::string, SFMLFont> _fonts;
};

#include <iostream>

class SFMLSound : public arc::ISound {
public:
    SFMLSound() = default;
    virtual ~SFMLSound() = default;

    bool init(const arc::SoundSpecification& spec)
    {
        this->_spec = spec;
        std::cout << "Loading sound: " << spec.path << std::endl;
        if (!this->_buffer.loadFromFile(spec.path))
            return false;
        std::cout << "Sound loaded" << std::endl;
        this->_sound.setBuffer(this->_buffer);
        this->_sound.setVolume(100);
        this->_sound.play();
        return true;
    }

    virtual void play() { this->_sound.play(); }
    virtual void stop() { this->_sound.stop(); }
    virtual sf::Sound::Status getStatus() const { return this->_sound.getStatus(); }
    virtual void setVolume(float volume) { this->_sound.setVolume(volume); }

    virtual const arc::SoundSpecification& specification() const { return this->_spec; }
    const sf::SoundBuffer& buffer() const { return this->_buffer; }
    const sf::Sound& sound() const { return this->_sound; }

private:
    sf::SoundBuffer _buffer = {};
    sf::Sound _sound = {};
    arc::SoundSpecification _spec = {};
};

class SFMLSoundManager : public arc::ISoundManager {
public:
    SFMLSoundManager() = default;
    virtual ~SFMLSoundManager() = default;

    virtual bool load(const std::string& name, const arc::SoundSpecification& spec)
    {
        auto sound = SFMLSound();

        if (!sound.init(spec))
            return false;
        this->_sounds[name] = sound;
        return true;
    }

    virtual arc::ISound& get(const std::string &name)
    {
        return this->_sounds.at(name);
    }

    virtual std::vector<std::pair<std::string, arc::SoundSpecification>> dump() const
    {
        auto specs = std::vector<std::pair<std::string, arc::SoundSpecification>>{};
        specs.reserve(_sounds.size());

        for (auto& [name, sound] : this->_sounds) {
            // if (sound.getStatus() == sf::Sound::Playing)
            //     sound.stop();
            specs.push_back({name, sound.specification()});
        }

        return specs;
    }

private:
    std::map<std::string, SFMLSound> _sounds;
};

// class SFMLMusic : public arc::IMusic {
// public:
//     SFMLMusic() = default;
//     virtual ~SFMLMusic() = default;

//     bool init(const arc::MusicSpecification& spec)
//     {
//         this->_spec = spec;
//         if (!this->_music.openFromFile(spec.path))
//             return false;
//         this->_music.setLoop(spec.loop);
//         if (spec.startOffset != -1)
//             this->_music.setPlayingOffset(sf::seconds(spec.startOffset));
//         return true;
//     }

//     virtual void play() { this->_music.play(); }
//     virtual void stop() { this->_music.stop(); }
//     virtual sf::Music::Status getStatus() const { return this->_music.getStatus(); }
//     virtual void setVolume(float volume) { this->_music.setVolume(volume); }

//     virtual const arc::MusicSpecification& specification() const { return this->_spec; }
//     const sf::Music& music() const { return this->_music; }

// private:
//     sf::Music _music = {};
//     arc::MusicSpecification _spec = {};
// };

// class SFMLMusicManager : public arc::IMusicManager {
// public:
//     SFMLMusicManager() = default;
//     virtual ~SFMLMusicManager() = default;

//     virtual bool load(const std::string& name, const arc::MusicSpecification& spec)
//     {
//         auto music = SFMLMusic();

//         if (!music.init(spec))
//             return false;
//         this->_musics[name] = std::make_shared<SFMLMusic>(music);
//         return true;
//     }

//     virtual arc::IMusic& get(const std::string &name)
//     {
//         return *this->_musics.at(name);
//     }

//     virtual std::vector<std::pair<std::string, arc::MusicSpecification>> dump()
//     {
//         auto specs = std::vector<std::pair<std::string, arc::MusicSpecification>>{};
//         specs.reserve(_musics.size());

//         for (auto& [name, music] : this->_musics) {
//             arc::MusicSpecification spec = (*music).specification();
//             if ((*music).music().getStatus() == sf::Music::Playing)
//                 spec.startOffset = (*music).music().getPlayingOffset().asSeconds();
//             (*music).stop();
//             specs.push_back({name, spec});
//         }

//         return specs;
//     }

// private:
//     std::map<std::string, std::shared_ptr<SFMLMusic>> _musics;
// };

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

    static arc::Key MapSFMLKey(sf::Keyboard::Key key)
    {
        if (key < 26) return static_cast<arc::Key>(key);
        if (key == sf::Keyboard::Up) return arc::Key::UP;
        if (key == sf::Keyboard::Down) return arc::Key::DOWN;
        if (key == sf::Keyboard::Left) return arc::Key::LEFT;
        if (key == sf::Keyboard::Right) return arc::Key::RIGHT;
        if (key == sf::Keyboard::Space) return arc::Key::SPACE;
        if (key == sf::Keyboard::Enter) return arc::Key::ENTER;
        if (key == sf::Keyboard::Escape) return arc::Key::ESCAPE;
        return arc::Key::UNKNOWN;
    }

    static sf::Keyboard::Key MapArcKey(arc::Key key)
    {
        if (static_cast<uint64_t>(key) < 26) return static_cast<sf::Keyboard::Key>(key);
        if (key == arc::Key::UP) return sf::Keyboard::Up;
        if (key == arc::Key::DOWN) return sf::Keyboard::Down;
        if (key == arc::Key::LEFT) return sf::Keyboard::Left;
        if (key == arc::Key::RIGHT) return sf::Keyboard::Right;
        if (key == arc::Key::SPACE) return sf::Keyboard::Space;
        if (key == arc::Key::ENTER) return sf::Keyboard::Enter;
        if (key == arc::Key::ESCAPE) return sf::Keyboard::Escape;
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

        while (this->_window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                this->_window.close();
                break;
            case sf::Event::KeyPressed:
                e.type = arc::EventType::KEY_PRESSED;
                e.key = SFMLDisplay::MapSFMLKey(event.key.code);
                this->_events.push_back(std::move(e));
                break;
            case sf::Event::MouseButtonPressed:
                e.type = arc::EventType::MOUSE_BUTTON_PRESSED;
                e.mouse.button = SFMLDisplay::MapSFMLMouseButton(event.mouseButton.button);
                e.mouse.x = event.mouseButton.x / this->_tileSize;
                e.mouse.y = event.mouseButton.y / this->_tileSize;
                this->_events.push_back(std::move(e));
                break;
            default:
                break;
            }
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

    virtual void draw(const arc::ITexture& texture, float x, float y)
    {
        auto rect = sf::RectangleShape{sf::Vector2f{static_cast<float>(this->_tileSize), static_cast<float>(this->_tileSize)}};
        rect.setTexture(dynamic_cast<const SFMLTexture&>(texture).raw().get());
        rect.setTextureRect(dynamic_cast<const SFMLTexture&>(texture).subrect());
        rect.setPosition(x * this->_tileSize, y * this->_tileSize);
        this->_window.draw(rect);
    }

    virtual void print(const std::string& string, const arc::IFont& font, float x, float y)
    {
        auto attr = dynamic_cast<const SFMLFont&>(font);
        auto text = sf::Text(sf::String(string), attr.font(), attr.size());
        text.setFillColor(attr.color());
        text.setPosition(x * this->_tileSize, y * this->_tileSize);
        this->_window.draw(text);
    }

    virtual arc::Rect<float> measure(const std::string& string, const arc::IFont& font, float x, float y)
    {
        auto attr = dynamic_cast<const SFMLFont&>(font);
        auto text = sf::Text(sf::String(string), attr.font(), attr.size());
        text.setFillColor(attr.color());
        text.setPosition(x, y);
        auto bounds = text.getLocalBounds();
        return {bounds.left, bounds.top, bounds.width / this->_tileSize, bounds.height / this->_tileSize};
    }

    virtual void playSound(const arc::ISound& sound, const float volume)
    {
        SFMLSound& s = const_cast<SFMLSound&>(dynamic_cast<const SFMLSound&>(sound));
        s.setVolume(volume);
        s.play();
    }

    virtual void stopSound(const arc::ISound& sound)
    {
        SFMLSound& s = const_cast<SFMLSound&>(dynamic_cast<const SFMLSound&>(sound));
        s.stop();
    }

    // virtual void playMusic(const arc::IMusic& music, const float volume)
    // {
    //     SFMLMusic& m = const_cast<SFMLMusic&>(dynamic_cast<const SFMLMusic&>(music));
    //     m.setVolume(volume);
    //     m.play();
    // }

    // virtual void stopMusic(const arc::IMusic& music)
    // {
    //     SFMLMusic& m = const_cast<SFMLMusic&>(dynamic_cast<const SFMLMusic&>(music));
    //     m.stop();
    // }

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
};

class SFMLLibrary : public arc::ILibrary {
public:
    SFMLLibrary() = default;
    virtual ~SFMLLibrary() = default;

    virtual std::string name() const { return "SFML"; }
    virtual std::string version() const { return "2.5.1"; }

    virtual arc::IDisplay& display() { return this->_display; }
    virtual arc::ITextureManager& textures() { return this->_textures; }
    virtual arc::IFontManager& fonts() { return this->_fonts; }
    virtual arc::ISoundManager& sounds() { return this->_sounds; }
    // virtual arc::IMusicManager& musics() { return this->_musics; }

private:
    SFMLDisplay _display;
    SFMLTextureManager _textures;
    SFMLFontManager _fonts;
    SFMLSoundManager _sounds;
    // SFMLMusicManager _musics;
};

extern "C" arc::ILibrary *entrypoint()
{
    return new SFMLLibrary;
}
