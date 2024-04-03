/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include "LibraryLoader.hpp"
#include "IGame.hpp"
#include "CoreMenu.hpp"
#include <iostream>
#include <vector>

class CoreException : public std::exception
{
    public:
        CoreException(const std::string& msg) : _msg(msg) {}
        ~CoreException() = default;
        virtual const char *what() const noexcept { return _msg.c_str(); }
    private:
        std::string _msg;
};

class Core
{
    public:
        Core(const std::string& path) : _loader(LibraryLoader("./lib"))
        {
            if (!this->_loader.contains(path, arc::SharedLibraryType::LIBRARY))
                throw CoreException("File " + path + " is not a valid graphical library.");
            auto lib = this->_loader.load(path);
            if (!lib)
                throw CoreException("Could not open " + path + ".");
            this->_lib = lib->get<arc::ILibrary>();
            if (!this->_loader.contains(arc::SharedLibraryType::GAME))
                throw CoreException("No game library found.");
            this->_game = std::make_shared<CoreMenu>(_loader.libs());
        }

        ~Core()
        {
        }

        void switch_game_lib()
        {
            auto menu = std::dynamic_pointer_cast<CoreMenu>(this->_game);

            if (menu != nullptr) {
                this->_game.reset();
                auto next = menu->getSelection();
                this->_game = next;
            } else {
                this->_game.reset();
                this->_game = std::make_shared<CoreMenu>(_loader.libs());
            }
            this->_game->initialize(*_lib);
        }

        void switch_graphic_lib()
        {
            std::string title = this->_lib->display().title();
            uint32_t framerate = this->_lib->display().framerate();
            std::size_t tileSize = this->_lib->display().tileSize();
            std::size_t width = this->_lib->display().width();
            std::size_t height = this->_lib->display().height();

            auto textures = this->_lib->textures().dump();
            auto fonts = this->_lib->fonts().dump();
            auto sounds = this->_lib->sounds().dump();
            auto musics = this->_lib->musics().dump();

            this->_lib.reset();
            this->_lib = this->_loader.nextLib()->get<arc::ILibrary>();

            if (_lib == nullptr)
                throw std::runtime_error("Failed to load library");

            this->_lib->display().setTitle(title);
            this->_lib->display().setFramerate(framerate);
            this->_lib->display().setTileSize(tileSize);
            this->_lib->display().setWidth(width);
            this->_lib->display().setHeight(height);

            for (const auto& texture : textures)
                this->_lib->textures().load(texture.first, texture.second);

            for (const auto& font : fonts)
                this->_lib->fonts().load(font.first, font.second);

            for (const auto& sound : sounds)
                this->_lib->sounds().load(sound.first, sound.second);

            for (const auto& music : musics)
                this->_lib->musics().load(music.first, music.second);
        }

        void run()
        {
            auto lib_switch = false;
            auto game_switch = false;
            auto before = std::chrono::high_resolution_clock::now();

            _game->initialize(*_lib);
            while (_lib->display().opened()) {
                arc::Event event = {};
                auto now = std::chrono::high_resolution_clock::now();
                float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
                before = now;

                if (lib_switch) {
                    this->switch_graphic_lib();
                    lib_switch = false;
                    continue;
                }

                if (game_switch) {
                    switch_game_lib();
                    game_switch = false;
                    continue;
                }

                _lib->display().update(deltaTime);
                while (_lib->display().pollEvent(event)) {
                    if (event.type == arc::EventType::KEY_PRESSED && event.key == arc::Key::SPACE)
                        lib_switch = true;
                    if (event.type == arc::EventType::KEY_PRESSED && event.key == arc::Key::ENTER)
                        game_switch = true;
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
        std::shared_ptr<arc::ILibrary> _lib = nullptr;
        std::shared_ptr<arc::IGame> _game = nullptr;
        LibraryLoader _loader;
};

int main(int ac, char **av, [[maybe_unused]] char **env)
{
    if (ac != 2) {
        std::cerr << "Wrong argument count" << std::endl;
        return 84;
    }

    try {
        Core core(av[1]);
        core.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
