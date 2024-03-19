/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#include "ILibrary.hpp"
#include <map>
#include <deque>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace arc
{
    class SDLTexture : public ITexture
    {
    public:
        SDLTexture() = default;
        ~SDLTexture() = default;


        bool load(const TextureSpecification& spec,
            SDL_Texture *texture,
            std::optional<arc::Rect<uint32_t>> rect)
        {
            if (std::holds_alternative<Color>(spec.graphical))
                _color = std::get<Color>(spec.graphical);
            this->_spec = spec;
            this->_texture = texture;
            if (rect.has_value()) {
                this->_rect = new SDL_Rect();
                this->_rect->x = (int)rect.value().x;
                this->_rect->y = (int)rect.value().y;
                this->_rect->w = (int)rect.value().width;
                this->_rect->h = (int)rect.value().height;
            }
            return true;
        }

        virtual const TextureSpecification& specification() const { return this->_spec; }
        SDL_Texture *raw() const { return this->_texture; }
        Color color() const { return this->_color; }
        const SDL_Rect *rect() const { return this->_rect; }

    private:
        Color _color = {};
        SDL_Rect *_rect = NULL;
        SDL_Texture *_texture = nullptr;
        TextureSpecification _spec = {};
    };

    class SDLTextureManager : public ITextureManager
    {
    public:
        SDLTextureManager(SDL_Renderer *renderer) : _renderer(renderer) {}
        ~SDLTextureManager() = default;

        virtual bool load(const std::string& name, const TextureSpecification& spec
            )
        {
            auto tex = SDLTexture();

            if (std::holds_alternative<TextureImage>(spec.graphical)) {
                auto graph = std::get<TextureImage>(spec.graphical);
                auto img = IMG_LoadTexture(this->_renderer, graph.path.c_str());
                if (!img)
                    return false;
                if (!tex.load(spec, img, graph.subrect))
                    return false;
                this->_textures[name] = tex;
                return true;
            }

            if (!tex.load(spec, nullptr, std::nullopt))
                return false;
            this->_textures[name] = tex;
            return true;
        }

        virtual ITexture& get(const std::string& name)
        {
            return _textures.at(name);
        }

        virtual std::vector<std::pair<std::string, TextureSpecification>> dump() const
        {
            auto specs = std::vector<std::pair<std::string, TextureSpecification>>{};
            specs.reserve(_textures.size());

            for (const auto& [name, texture] : this->_textures)
                specs.push_back({name, texture.specification()});

            return specs;
        }

    private:
        SDL_Renderer *_renderer = nullptr;
        std::map<std::string, SDLTexture> _textures = {};
    };

    class SDLFont : public IFont
    {
    public:
        SDLFont() = default;
        ~SDLFont() = default;

        virtual const FontSpecification& specificiation() const
        {
            return _spec;
        }

    private:
        FontSpecification _spec = {};
    };

    class SDLFontManager : public IFontManager
    {
    public:
        virtual bool load(const std::string& name, const FontSpecification& specification)
        {
            (void)name;
            (void)specification;
            return true;
        }

        virtual IFont& get(const std::string &name)
        {
            return _fonts.at(name);
        }

        virtual std::vector<std::pair<std::string, FontSpecification>> dump() const
        {
            auto specs = std::vector<std::pair<std::string, FontSpecification>>{};
            specs.reserve(_fonts.size());

            for (const auto& [name, font] : this->_fonts)
                specs.push_back({name, font.specificiation()});

            return specs;
        }

    private:
        std::map<std::string, SDLFont> _fonts;
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

        virtual void update([[maybe_unused]] float deltaTime)
        {
            SDL_Event sdlEvent;
            Event arcEvent;

            while (SDL_PollEvent(&sdlEvent)) {
                switch (sdlEvent.type)
                {
                case SDL_EventType::SDL_QUIT:
                    this->_opened = false;
                    break;
                case SDL_EventType::SDL_KEYDOWN:
                    arcEvent.type = EventType::KEY_PRESSED;
                    arcEvent.key = (Key)(sdlEvent.key.keysym.sym - SDL_KeyCode::SDLK_a);
                    _events.push_back(arcEvent);
                default:
                    break;
                }
            }
        }

        virtual void clear(Color color = {0, 0, 0, 255})
        {
                SDL_SetRenderDrawColor(this->_renderer, color.red, color.green, color.blue, color.alpha);
            SDL_RenderClear(this->_renderer);
        }

        virtual void draw(const ITexture& texture, float x, float y)
        {
            auto rect = SDL_Rect{};
            rect.x = (int)x * this->_tileSize;
            rect.y = (int)y * this->_tileSize;
            rect.w = (int)this->_tileSize;
            rect.h = (int)this->_tileSize;
            auto tex = dynamic_cast<const SDLTexture&>(texture);
            if (!tex.raw()) {
                auto c = tex.color();
                SDL_SetRenderDrawColor(this->_renderer, c.red, c.green, c.blue, c.alpha);
                SDL_RenderFillRect(this->_renderer, &rect);
                SDL_RenderDrawRect(this->_renderer, &rect);
            }
            else
                SDL_RenderCopy(this->_renderer, tex.raw(), tex.rect(), &rect);
        }

        virtual void print(const std::string& string, const IFont& font, float x, float y)
        {
            (void)string;
            (void)font;
            (void)x;
            (void)y;
        }

        virtual Rect<float> measure(const std::string& string, const IFont& font, float x, float y)
        {
            (void)string;
            (void)font;
            (void)x;
            (void)y;
            return Rect<float>();
        }

        virtual void flush()
        {
            SDL_RenderPresent(this->_renderer);
        }

    private:
        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;

        bool _opened = false;
        std::deque<arc::Event> _events;
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
        ~SDLLibrary() = default;

        virtual std::string name() const
        {
            return "SDL";
        }

        virtual IDisplay& display()
        {
            return _display;
        }

        virtual ITextureManager& textures()
        {
            return _textures;
        }

        virtual IFontManager& fonts()
        {
            return _fonts;
        }

    private:
        SDLDisplay _display;
        SDLTextureManager _textures;
        SDLFontManager _fonts;

        SDL_Window *_window;
        SDL_Renderer *_renderer;
    };
}

extern "C" arc::ILibrary *entrypoint()
{
    return new arc::SDLLibrary();
}