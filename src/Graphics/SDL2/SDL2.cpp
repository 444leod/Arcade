/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#include "ILibrary.hpp"
#include "SharedLibraryType.hpp"

#include <iostream>
#include <map>
#include <deque>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class SDLRendering
{
public:
    SDLRendering() = default;
    ~SDLRendering() = default;

    void init(const std::string &title, uint16_t width, uint16_t height)
    {
        auto win = SDL_CreateWindow(title.c_str(),
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, 0);
        this->_window.reset(win, SDL_DestroyWindow);

        auto ren = SDL_CreateRenderer(this->_window.get(), -1, 0);
        this->_renderer.reset(ren, SDL_DestroyRenderer);
    }

    std::shared_ptr<SDL_Renderer> renderer() const { return this->_renderer; }

    std::shared_ptr<SDL_Window> window() const { return this->_window; }

private:
    std::shared_ptr<SDL_Renderer> _renderer = nullptr;
    std::shared_ptr<SDL_Window> _window = nullptr;
};

class SDLSound : public arc::ISound
{
public:
    SDLSound() = default;
    ~SDLSound() = default;

    bool load(const arc::SoundSpecification &spec)
    {
        _spec = spec;
        _sound.reset(Mix_LoadWAV(spec.path.c_str()), Mix_FreeChunk);
        if (_sound == nullptr)
            std::cerr << Mix_GetError() << std::endl;
        return _sound != nullptr;
    }

    void play(float volume)
    {
        Mix_VolumeChunk(this->_sound.get(), volume * 1.28f);
        this->_channel = Mix_PlayChannel(-1, this->_sound.get(), 0);
    }

    void stop() { Mix_HaltChannel(_channel); }
    bool isPlaying() { return Mix_Playing(_channel); }
    virtual const arc::SoundSpecification &specification() const { return this->_spec; }

private:
    arc::SoundSpecification _spec = {};
    std::shared_ptr<Mix_Chunk> _sound = nullptr;
    int _channel = -1;
};

class SDLSoundManager : public arc::ISoundManager
{
public:
    SDLSoundManager()
    {
        if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096))
            std::cerr << Mix_GetError() << std::endl;
    }
    ~SDLSoundManager()
    {
        Mix_CloseAudio();
    }

    virtual bool load(const std::string &name, const arc::SoundSpecification &spec)
    {
        auto sound = std::make_shared<SDLSound>();

        if (!sound->load(spec))
            return false;
        this->_sounds[name] = sound;
        return true;
    }

    virtual std::map<std::string, arc::SoundSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::SoundSpecification>{};

        for (const auto &[name, sound] : this->_sounds)
            specs[name] = sound->specification();
        return specs;
    }

    virtual void play(const std::string &name, const float volume)
    {
        if (!this->_sounds.contains(name))
            return;
        auto sound = this->_sounds.at(name);
        if (!sound->isPlaying())
            sound->play(volume);
    }

    virtual void stop(const std::string &name)
    {
        if (!this->_sounds.contains(name))
            return;
        this->_sounds.at(name)->stop();
    }

private:
    std::map<std::string, std::shared_ptr<SDLSound>> _sounds;
};

class SDLMusic : public arc::IMusic
{
public:
    SDLMusic() = default;
    ~SDLMusic() = default;

    bool load(const arc::MusicSpecification &spec)
    {
        _spec = spec;
        _music.reset(Mix_LoadMUS(spec.path.c_str()), Mix_FreeMusic);
        if (spec.startOffset != -1)
            Mix_SetMusicPosition(spec.startOffset);
        if (spec.isPlaying)
            this->play();
        return this->_music != nullptr;
    }

    void play()
    {
        Mix_PlayMusic(this->_music.get(), 0);
        this->_playing = true;
    }

    void stop() { Mix_HaltMusic(); }
    void setVolume(float volume) { Mix_VolumeMusic(volume * 1.28); }
    bool isPlaying() const { return this->_playing; }
    void refreshState() { this->_playing = false; }
    virtual const arc::MusicSpecification &specification() const { return this->_spec; }

private:
    bool _playing = false;
    std::shared_ptr<Mix_Music> _music = nullptr;
    arc::MusicSpecification _spec = {};
};

class SDLMusicManager : public arc::IMusicManager
{
public:
    SDLMusicManager() = default;
    ~SDLMusicManager() = default;

    virtual bool load(const std::string &name, const arc::MusicSpecification &spec)
    {
        auto music = std::make_shared<SDLMusic>();

        if (!music->load(spec))
            return false;
        this->_musics[name] = music;
        return true;
    }

