/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include "LibraryLoader.hpp"
#include "IGame.hpp"
#include "Score.hpp"
#include "GameSwitcher.hpp"
#include <iostream>
#include <vector>
#include <fstream>

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
        Core(const std::string& path, bool tty) : _loader(LibraryLoader("./lib", tty))
        {
            if (!this->_loader.contains(path, arc::SharedLibraryType::LIBRARY))
                throw CoreException("File " + path + " is not a valid graphical library.");

            auto lib_object = this->_loader.get(path);
            if (lib_object == nullptr)
                throw CoreException("Could not open " + path + ".");
            this->_lib = lib_object->get<arc::ILibrary>();

            if (!this->_loader.contains(arc::SharedLibraryType::GAME))
                throw CoreException("No game library found.");
            this->_switcher.init(this->_loader, *this->_lib);
        }

        ~Core() = default;

        void run()
        {
            auto before = std::chrono::high_resolution_clock::now();

            while (this->_lib->display().opened()) {
                arc::Event event = {};
                auto now = std::chrono::high_resolution_clock::now();
                float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
                before = now;

                auto game = this->_switcher.current();
                this->_switcher.update(*this->_lib, deltaTime);
                this->_lib->display().update(deltaTime);

                while (_lib->display().pollEvent(event)) {
                    switch (event.eventType)
                    {
                        case arc::EventType::PRESSED:
                        {
                            switch (event.keyType) {
                                case arc::KeyType::KEY:
                                {
                                    if (event.key.code == arc::KeyCode::ENTER)  this->_switcher.setPressingStart(true);
                                    if (event.key.code == arc::KeyCode::ESCAPE) this->_switcher.setPressingExit(true);
                                    if (event.key.code == arc::KeyCode::UP)     this->_switcher.previous();
                                    if (event.key.code == arc::KeyCode::DOWN)   this->_switcher.next();
                                    game->onKeyPressed(*this->_lib, event.key.code, event.key.shift);
                                    break;
                                }
                                case arc::KeyType::MOUSE_BUTTON:
                                {
                                    game->onMouseButtonPressed(*this->_lib, event.mouse.button, event.mouse.x, event.mouse.y);
                                    break;
                                }
                                case arc::KeyType::JOYSTICK_BUTTON:
                                {
                                    if (event.joystick.button == arc::JoystickButton::R1)   this->_switcher.setPressingStart(true);
                                    if (event.joystick.button == arc::JoystickButton::R2)   this->_switcher.setPressingExit(true);
                                    game->onJoystickButtonPressed(*this->_lib, event.joystick.button, event.joystick.id);
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        }
                        case arc::EventType::DOWN:
                        {
                            switch (event.keyType) {
                                case arc::KeyType::KEY:
                                {
                                    game->onKeyDown(*this->_lib, event.key.code);
                                    break;
                                }
                                case arc::KeyType::MOUSE_BUTTON:
                                {
                                    game->onMouseButtonDown(*this->_lib, event.mouse.button, event.mouse.x, event.mouse.y);
                                    break;
                                }
                                case arc::KeyType::JOYSTICK_BUTTON:
                                {
                                    game->onJoystickButtonDown(*this->_lib, event.joystick.button, event.joystick.id);
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        }
                        case arc::EventType::RELEASED:
                        {
                            switch (event.keyType) {
                                case arc::KeyType::KEY:
                                {
                                    if (event.key.code == arc::KeyCode::ENTER)  this->_switcher.setPressingStart(false);
                                    if (event.key.code == arc::KeyCode::ESCAPE) this->_switcher.setPressingExit(false);
                                    game->onKeyReleased(*this->_lib, event.key.code);
                                    break;
                                }
                                case arc::KeyType::MOUSE_BUTTON:
                                {
                                    game->onMouseButtonReleased(*this->_lib, event.mouse.button, event.mouse.x, event.mouse.y);
                                    break;
                                }
                                case arc::KeyType::JOYSTICK_BUTTON:
                                {
                                    if (event.joystick.button == arc::JoystickButton::R1)   this->_switcher.setPressingStart(false);
                                    if (event.joystick.button == arc::JoystickButton::R2)   this->_switcher.setPressingExit(false);
                                    game->onJoystickButtonReleased(*this->_lib, event.joystick.button, event.joystick.id);
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        }
                        case arc::EventType::MOVE:
                        {
                            game->onJoystickMove(*this->_lib, event.joystick.axis, event.joystick.id);
                            break;
                        }
                    }
                }

                game->update(*_lib, deltaTime);
                game->draw(*_lib);
            }
        }

    private:
        std::shared_ptr<arc::ILibrary> _lib;
        LibraryLoader _loader;
        GameSwitcher _switcher;
};

int main(int ac, char **av, char **env)
{
    std::string lib = "./lib/arcade_sfml.so";
    bool tty = true;

    if (ac > 2) {
        std::cerr << "Wrong argument count" << std::endl;
        return 84;
    }
    if (ac > 1)
        lib = av[1];
    for (int i = 0; env[i]; i++) {
        if (!std::string(env[i]).starts_with("DISPLAY"))
            continue;
        tty = false;
        break;
    }

    try {
        Core core(lib, tty);
        core.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
