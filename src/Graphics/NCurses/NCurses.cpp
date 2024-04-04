/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurses graphic library
*/

#include "ILibrary.hpp"
#include "SharedLibraryType.hpp"

#include <iostream>
#include <map>
#include <cmath>
#include <deque>
#include <thread>
#include <ncurses.h>
#include <cmath>

class NCursesTexture : public arc::ITexture {
public:
    NCursesTexture() = default;

    virtual ~NCursesTexture() = default;

    virtual bool load(const arc::TextureSpecification& spec)
    {
        this->_spec = spec;

        return true;
    }

    virtual const arc::TextureSpecification& specification() const { return this->_spec; }
    const arc::TextureTextualSpecification& characteristics() const { return this->_spec.textual; }

private:
    arc::TextureSpecification _spec;
};

class NCursesTextureManager : public arc::ITextureManager {
public:
    NCursesTextureManager() = default;
    virtual ~NCursesTextureManager() = default;

    virtual bool load(const std::string& name, const arc::TextureSpecification& specification)
    {
        auto texture = std::make_shared<NCursesTexture>();

        if (!texture->load(specification))
            return false;
        this->_textures[name] = texture;
        return true;
    }

    virtual std::shared_ptr<arc::ITexture> get(const std::string& name) { return this->_textures.at(name); }

    virtual std::map<std::string, arc::TextureSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::TextureSpecification>{};

        for (const auto& [name, texture] : this->_textures)
            specs[name] = texture->specification();

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<NCursesTexture>> _textures;
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

    virtual const arc::FontSpecification& specification() const { return this->_spec; }

private:
    arc::FontSpecification _spec = {};
};

class NCursesFontManager : public arc::IFontManager {
public:
    NCursesFontManager() = default;
    virtual ~NCursesFontManager() = default;

    virtual bool load(const std::string& name, const arc::FontSpecification& spec)
    {
        auto attribute = std::make_shared<NCursesFont>();

        if (!attribute->init(spec))
            return false;
        this->_fonts[name] = attribute;
        return true;
    }

    virtual std::shared_ptr<arc::IFont> get(const std::string &name) { return this->_fonts.at(name); }

    virtual std::map<std::string, arc::FontSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::FontSpecification>{};

        for (const auto& [name, font] : this->_fonts)
            specs[name] = font->specification();

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<NCursesFont>> _fonts;
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
        auto attribute = std::make_shared<NCursesSound>();

        if (!attribute->init(spec))
            return false;
        this->_sounds[name] = attribute;
        return true;
    }

    virtual void play([[maybe_unused]]const std::string& name, [[maybe_unused]]const float volume) { }

    virtual void stop([[maybe_unused]]const std::string& name) { }

    virtual std::map<std::string, arc::SoundSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::SoundSpecification>{};

        for (const auto& [name, sound] : this->_sounds)
            specs[name] = sound->specification();

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<NCursesSound>> _sounds;
};

class NCursesMusic : public arc::IMusic {
public:
    NCursesMusic() = default;
    virtual ~NCursesMusic() = default;

    virtual bool init(const arc::MusicSpecification& spec)
    {
        this->_spec = spec;
        this->isPlaying = spec.isPlaying;
        if (this->isPlaying)
            this->_start = spec.startOffset == -1 ? std::chrono::system_clock::now() : std::chrono::system_clock::now() - std::chrono::milliseconds(static_cast<int>(spec.startOffset * 1000));

        return true;
    }

    virtual void play()
    {
        this->_start = std::chrono::system_clock::now();
        this->isPlaying = true;
    }
    virtual void stop() { this->isPlaying = false; }

    virtual const arc::MusicSpecification& specification() const { return this->_spec; }

    std::chrono::time_point<std::chrono::system_clock> getCurrentOffset() const { return this->_start; }

    bool isPlaying = false;
private:
    arc::MusicSpecification _spec;
    std::chrono::time_point<std::chrono::system_clock> _start;
};

class NCursesMusicManager : public arc::IMusicManager {
public:
    NCursesMusicManager() = default;
    virtual ~NCursesMusicManager() = default;

    virtual bool load(const std::string& name, const arc::MusicSpecification& spec)
    {
        auto attribute = std::make_shared<NCursesMusic>();

        if (!attribute->init(spec))
            return false;
        this->_musics[name] = attribute;
        return true;
    }

    virtual void play(const std::string& name, [[maybe_unused]]const float volume)
    {
        this->_musics.at(name)->play();
    }

    virtual void stop(const std::string& name)
    {
        this->_musics.at(name)->stop();
    }

    virtual bool isPlaying(const std::string& name)
    {
        return this->_musics.at(name)->isPlaying;
    }

    virtual std::map<std::string, arc::MusicSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::MusicSpecification>{};

        for (const auto& [name, music] : this->_musics) {
            arc::MusicSpecification newSpec = music->specification();
            newSpec.isPlaying = music->isPlaying;
            if (music->isPlaying)
                newSpec.startOffset = std::chrono::duration<float>(std::chrono::system_clock::now() - music->getCurrentOffset()).count();
            specs[name] = newSpec;
        }

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<NCursesMusic>> _musics;
};