    virtual std::map<std::string, arc::MusicSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::MusicSpecification>{};

        for (const auto &[name, music] : this->_musics)
        {
            arc::MusicSpecification spec = music->specification();
            spec.isPlaying = music->isPlaying();
            music->stop();
            specs[name] = spec;
        }
        return specs;
    }

    virtual void play(const std::string &name, const float volume)
    {
        if (!this->_musics.contains(name))
            return;
        for (auto m : _musics)
            m.second->refreshState();
        auto music = this->_musics.at(name);
        music->setVolume(volume);
        if (!music->isPlaying())
            music->play();
    }

    virtual void stop(const std::string &name)
    {
        if (!this->_musics.contains(name))
            return;
        auto music = this->_musics.at(name);
        if (music->isPlaying())
            music->stop();
    }

    virtual bool isPlaying(const std::string &name)
    {
        if (!this->_musics.contains(name))
            return false;
        if (!Mix_PlayingMusic())
        {
            for (auto m : _musics)
                m.second->refreshState();
            return false;
        }
        return this->_musics.at(name)->isPlaying();
    }

private:
    std::map<std::string, std::shared_ptr<SDLMusic>> _musics;
};

class SDLTexture : public arc::ITexture
{
public:
    SDLTexture() = default;
    ~SDLTexture() = default;

    bool load(const arc::TextureSpecification &spec,
        std::string path, SDLRendering& rendering,
        std::optional<arc::Rect<uint32_t>> rect)
    {
        if (std::holds_alternative<arc::Color>(spec.graphical))
            _color = std::get<arc::Color>(spec.graphical);

        this->_spec = spec;
        this->_texture.reset(
            IMG_LoadTexture(rendering.renderer().get(), path.c_str()),
            SDL_DestroyTexture);

        if (rect.has_value())
        {
            this->_rect.x = (int)rect.value().x;
            this->_rect.y = (int)rect.value().y;
            this->_rect.w = (int)rect.value().width;
            this->_rect.h = (int)rect.value().height;
        }
        else
        {
            SDL_QueryTexture(this->_texture.get(), NULL, NULL,
                             &this->_rect.w, &this->_rect.h);
        }
        return true;
    }

    virtual const arc::TextureSpecification &specification() const { return this->_spec; }
    std::shared_ptr<SDL_Texture> raw() const { return this->_texture; }
    arc::Color color() const { return this->_color; }
    const SDL_Rect *rect() const { return &this->_rect; }

private:
    arc::Color _color = {};
    SDL_Rect _rect = {0, 0, 0, 0};
    std::shared_ptr<SDL_Texture> _texture = nullptr;
    arc::TextureSpecification _spec = {};
};

class SDLTextureManager : public arc::ITextureManager
{
public:
    SDLTextureManager(SDLRendering &rendering) : _sdl(rendering) {}
    ~SDLTextureManager() = default;

    virtual bool load(const std::string &name, const arc::TextureSpecification &spec)
    {
        auto tex = std::make_shared<SDLTexture>();

        if (std::holds_alternative<arc::TextureImage>(spec.graphical))
        {
            auto graph = std::get<arc::TextureImage>(spec.graphical);
            if (!tex->load(spec, graph.path, this->_sdl, graph.subrect))
                return false;
            this->_textures[name] = tex;
            return true;
        }

        if (!tex->load(spec, "", this->_sdl, std::nullopt))
            return false;
        this->_textures[name] = tex;
        return true;
    }

    virtual std::shared_ptr<arc::ITexture> get(const std::string &name)
    {
        if (this->_textures.find(name) == this->_textures.end())
            return nullptr;
        return this->_textures.at(name);
    }

    virtual std::map<std::string, arc::TextureSpecification> dump() const
    {
        auto specs = std::map<std::string, arc::TextureSpecification>{};

        for (const auto &[name, texture] : this->_textures)
            specs[name] = texture->specification();
        return specs;
    }

private:
    SDLRendering &_sdl;
    std::map<std::string, std::shared_ptr<SDLTexture>> _textures = {};
};

class SDLFont : public arc::IFont
{
public:
    SDLFont() = default;
    ~SDLFont() = default;

    bool load(const arc::FontSpecification &spec)
    {
        this->_spec = spec;
        this->_font.reset(TTF_OpenFont(spec.path.c_str(), spec.size), TTF_CloseFont);
        this->_color = {
            .r = spec.color.red,
            .g = spec.color.green,
            .b = spec.color.blue,
            .a = spec.color.alpha,
        };
        return true;
    }

