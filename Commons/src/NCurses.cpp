/*
** EPITECH PROJECT, 2024
** NCurses.cpp
** File description:
** NCurses.cpp
*/

#include "arcade/ILibrary.hpp"

#include <map>
#include <deque>
#include <thread>
#include <ncurses.h>

class NCursesTexture : public arc::ITexture {
public:
    NCursesTexture() = default;

    virtual ~NCursesTexture() = default;

    virtual void load(const arc::TextureSpecification& spec)
    {
        this->_spec = spec;
    }

    virtual const arc::TextureSpecification& specification() const
    {
        return this->_spec;
    }

    const arc::TextureTextualSpecification& characteristics() const
    {
        return this->_spec.textual;
    }

private:
    arc::TextureSpecification _spec;
};

class NCursesTextureManager : public arc::ITextureManager {
public:
    NCursesTextureManager() = default;
    virtual ~NCursesTextureManager() = default;

    virtual bool load(const std::string& name, const arc::TextureSpecification& specification)
    {
        NCursesTexture texture;
        texture.load(specification);
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
    std::map<std::string, NCursesTexture> _textures;
};

class NCursesFont : public arc::IFont {
public:
    NCursesFont() = default;
    virtual ~NCursesFont() = default;

    virtual bool init(const arc::FontSpecification& spec)
    {
        this->_spec = spec;
        return true;
    }

    virtual const arc::FontSpecification& specificiation() const { return this->_spec; }

private:
    arc::FontSpecification _spec = {};
};

class NCursesFontManager : public arc::IFontManager {
public:
    NCursesFontManager() = default;
    virtual ~NCursesFontManager() = default;

    virtual bool load(const std::string& name, const arc::FontSpecification& spec)
    {
        auto attribute = NCursesFont();

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
    std::map<std::string, NCursesFont> _fonts;
};

class NCursesSound : public arc::ISound {
public:
    NCursesSound() = default;
    virtual ~NCursesSound() = default;

    virtual bool init(const arc::SoundSpecification& spec)
    {
        this->_spec = spec;
        return true;
    }

    virtual const arc::SoundSpecification& specification() const { return this->_spec; }

private:
    arc::SoundSpecification _spec;
};

class NCursesSoundManager : public arc::ISoundManager {
public:
    NCursesSoundManager() = default;
    virtual ~NCursesSoundManager() = default;

    virtual bool load(const std::string& name, const arc::SoundSpecification& spec)
    {
        auto attribute = NCursesSound{};

        if (!attribute.init(spec))
            return false;
        this->_sounds[name] = attribute;
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

        for (const auto& [name, sound] : this->_sounds)
            specs.push_back({name, sound.specification()});

        return specs;
    }

private:
    std::map<std::string, NCursesSound> _sounds;
};

class NCursesMusic : public arc::IMusic {
public:
    NCursesMusic() = default;
    virtual ~NCursesMusic() = default;

    virtual bool init(const arc::MusicSpecification& spec)
    {
        this->_spec = spec;
        this->isPlaying = spec.isPlaying;
        return true;
    }

    virtual void play() { this->isPlaying = true; }
    virtual void stop() { this->isPlaying = false; }
    virtual const arc::MusicSpecification& specification() const { return this->_spec; }

    bool isPlaying = false;
private:
    arc::MusicSpecification _spec;
};

class NCursesMusicManager : public arc::IMusicManager {
public:
    NCursesMusicManager() = default;
    virtual ~NCursesMusicManager() = default;

    virtual bool load(const std::string& name, const arc::MusicSpecification& spec)
    {
        auto attribute = NCursesMusic();

        if (!attribute.init(spec))
            return false;
        this->_musics[name] = attribute;
        return true;
    }

    virtual arc::IMusic& get(const std::string &name)
    {
        return this->_musics.at(name);
    }

    virtual std::vector<std::pair<std::string, arc::MusicSpecification>> dump()
    {
        auto specs = std::vector<std::pair<std::string, arc::MusicSpecification>>{};
        specs.reserve(_musics.size());

        for (const auto& [name, music] : this->_musics) {
            arc::MusicSpecification spec = music.specification();
            spec.isPlaying = music.isPlaying;
            specs.push_back({name, spec});
        }

        return specs;
    }

private:
    std::map<std::string, NCursesMusic> _musics;
};

class NCursesDisplay : public arc::IDisplay {
public:
    NCursesDisplay()
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);

