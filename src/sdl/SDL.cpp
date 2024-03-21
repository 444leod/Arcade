/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#include "ILibrary.hpp"
#include <iostream>
#include <map>
#include <deque>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace arc
{
    class SDLSound : public ISound
    {
    public:
        SDLSound() = default;
        ~SDLSound()
        {
            Mix_FreeChunk(this->_sound);
        }

        bool load(const SoundSpecification& spec)
        {
            _spec = spec;
            std::cout << "Loading: " << spec.path << std::endl;
            _sound = Mix_LoadWAV(spec.path.c_str());
            if (_sound == nullptr)
                std::cout << Mix_GetError() << std::endl;
            return _sound != nullptr;
        }

        void play(float volume)
        {
            Mix_VolumeChunk(this->_sound, volume * 1.28f);
            this->_channel = Mix_PlayChannel(-1, this->_sound, 0);
        }

        void stop() { Mix_HaltChannel(_channel); }
        bool isPlaying() { return Mix_Playing(_channel); }
        virtual const SoundSpecification& specification() const { return this->_spec; }

    private:
        SoundSpecification _spec = {};
        Mix_Chunk *_sound = nullptr;
        int _channel = -1;
    };

    class SDLSoundManager : public ISoundManager
    {
    public:
        SDLSoundManager()
        {
            if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096))
                std::cout << Mix_GetError() << std::endl;
        }
        ~SDLSoundManager()
        {
            Mix_CloseAudio();
        }

        virtual bool load(const std::string& name, const SoundSpecification& spec)
        {
            auto sound = std::make_shared<SDLSound>();

            if (!sound->load(spec))
                return false;
            this->_sounds[name] = sound;
            return true;
        }

        virtual std::vector<std::pair<std::string, SoundSpecification>> dump() const
        {
            auto specs = std::vector<std::pair<std::string, SoundSpecification>>{};
            specs.reserve(_sounds.size());

            for (const auto& [name, sound] : this->_sounds) {
                std::cout << "Dumping: " << name << ": " << sound->specification().path << std::endl;
                specs.push_back({name, sound->specification()});
            }
            return specs;
        }

        virtual void play(const std::string& name, const float volume)
        {
            if (!this->_sounds.contains(name))
                return;
            auto sound = this->_sounds.at(name);
            if (!sound->isPlaying())
                sound->play(volume);
        }

        virtual void stop(const std::string& name)
        {
            if (!this->_sounds.contains(name))
                return;
            this->_sounds.at(name)->stop();
        }

    private:
        std::map<std::string, std::shared_ptr<SDLSound>> _sounds;
    };

    class SDLMusic : public IMusic
    {
    public:
        SDLMusic() = default;
        ~SDLMusic()
        {
            Mix_FreeMusic(this->_music);
        }

        bool load(const MusicSpecification& spec)
        {
            _spec = spec;
            _music = Mix_LoadMUS(spec.path.c_str());
            return this->_music != nullptr;
        }

        void play() {
            Mix_PlayMusic(this->_music, 0);
            this->_playing = true;
        }

        void stop() { Mix_HaltMusic(); }
        void setVolume(float volume) { Mix_VolumeMusic(volume * 1.28); }
        bool isPlaying() const { return this->_playing; }
        void refreshState() { this->_playing = false; }
        virtual const MusicSpecification& specification() const { return this->_spec; }

    private:
        bool _playing = false;
        Mix_Music *_music = nullptr;
        MusicSpecification _spec = {};
    };

    class SDLMusicManager : public IMusicManager
    {
    public:
        SDLMusicManager() = default;
        ~SDLMusicManager() = default;

        virtual bool load(const std::string& name, const MusicSpecification& spec)
        {
            auto music = std::make_shared<SDLMusic>();

            if (!music->load(spec))
                return false;
            this->_musics[name] = music;
            return true;
        }

        virtual std::vector<std::pair<std::string, MusicSpecification>> dump()
        {
            auto specs = std::vector<std::pair<std::string, MusicSpecification>>{};
            specs.reserve(_musics.size());

            for (const auto& [name, music] : this->_musics)
                specs.push_back({name, music->specification()});
            return specs;
        }

        virtual void play(const std::string& name, const float volume)
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

        virtual void stop(const std::string& name)
        {
            if (!this->_musics.contains(name))
                return;
            auto music = this->_musics.at(name);
            if (music->isPlaying())
                music->stop();
        }

        virtual bool isPlaying(const std::string& name)
        {
            if (!this->_musics.contains(name))
                return false;
            if (!Mix_PlayingMusic()) {
                for (auto m : _musics)
                    m.second->refreshState();
                return false;
            }
            return this->_musics.at(name)->isPlaying();
        }

    private:
        std::map<std::string, std::shared_ptr<SDLMusic>> _musics;
    };

    class SDLTexture : public ITexture
    {
    public:
        SDLTexture() = default;
        ~SDLTexture()
        {
            SDL_DestroyTexture(_texture);
        }

        bool load(const TextureSpecification& spec,
            SDL_Texture *texture,
            std::optional<Rect<uint32_t>> rect)
        {
            if (std::holds_alternative<Color>(spec.graphical))
                _color = std::get<Color>(spec.graphical);
            this->_spec = spec;
            this->_texture = texture;
            if (rect.has_value()) {
                this->_rect.x = (int)rect.value().x;
                this->_rect.y = (int)rect.value().y;
                this->_rect.w = (int)rect.value().width;
                this->_rect.h = (int)rect.value().height;
            } else {
                SDL_QueryTexture(this->_texture, NULL, NULL,
                    &this->_rect.w, &this->_rect.h);
            }
            return true;
        }

        virtual const TextureSpecification& specification() const { return this->_spec; }
        SDL_Texture *raw() const { return this->_texture; }
        Color color() const { return this->_color; }
        const SDL_Rect *rect() const { return &this->_rect; }

    private:
        Color _color = {};
        SDL_Rect _rect = {0, 0, 0, 0};
        SDL_Texture *_texture = nullptr;
        TextureSpecification _spec = {};
    };

    class SDLTextureManager : public ITextureManager
    {
    public:
        SDLTextureManager(SDL_Renderer *renderer) : _renderer(renderer) {}
        ~SDLTextureManager() = default;

        virtual bool load(const std::string& name, const TextureSpecification& spec)
        {
            auto tex = std::make_shared<SDLTexture>();

            if (std::holds_alternative<TextureImage>(spec.graphical)) {
                auto graph = std::get<TextureImage>(spec.graphical);
                auto img = IMG_LoadTexture(this->_renderer, graph.path.c_str());
                if (!img)
                    return false;
                if (!tex->load(spec, img, graph.subrect))
                    return false;
                this->_textures[name] = tex;
                return true;
            }

            if (!tex->load(spec, nullptr, std::nullopt))
                return false;
            this->_textures[name] = tex;
            return true;
        }

        virtual std::shared_ptr<ITexture> get(const std::string& name)
        {
            if (this->_textures.find(name) == this->_textures.end())
                return nullptr;
            return this->_textures.at(name);
        }

        virtual std::vector<std::pair<std::string, TextureSpecification>> dump() const
        {
            auto specs = std::vector<std::pair<std::string, TextureSpecification>>{};
            specs.reserve(_textures.size());

            for (const auto& [name, texture] : this->_textures)
                specs.push_back({name, texture->specification()});
            return specs;
        }

    private:
        SDL_Renderer *_renderer = nullptr;
        std::map<std::string, std::shared_ptr<SDLTexture>> _textures = {};
    };

    class SDLFont : public IFont
    {
    public:
        SDLFont() = default;
        ~SDLFont() = default;

        bool load(const FontSpecification& spec)
        {
            this->_spec = spec;
            this->_font = TTF_OpenFont(spec.path.c_str(), spec.size);
            this->_color = {
                .r = spec.color.red,
                .g = spec.color.green,
                .b = spec.color.blue,
                .a = spec.color.alpha,
            };
            return true;
        }

        virtual const FontSpecification& specification() const { return _spec; }
        TTF_Font *font() { return this->_font; }
        SDL_Color color() { return this->_color; }

    private:
        FontSpecification _spec = {};
        TTF_Font *_font = nullptr;
        SDL_Color _color = {0, 0, 0, 0};
    };

    class SDLFontManager : public IFontManager
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

        virtual bool load(const std::string& name, const FontSpecification& spec)
        {
            auto font = std::make_shared<SDLFont>();

            if (!font->load(spec))
                return false;
            this->_fonts[name] = font;
            return true;
        }

        virtual std::shared_ptr<IFont> get(const std::string &name)
        {
            if (this->_fonts.find(name) == this->_fonts.end())
                return nullptr;
            return this->_fonts.at(name);
        }

        virtual std::vector<std::pair<std::string, FontSpecification>> dump() const
        {
            auto specs = std::vector<std::pair<std::string, FontSpecification>>{};
            specs.reserve(_fonts.size());

            for (const auto& [name, font] : this->_fonts)
                specs.push_back({name, font->specification()});
            return specs;
        }

    private:
        std::map<std::string, std::shared_ptr<SDLFont>> _fonts;
    };

    class SDLDisplay : public IDisplay
    {
    public:
        SDLDisplay(SDL_Window **window, SDL_Renderer **renderer)
        {
            this->_tileSize = 16;
            this->_width = 80;
            this->_height = 60;
            this->_framerate = 0;
            this->_title = "Arcade";
            this->_opened = true;
            SDL_Init(SDL_INIT_VIDEO);
            SDL_CreateWindowAndRenderer(
                this->_width * this->_tileSize,
                this->_height * this->_tileSize,
                0, window, renderer
            );
            this->_window = *window;
            this->_renderer = *renderer;
            SDL_SetWindowTitle(this->_window, this->_title.c_str());
        }
        ~SDLDisplay() = default;

        virtual void setTitle(const std::string& title)
        {
            this->_title = title;
            SDL_SetWindowTitle(this->_window, title.c_str());
        }

        virtual void setFramerate(uint32_t framerate)
        {
            this->_framerate = framerate;
        }

        virtual void setTileSize(std::size_t size)
        {
            this->_tileSize = size;
            SDL_SetWindowSize(
                this->_window,
                this->_width * this->_tileSize,
                this->_height * this->_tileSize
            );
        }

        virtual void setWidth(std::size_t width)
        {
            this->_width = width;
            SDL_SetWindowSize(
                this->_window,
                this->_width * this->_tileSize,
                this->_height * this->_tileSize
            );
        }

        virtual void setHeight(std::size_t height)
        {
            this->_height = height;
            SDL_SetWindowSize(
                this->_window,
                this->_width * this->_tileSize,
                this->_height * this->_tileSize
            );
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

        virtual bool pollEvent([[maybe_unused]] Event& event)
        {
            if (this->_events.empty())
                return false;

            event = this->_events.front();
            this->_events.pop_front();
            return true;
        }

        static Key MapSDLKey(SDL_Keycode key)
        {
            if (key >= SDL_KeyCode::SDLK_a && key <= SDL_KeyCode::SDLK_z)
                return (Key)((uint32_t)Key::A + key - SDL_KeyCode::SDLK_a);
            if (key >= SDL_KeyCode::SDLK_RIGHT && key <= SDL_KeyCode::SDLK_UP)
                return (Key)((uint32_t)Key::UP + key - SDL_KeyCode::SDLK_RIGHT);

            switch (key)
            {
            case SDL_KeyCode::SDLK_SPACE:
                return Key::SPACE;
            case SDL_KeyCode::SDLK_KP_ENTER:
                return Key::ENTER;
            case SDL_KeyCode::SDLK_ESCAPE:
                return Key::ESCAPE;
            default:
                return Key::UNKNOWN;
            }
            return Key::UNKNOWN;
        }

        virtual void update([[maybe_unused]] float deltaTime)
        {
            SDL_Event sdlEvent = {};
            Event arcEvent = {};

            while (SDL_PollEvent(&sdlEvent)) {
                switch (sdlEvent.type)
                {
                case SDL_EventType::SDL_QUIT:
                    this->_opened = false;
                    break;
                default:
                    arcEvent.type = EventType::KEY_PRESSED;
                    arcEvent.key = MapSDLKey(sdlEvent.key.keysym.sym);
                    _events.push_back(arcEvent);
                    break;
                }
            }
        }

        virtual void clear(Color color = {0, 0, 0, 255})
        {
            SDL_SetRenderDrawColor(this->_renderer, color.red, color.green, color.blue, color.alpha);
            SDL_RenderClear(this->_renderer);
        }

        virtual void draw(const std::shared_ptr<ITexture> texture, float x, float y)
        {
            if (texture == nullptr)
                return;
            auto tex = std::dynamic_pointer_cast<SDLTexture>(texture);
            auto rect = SDL_Rect{};
            rect.x = (int)x * this->_tileSize;
            rect.y = (int)y * this->_tileSize;
            rect.w = (int)this->_tileSize;
            rect.h = (int)this->_tileSize;
            if (!tex->raw()) {
                auto c = tex->color();
                SDL_SetRenderDrawColor(this->_renderer, c.red, c.green, c.blue, c.alpha);
                SDL_RenderFillRect(this->_renderer, &rect);
                SDL_RenderDrawRect(this->_renderer, &rect);
            }
            else
                SDL_RenderCopy(this->_renderer, tex->raw(), tex->rect(), &rect);
        }

        virtual void print(const std::string& string, std::shared_ptr<IFont> font, float x, float y)
        {
            if (font == nullptr)
                return;
            auto attr = dynamic_cast<const SDLFont&>(*font);
            auto surf = TTF_RenderText_Solid(attr.font(), string.c_str(), attr.color());
            auto tex = SDL_CreateTextureFromSurface(this->_renderer, surf);
            SDL_Rect rect = {
                (int)(x * (float)this->_tileSize),
                (int)(y * (float)this->_tileSize),
                surf->w, surf->h };
            SDL_RenderCopy(this->_renderer, tex, NULL, &rect);
            SDL_FreeSurface(surf);
        }

        virtual Rect<float> measure(const std::string& string, std::shared_ptr<IFont> font, float x, float y)
        {
            if (font == nullptr)
                return Rect<float>();
            auto attr = dynamic_cast<const SDLFont&>(*font);
            auto surf = TTF_RenderText_Solid(attr.font(), string.c_str(), attr.color());
            Rect<float> rect = { x, y,
                (float)surf->w  / this->_tileSize,
                (float)surf->h  / this->_tileSize};
            SDL_FreeSurface(surf);
            return rect;
        }

        virtual void flush()
        {
            SDL_RenderPresent(this->_renderer);
        }

    private:
        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;

        bool _opened = false;
        std::deque<Event> _events;
        std::string _title = "";
        uint32_t _framerate = 0;
        std::size_t _tileSize = 0;
        std::size_t _width = 0;
        std::size_t _height = 0;
    };

    class SDLLibrary : public ILibrary
    {
    public:
        SDLLibrary() :
            _display(SDLDisplay(&_window, &_renderer)),
            _textures(SDLTextureManager(_renderer))
        {
        }
        ~SDLLibrary()
        {
            SDL_DestroyRenderer(this->_renderer);
            SDL_DestroyWindow(this->_window);
            SDL_Quit();
        }

        virtual std::string name() const { return " SDL"; }

        virtual IDisplay& display() { return this->_display; }
        virtual ITextureManager& textures() { return this->_textures; }
        virtual IFontManager& fonts() { return this->_fonts; }
        virtual IMusicManager& musics() { return this->_musics; }
        virtual ISoundManager& sounds() { return this->_sounds; }

    private:
        SDLDisplay _display;
        SDLTextureManager _textures;
        SDLFontManager _fonts;
        SDLMusicManager _musics;
        SDLSoundManager _sounds;

        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;
    };
}

extern "C" arc::ILibrary *entrypoint()
{
    return new arc::SDLLibrary();
}
