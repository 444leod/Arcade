/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main.cpp
*/

#include "arcade/IGame.hpp"

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
        : _sl_lib{"./lib_arcade_ncurses.so"},
          _sl_game{"./arcade_snake.so"},
          _lib(_sl_lib.get()),
          _game(_sl_game.get()),
          _switch_next_frame{false},
          _isSFML{false}
    {
        if (_lib == nullptr || _game == nullptr)
            throw std::runtime_error("Failed to load library or game");
    }

    void switch_lib()
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

        // Unload the current library
        _lib.reset(nullptr);

        // Load the next library
        _sl_lib = SharedLibraryLoader<arc::ILibrary>(_isSFML ? "./lib_arcade_ncurses.so" : "./lib_arcade_sfml.so");
        _isSFML = !_isSFML;
        _lib = _sl_lib.get();

        if (_lib == nullptr)
            throw std::runtime_error("Failed to load library");

        // Set the previous specifications
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

    void run()
    {
        _game->initialize(*_lib);

        arc::Event event;
        auto before = std::chrono::high_resolution_clock::now();

        while (_lib->display().opened()) {
            auto now = std::chrono::high_resolution_clock::now();

            if (_switch_next_frame) {
                _switch_next_frame = false;
                switch_lib();
            }

            float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
            before = now;

            _lib->display().update(deltaTime);
            while (_lib->display().pollEvent(event)) {
                if (event.type == arc::EventType::KEY_PRESSED && event.key == arc::Key::SPACE)
                    _switch_next_frame = true;
                if (event.type == arc::EventType::KEY_PRESSED)
                    _game->onKeyPressed(*_lib, event.key);
                if (event.type == arc::EventType::MOUSE_BUTTON_PRESSED)
                    _game->onMouseButtonPressed(*_lib, event.mouse.button, event.mouse.x, event.mouse.y);
            }
            _game->update(*_lib, deltaTime);
            _game->draw(*_lib);
        }
    }

private:
    SharedLibraryLoader<arc::ILibrary> _sl_lib;
    SharedLibraryLoader<arc::IGame> _sl_game;

    std::unique_ptr<arc::ILibrary> _lib;
    std::unique_ptr<arc::IGame> _game;

    bool _switch_next_frame;
    bool _isSFML;
};

int main()
{
    try {
        Core().run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