        this->_title = "";
        this->_framerate = 0;
        this->_width = 80;
        this->_height = 60;
        this->_tileSize = 16;
    }

    virtual ~NCursesDisplay()
    {
        endwin();
    }

    virtual void setTitle(const std::string& title)
    {
        this->_title = title;
    }

    virtual void setFramerate(uint32_t framerate)
    {
        this->_framerate = framerate;
    }

    virtual void setTileSize(std::size_t size)
    {
        this->_tileSize = size;
    }

    virtual void setWidth(std::size_t width)
    {
        this->_width = width;
    }

    virtual void setHeight(std::size_t height)
    {
        this->_height = height;
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

    virtual bool opened() const
    {
        return _opened;
    }

    virtual void close()
    {
        _opened = false;
    }

    static arc::Key MapNCursesKey(char key)
    {
        if (key >= 'a' && key <= 'z') return static_cast<arc::Key>(key - 'a');
        if (key >= 'A' && key <= 'Z') return static_cast<arc::Key>(key - 'A');
        if (key == ' ') return arc::Key::SPACE;
        return arc::Key::UNKNOWN;
    }

    virtual void update(float deltaTime)
    {
        // TODO: ch could be a MOUSE button
        int ch = getch();
        if (ch != ERR) {
            arc::Key key = NCursesDisplay::MapNCursesKey(ch);
            arc::Event e;
            e.type = arc::EventType::KEY_PRESSED;
            e.key = key;
            this->_events.push_back(std::move(e));
        }

        if (_framerate == 0)
            return;

        float sleeping = std::max(0.0, 1000.0 / this->_framerate - deltaTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleeping)));
    }

    virtual bool pollEvent(arc::Event& event)
    {
        if (this->_events.empty())
            return false;

        event = this->_events.front();
        this->_events.pop_front();
        return true;
    }

    virtual void clear([[maybe_unused]] arc::Color color)
    {
        ::clear();
    }

    virtual void draw(const arc::ITexture& texture, float x, float y)
    {
        auto& spec = static_cast<const NCursesTexture&>(texture).characteristics();
        mvprintw(y, x, "%c", spec.character);
    }

    virtual void print(const std::string& string, const arc::IFont& font, float x, float y)
    {
        [[maybe_unused]] auto& spec = static_cast<const NCursesFont&>(font).specificiation();
        mvprintw(y, x, "%s", string.c_str());
    }

    virtual arc::Rect<float> measure(const std::string& string, [[maybe_unused]] const arc::IFont& font, float x, float y)
    {
        return arc::Rect<float>{x, y, (float)string.length(), 1};
    }

    virtual void flush()
    {
        refresh();
    }

    virtual void playSound([[maybe_unused]] arc::ISound& sound, [[maybe_unused]] const float volume)
    {
    }

    virtual void stopSound([[maybe_unused]] arc::ISound& sound)
    {
    }

    virtual void playMusic(arc::IMusic& music, [[maybe_unused]] const float volume)
    {
        auto &attr = static_cast<NCursesMusic&>(music);
        attr.play();
    }

    virtual void stopMusic(arc::IMusic& music)
    {
        auto &attr = static_cast<NCursesMusic&>(music);
        attr.stop();
    }

    virtual bool isMusicPlaying([[maybe_unused]] arc::IMusic& music)
    {
        auto &attr = static_cast<NCursesMusic&>(music);
        return attr.isPlaying;
    }

private:
    bool _opened = true;
    std::string _title;
    uint32_t _framerate;
    std::size_t _width;
    std::size_t _height;
    std::size_t _tileSize;
    std::deque<arc::Event> _events;
};

class NCursesLibrary : public arc::ILibrary {
public:
    NCursesLibrary() = default;
    virtual ~NCursesLibrary() = default;

    virtual std::string name() const { return "NCurses"; }
    virtual std::string version() const { return "1.0.0"; }

    virtual arc::IDisplay& display() { return this->_display; }
    virtual arc::ITextureManager& textures() { return this->_textures; }
    virtual arc::IFontManager& fonts() { return this->_fonts; }
    virtual arc::ISoundManager& sounds() { return this->_sounds; }
    virtual arc::IMusicManager& musics() { return this->_musics; }

private:
    NCursesDisplay _display;
    NCursesTextureManager _textures;
    NCursesFontManager _fonts;
    NCursesSoundManager _sounds;
    NCursesMusicManager _musics;
};

extern "C" arc::ILibrary *entrypoint()
{
    return new NCursesLibrary;
}
