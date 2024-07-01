/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** GameSwitcher
*/

#pragma once

#include "CoreMenu.hpp"
#include "LibraryLoader.hpp"
#include "Score.hpp"
#include <array>
#include <map>

class GameSwitcher {
    public:
        GameSwitcher() = default;
        ~GameSwitcher();

        void init(const LibraryLoader& loader, arc::ILibrary& lib) noexcept;
        void update(arc::ILibrary& lib, double dt) noexcept;

        std::shared_ptr<arc::IGame> current() const noexcept { return this->_current; }
        void next() noexcept;
        void previous() noexcept;

        void setPressingStart(bool state) noexcept { this->_pressing_start = state; }
        void setPressingExit(bool state) noexcept { this->_pressing_exit = state; }

    private:
        void _start(arc::ILibrary& lib) noexcept;
        void _exit(arc::ILibrary& lib) noexcept;
        std::array<std::string, 3> _names() const noexcept;
        void _loadScores() noexcept;
        void _saveScores() noexcept;

    private:
        bool _pressing_start = false;
        bool _pressing_exit = false;
        double _start_timer = 0.0;
        double _exit_timer = 0.0;

        uint8_t _selector_index = 0;
        std::shared_ptr<arc::IGame> _current = nullptr;
        std::shared_ptr<CoreMenu> _menu = nullptr;
        std::vector<std::shared_ptr<LibraryObject>> _games = {};
        std::map<std::string, arc::Score> _scores = {};
};