#define COLOR_ORANGE 8

class NCursesDisplay : public arc::IDisplay {
public:
    NCursesDisplay()
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);

        start_color();
        if (can_change_color()) {
            _canChangeColor = true;
            init_color(COLOR_BLACK, 0, 0, 0);
            init_color(COLOR_RED, 1000, 0, 0);
            init_color(COLOR_GREEN, 0, 1000, 0);
            init_color(COLOR_YELLOW, 1000, 1000, 0);
            init_color(COLOR_BLUE, 0, 0, 1000);
            init_color(COLOR_MAGENTA, 1000, 0, 1000);
            init_color(COLOR_CYAN, 0, 1000, 1000);
            init_color(COLOR_WHITE, 1000, 1000, 1000);
            init_color(COLOR_ORANGE, 900, 450, 0); // RGB values range from 0 to 1000

            init_pair(1, COLOR_BLACK, COLOR_BLACK);
            init_pair(2, COLOR_RED, COLOR_BLACK);
            init_pair(3, COLOR_GREEN, COLOR_BLACK);
            init_pair(4, COLOR_YELLOW, COLOR_BLACK);
            init_pair(5, COLOR_BLUE, COLOR_BLACK);
            init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
            init_pair(7, COLOR_CYAN, COLOR_BLACK);
            init_pair(8, COLOR_WHITE, COLOR_WHITE);
            init_pair(9, COLOR_ORANGE, COLOR_BLACK);

        }

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

    static arc::Key MapNCursesKey(int key)
    {
        if (key >= 'a' && key <= 'z') return static_cast<arc::Key>(key - 'a');
        if (key >= 'A' && key <= 'Z') return static_cast<arc::Key>(key - 'A');
        if (key == ' ')         return arc::Key::SPACE;
        if (key == '\033')      return arc::Key::ESCAPE;
        if (key == '\n')        return arc::Key::ENTER;
        if (key >= '0' && key <= '9') return static_cast<arc::Key>(key - '0' + 26);
        if (key == KEY_DOWN)    return arc::Key::DOWN;
        if (key == KEY_UP)      return arc::Key::UP;
        if (key == KEY_LEFT)    return arc::Key::LEFT;
        if (key == KEY_RIGHT)   return arc::Key::RIGHT;
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

    virtual void draw(std::shared_ptr<arc::ITexture> texture, float x, float y)
    {
        auto& spec = std::dynamic_pointer_cast<NCursesTexture>(texture)->characteristics();
        int roundedX = static_cast<int>(std::round(x));
        int roundedY = static_cast<int>(std::round(y));

        if (_canChangeColor)
            attron(COLOR_PAIR(mapToNcurseColor(spec.color)));
        mvaddch(roundedY, roundedX, spec.character);
        if (_canChangeColor)
            attroff(COLOR_PAIR(mapToNcurseColor(spec.color)));
    }

    virtual void print(const std::string& string, std::shared_ptr<arc::IFont> font, float x, float y)
    {
        [[maybe_unused]] auto& spec = std::dynamic_pointer_cast<NCursesFont>(font)->specification();
        if (_canChangeColor)
            attron(COLOR_PAIR(mapToNcurseColor(spec.color)));
        mvprintw(y, x, "%s", string.c_str());
        if (_canChangeColor)
            attroff(COLOR_PAIR(mapToNcurseColor(spec.color)));
    }

    virtual arc::Rect<float> measure(const std::string& string, [[maybe_unused]] std::shared_ptr<arc::IFont> font, float x, float y)
    {
        return arc::Rect<float>{x, y, (float)string.length(), 1};
    }

    virtual void flush()
    {
        refresh();
    }

private:
    int mapToNcurseColor(arc::Color color)
    {
        int c = 1;

        if (color.red > 127)
            c += 1;
        if (color.green > 127)
            c += 2;
        if (color.blue > 127)
            c += 4;
        return c;
    }

    bool _opened = true;
    std::string _title;
    uint32_t _framerate;
    std::size_t _width;
    std::size_t _height;
    std::size_t _tileSize;
    std::deque<arc::Event> _events;
    std::map<std::tuple<size_t, size_t, size_t>, int> _colorPairs = {
        {{0, 0, 0}, 1},
        {{255, 0, 0}, 2},
        {{0, 255, 0}, 3},
        {{255, 255, 0}, 4},
        {{0, 0, 255}, 5},
        {{255, 0, 255}, 6},
        {{0, 255, 255}, 7},
        {{255, 255, 255}, 8},
        {{200, 100, 0}, 9}
    };
    bool _canChangeColor = false;
};

class NCursesLibrary : public arc::ILibrary {
public:
    NCursesLibrary() = default;
    virtual ~NCursesLibrary() = default;

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

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::LIBRARY;
}

extern "C" const char *name()
{
    return "NCurses";
}
