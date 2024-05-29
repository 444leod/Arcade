/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include "LibraryLoader.hpp"
#include "IGame.hpp"
#include "CoreMenu.hpp"
#include "Score.hpp"
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
            this->_lib_handler = this->_loader.load(path);
            if (!this->_lib_handler)
                throw CoreException("Could not open " + path + ".");
            this->_cur_lib = this->_lib_handler->get<arc::ILibrary>();
            if (!this->_loader.contains(arc::SharedLibraryType::GAME))
                throw CoreException("No game library found.");
            this->_menu = std::make_shared<CoreMenu>(this->_loader.libs(), this->_lib_handler);
            this->_cur_game = std::static_pointer_cast<arc::IGame>(this->_menu);

            std::ifstream rstream(".scores");
            if (!rstream.is_open())
                return;
            std::string tmp = "";
            while (std::getline(rstream, tmp)) {
                if (tmp.empty()) break;
                arc::Score score;
                tmp >> score;
                this->_scores[score.game] = score;
            }
            rstream.close();
            this->_menu->updateScores(this->_scores);
        }

        ~Core()
        {
            if (this->_cur_game != this->_menu)
                this->saveScore();
        }

        void start_game()
        {
            for (const auto& sound : this->_cur_lib->musics().dump()) {
                this->_cur_lib->musics().stop(sound.first);
            }
            for (const auto& sound : this->_cur_lib->sounds().dump()) {
                this->_cur_lib->sounds().stop(sound.first);
            }
            this->_menu->setRunning(false);
            this->_game_handler.reset();
            this->_game_handler = this->_menu->game();
            this->_cur_game.reset();
            this->_cur_game = this->_game_handler->get<arc::IGame>();
            if (this->_cur_game == nullptr)
                throw CoreException("Object failed to load game");
            this->_cur_game->initialize(*_cur_lib);
        }

        void leave_game()
        {
            for (const auto& sound : this->_cur_lib->musics().dump()) {
                this->_cur_lib->musics().stop(sound.first);
            }
            for (const auto& sound : this->_cur_lib->sounds().dump()) {
                this->_cur_lib->sounds().stop(sound.first);
            }
            if (this->_menu->running()) {
                this->_cur_lib->display().close();
            } else {
                this->saveScore();
                this->_cur_game.reset();
                this->_cur_game = this->_menu;
                this->_menu->initialize(*_cur_lib);
                this->_menu->updateScores(this->_scores);
            }
        }

        void run()
        {
            auto enter_game = false;
            auto escape_game = false;
            auto before = std::chrono::high_resolution_clock::now();

            this->_cur_game->initialize(*_cur_lib);
            while (this->_cur_lib->display().opened()) {
                arc::Event event = {};
                auto now = std::chrono::high_resolution_clock::now();
                float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
                before = now;

                if (enter_game) {
                    this->start_game();
                    enter_game = false;
                    continue;
                }
                if (escape_game) {
                    this->leave_game();
                    escape_game = false;
                    continue;
                }

                this->_cur_lib->display().update(deltaTime);

                while (_cur_lib->display().pollEvent(event)) {
                    if (event.key.code == arc::KeyCode::I || event.key.code == arc::KeyCode::K)
                        enter_game = !this->_menu->running();
                    if (event.type == arc::EventType::KEY_PRESSED && event.key.code == arc::KeyCode::ENTER)
                        enter_game = true;
                    if (event.type == arc::EventType::KEY_PRESSED && event.key.code == arc::KeyCode::ESCAPE)
                        escape_game = true;

                    this->_cur_game->onKeyPressed(*_cur_lib, event.key.code, event.key.shift);
                    if (!this->_menu->running())
                        this->_menu->onKeyPressed(*_cur_lib, event.key.code, event.key.shift);
                }

                this->_cur_game->update(*_cur_lib, deltaTime);
                this->_cur_game->draw(*_cur_lib);
            }
        }

    private:
        void saveScore()
        {
            std::ofstream stream(".scores");

            if (!stream.is_open())
                return;
            if (!this->_scores.contains(this->_game_handler->name()) || this->_scores[this->_game_handler->name()].hs < this->_cur_game->score())
                this->_scores[this->_game_handler->name()] = { this->_game_handler->name(), this->_menu->player(), this->_cur_game->score() };
            for (auto entry : this->_scores)
                stream << entry.second;
            stream.close();
        }

        std::shared_ptr<CoreMenu> _menu = nullptr;
        std::shared_ptr<arc::IGame> _cur_game = nullptr;
        std::shared_ptr<arc::ILibrary> _cur_lib = nullptr;
        std::shared_ptr<LibraryObject> _game_handler = nullptr;
        std::shared_ptr<LibraryObject> _lib_handler = nullptr;

        std::map<std::string, arc::Score> _scores = {};
        LibraryLoader _loader;
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