    virtual const arc::FontSpecification &specification() const { return _spec; }
    std::shared_ptr<TTF_Font> font() { return this->_font; }
    SDL_Color color() { return this->_color; }

private:
    arc::FontSpecification _spec = {};
    std::shared_ptr<TTF_Font> _font = nullptr;
    SDL_Color _color = {0, 0, 0, 0};
};

class SDLFontManager : public arc::IFontManager
{
public:
    SDLFontManager()
    {
        TTF_Init();
    }
    ~SDLFontManager()
    {
        TTF_Quit();
    }

    virtual bool load(const std::string &name, const arc::FontSpecification &spec)
    {
        auto font = std::make_shared<SDLFont>();

        if (!font->load(spec))
            return false;
        this->_fonts[name] = font;
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

        for (const auto &[name, font] : this->_fonts)
            specs[name] = font->specification();
        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<SDLFont>> _fonts;
};

class SDLDisplay : public arc::IDisplay
{
public:
    SDLDisplay(SDLRendering &rendering) : _sdl(rendering)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        this->_tileSize = 16;
        this->_width = 80;
        this->_height = 60;
        this->_framerate = 0;
        this->_title = "Arcade";
        this->_opened = true;
        _sdl.init(this->_title,
                  this->_width * this->_tileSize,
                  this->_height * this->_tileSize);
    }
    ~SDLDisplay() = default;

    virtual void setTitle(const std::string &title)
    {
        this->_title = title;
        SDL_SetWindowTitle(this->_sdl.window().get(), title.c_str());
    }

    virtual void setFramerate(uint32_t framerate)
    {
        this->_framerate = framerate;
    }

    virtual void setTileSize(std::size_t size)
    {
        this->_tileSize = size;
        SDL_SetWindowSize(
            this->_sdl.window().get(),
            this->_width * this->_tileSize,
            this->_height * this->_tileSize);
    }

    virtual void setWidth(std::size_t width)
    {
        this->_width = width;
        SDL_SetWindowSize(
            this->_sdl.window().get(),
            this->_width * this->_tileSize,
            this->_height * this->_tileSize);
    }

    virtual void setHeight(std::size_t height)
    {
        this->_height = height;
        SDL_SetWindowSize(
            this->_sdl.window().get(),
            this->_width * this->_tileSize,
            this->_height * this->_tileSize);
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
        this->_opened = false;
    }

    virtual bool pollEvent(arc::Event &event)
    {
        if (this->_events.empty())
            return false;

        event = this->_events.front();
        this->_events.pop_front();
        return true;
    }

    static arc::Key MapSDLKey(SDL_Keycode key)
    {
        if (key >= SDL_KeyCode::SDLK_a && key <= SDL_KeyCode::SDLK_z)
            return (arc::Key)((uint32_t)arc::Key::A + key - SDL_KeyCode::SDLK_a);
        if (key >= SDL_KeyCode::SDLK_RIGHT && key <= SDL_KeyCode::SDLK_UP)
            return (arc::Key)((uint32_t)arc::Key::UP + key - SDL_KeyCode::SDLK_RIGHT);

        switch (key)
        {
        case SDL_KeyCode::SDLK_SPACE:
            return arc::Key::SPACE;
        case SDL_KeyCode::SDLK_RETURN:
            return arc::Key::ENTER;
        case SDL_KeyCode::SDLK_ESCAPE:
            return arc::Key::ESCAPE;
        default:
            return arc::Key::UNKNOWN;
        }
        return arc::Key::UNKNOWN;
    }

    static arc::MouseButton MapSDLButton(uint8_t button)
    {
        switch (button)
        {
        case SDL_BUTTON_LEFT:
            return arc::MouseButton::LEFT;
        case SDL_BUTTON_RIGHT:
            return arc::MouseButton::RIGHT;
        case SDL_BUTTON_MIDDLE:
            return arc::MouseButton::MIDDLE;
        default:
            break;
        }
        return arc::MouseButton::UNKNOWN;
    }

