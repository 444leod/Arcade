/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main.cpp
*/

#include "IGame.hpp"

#include <dlfcn.h>
#include <memory>
#include <chrono>
#include <iostream>

template<typename T>
class SharedLibraryLoader {
public:
    SharedLibraryLoader(const std::string& path)
    {
        this->_path = path;
        this->_handle = dlopen(path.c_str(), RTLD_LAZY);
        std::cout << "Loading " << path << " (" << this->_handle << ")" << std::endl;
    }

    SharedLibraryLoader(SharedLibraryLoader<T>&& other)
    {
        if (this == &other)
            return;

        this->_path = std::move(other._path);
        this->_handle = other._handle;
        other._handle = nullptr;
    }

    SharedLibraryLoader<T>& operator=(SharedLibraryLoader<T>&& other)
    {
        if (this == &other)
            return *this;

        this->_path = std::move(other._path);
        this->_handle = other._handle;
        other._handle = nullptr;

        return *this;
    }

    ~SharedLibraryLoader()
    {
        std::cout << "Unloading " << _path << std::endl;
        if (this->_handle != nullptr)
            dlclose(this->_handle);
    }

    std::unique_ptr<T> get()
    {
        if (this->_handle == nullptr)
            return nullptr;

        auto entrypoint = reinterpret_cast<T*(*)()>(dlsym(this->_handle, "entrypoint"));

        if (entrypoint == nullptr)
            return nullptr;

        return std::unique_ptr<T>(entrypoint());
    }

private:
    std::string _path;
    void* _handle;
};

class Core {
public:
    Core()
        : _sl_lib{_graphicLibraries[_currentGraphicLibrary]},
          _sl_game{_gameLibraries[_currentGameLibrary]},
          _lib(_sl_lib.get()),
          _game(_sl_game.get()),
          _switch_display_next_frame{false}
    {
        if (_lib == nullptr || _game == nullptr)
            throw std::runtime_error("Failed to load library or game");
    }

    void switch_game_lib()
    {
        _game.reset(nullptr);

        _currentGameLibrary = (_currentGameLibrary + 1) % _gameLibraries.size();
        _sl_game = SharedLibraryLoader<arc::IGame>(_gameLibraries[_currentGameLibrary]);
        _game = _sl_game.get();

        if (_game == nullptr)
            throw std::runtime_error("Failed to load game");
    }

    void switch_graphic_lib()
    {
        std::string title = _lib->display().title();
        uint32_t framerate = _lib->display().framerate();
        std::size_t tileSize = _lib->display().tileSize();
        std::size_t width = _lib->display().width();
        std::size_t height = _lib->display().height();

        auto textures = _lib->textures().dump();
        auto fonts = _lib->fonts().dump();
        auto sounds = _lib->sounds().dump();
        auto musics = _lib->musics().dump();

        _lib.reset(nullptr);

        _currentGraphicLibrary = (_currentGraphicLibrary + 1) % _graphicLibraries.size();
        _sl_lib = SharedLibraryLoader<arc::ILibrary>(_graphicLibraries[_currentGraphicLibrary]);
        _lib = _sl_lib.get();

        if (_lib == nullptr)
            throw std::runtime_error("Failed to load library");

        _lib->display().setTitle(title);
        _lib->display().setFramerate(framerate);
        _lib->display().setTileSize(tileSize);
        _lib->display().setWidth(width);
        _lib->display().setHeight(height);

        for (const auto& texture : textures)
            _lib->textures().load(texture.first, texture.second);

        for (const auto& font : fonts)
            _lib->fonts().load(font.first, font.second);

        for (const auto& sound : sounds)
            _lib->sounds().load(sound.first, sound.second);

        for (const auto& music : musics)
            _lib->musics().load(music.first, music.second);
    }

    void run(int ac, char** av)
    {
        this->verify_args(ac, av);
        _game->initialize(*_lib);

        arc::Event event;
        auto before = std::chrono::high_resolution_clock::now();

        while (_lib->display().opened()) {
            auto now = std::chrono::high_resolution_clock::now();

            if (_switch_display_next_frame) {
                _switch_display_next_frame = false;
                switch_graphic_lib();
            }
            if (_switch_game_next_frame) {
                _switch_game_next_frame = false;
                switch_game_lib();
                _game->initialize(*_lib);
            }

            float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
            before = now;

            _lib->display().update(deltaTime);
            while (_lib->display().pollEvent(event)) {
                if (event.type == arc::EventType::KEY_PRESSED && event.key == arc::Key::SPACE)
                    _switch_display_next_frame = true;
                if (event.type == arc::EventType::KEY_PRESSED && event.key == arc::Key::ENTER)
                    _switch_game_next_frame = true;
                if (event.type == arc::EventType::KEY_PRESSED)
                    _game->onKeyPressed(*_lib, event.key);
                if (event.type == arc::EventType::MOUSE_BUTTON_PRESSED)
                    _game->onMouseButtonPressed(*_lib, event.mouse.button, event.mouse.x, event.mouse.y);
            }
            _game->update(*_lib, deltaTime);
            _game->draw(*_lib);
        }
    }

    void verify_args(int ac, [[maybe_unused]] char** av)
    {
        if (ac != 2)
            throw std::runtime_error("Usage: ./arcade path_to_graphic_library");
    }

private:
    std::vector<std::string> _graphicLibraries = {
        "./lib/arcade_ncurses.so",
        "./lib/arcade_sfml.so",
        "./lib/arcade_sdl2.so",
    };
    size_t _currentGraphicLibrary = 0;
    #if PACMAN
        std::vector<std::string> _gameLibraries = {
            "./lib/arcade_pacman.so",
        };
    #else
        std::vector<std::string> _gameLibraries = {
            "./lib/arcade_example.so",
            "./lib/arcade_pacman.so"
        };
    #endif
    size_t _currentGameLibrary = 0;

    SharedLibraryLoader<arc::ILibrary> _sl_lib;
    SharedLibraryLoader<arc::IGame> _sl_game;

    std::unique_ptr<arc::ILibrary> _lib;
    std::unique_ptr<arc::IGame> _game;

    bool _switch_display_next_frame;
    bool _switch_game_next_frame;
};

int main(int ac, char** av)
{
    try {
        Core().run(ac, av);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