    virtual void update([[maybe_unused]] float deltaTime)
    {
        SDL_Event sdlEvent = {};
        arc::Event arcEvent = {};

        while (SDL_PollEvent(&sdlEvent))
        {
            switch (sdlEvent.type)
            {
            case SDL_EventType::SDL_QUIT:
                this->_opened = false;
                break;
            case SDL_EventType::SDL_KEYDOWN:
                arcEvent.type = arc::EventType::KEY_PRESSED;
                arcEvent.key = MapSDLKey(sdlEvent.key.keysym.sym);
                _events.push_back(arcEvent);
                break;
            case SDL_EventType::SDL_MOUSEBUTTONDOWN:
                arcEvent.type = arc::EventType::MOUSE_BUTTON_PRESSED;
                arcEvent.mouse = {
                    .button = MapSDLButton(sdlEvent.button.button),
                    .x = sdlEvent.button.x / (int)this->_tileSize,
                    .y = sdlEvent.button.y / (int)this->_tileSize};
                _events.push_back(arcEvent);
                break;
            default:
                break;
            }
        }
    }

    virtual void clear(arc::Color color = {0, 0, 0, 255})
    {
        SDL_SetRenderDrawColor(this->_sdl.renderer().get(), color.red, color.green, color.blue, color.alpha);
        SDL_RenderClear(this->_sdl.renderer().get());
    }

    virtual void draw(std::shared_ptr<arc::ITexture> texture, float x, float y)
    {
        if (texture == nullptr)
            return;
        auto tex = std::dynamic_pointer_cast<SDLTexture>(texture);
        auto rect = SDL_Rect{};
        rect.x = (int)x * this->_tileSize;
        rect.y = (int)y * this->_tileSize;
        rect.w = (int)this->_tileSize;
        rect.h = (int)this->_tileSize;
        if (!tex->raw())
        {
            auto c = tex->color();
            SDL_SetRenderDrawColor(this->_sdl.renderer().get(), c.red, c.green, c.blue, c.alpha);
            SDL_RenderFillRect(this->_sdl.renderer().get(), &rect);
            SDL_RenderDrawRect(this->_sdl.renderer().get(), &rect);
        }
        else
            SDL_RenderCopy(this->_sdl.renderer().get(), tex->raw().get(), tex->rect(), &rect);
    }

    virtual void print(const std::string &string, std::shared_ptr<arc::IFont> font, float x, float y)
    {
        if (font == nullptr)
            return;
        auto attr = dynamic_cast<const SDLFont &>(*font);
        auto surf = TTF_RenderText_Solid(attr.font().get(), string.c_str(), attr.color());
        auto tex = SDL_CreateTextureFromSurface(this->_sdl.renderer().get(), surf);
        SDL_Rect rect = {
            (int)(x * (float)this->_tileSize),
            (int)(y * (float)this->_tileSize),
            surf->w, surf->h};
        SDL_RenderCopy(this->_sdl.renderer().get(), tex, NULL, &rect);
        SDL_FreeSurface(surf);
    }

    virtual arc::Rect<float> measure(const std::string &string, std::shared_ptr<arc::IFont> font, float x, float y)
    {
        if (font == nullptr)
            return arc::Rect<float>();
        auto attr = dynamic_cast<const SDLFont &>(*font);
        auto surf = TTF_RenderText_Solid(attr.font().get(), string.c_str(), attr.color());
        arc::Rect<float> rect = {x, y,
                                 (float)surf->w / this->_tileSize,
                                 (float)surf->h / this->_tileSize};
        SDL_FreeSurface(surf);
        return rect;
    }

    virtual void flush()
    {
        SDL_RenderPresent(this->_sdl.renderer().get());
    }

private:
    SDLRendering& _sdl;

    bool _opened = false;
    std::deque<arc::Event> _events;
    std::string _title = "";
    uint32_t _framerate = 0;
    std::size_t _tileSize = 0;
    std::size_t _width = 0;
    std::size_t _height = 0;
};

class SDLLibrary : public arc::ILibrary
{
public:
    SDLLibrary() : _display(SDLDisplay(this->_rendering)),
                   _textures(SDLTextureManager(this->_rendering))
    {
    }
    ~SDLLibrary()
    {
        SDL_Quit();
    }

    virtual std::string name() const { return " SDL"; }

    virtual arc::IDisplay &display() { return this->_display; }
    virtual arc::ITextureManager &textures() { return this->_textures; }
    virtual arc::IFontManager &fonts() { return this->_fonts; }
    virtual arc::IMusicManager &musics() { return this->_musics; }
    virtual arc::ISoundManager &sounds() { return this->_sounds; }

private:
    SDLRendering _rendering;
    SDLDisplay _display;
    SDLTextureManager _textures;
    SDLFontManager _fonts;
    SDLMusicManager _musics;
    SDLSoundManager _sounds;
};

extern "C" arc::ILibrary *entrypoint()
{
    return new SDLLibrary();
}

extern "C" const char *name()
{
    return "SDL2";
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::LIBRARY;
}
