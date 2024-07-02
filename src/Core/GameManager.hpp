/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** GameManager
*/

#pragma once

#include "CoreMenu.hpp"
#include "LibraryLoader.hpp"
#include "Score.hpp"
#include <array>
#include <map>

/**
 * @brief Managers the game libraries.
 */
class GameManager {
    public:
        GameManager() = default;
        ~GameManager();

        /**
         * @brief Initiates a `GameManager` object.
         * @param loader The library loader used in the `Core`.
         * @param lib The graphical library in use in the `Core`.
         */
        void init(const LibraryLoader& loader, arc::ILibrary& lib) noexcept;
        /**
         * @brief Updates the game state.
         * @param lib The current graphical library.
         * @param dt The delta time in between frames.
         */
        void update(arc::ILibrary& lib, double dt) noexcept;

        /**
         * @brief Gets the current `IGame` (game instance).
         * @return A `shared_ptr`.
         */
        std::shared_ptr<arc::IGame> current() const noexcept { return this->_current; }

        /**
         * @brief Changes the selector to the next game.
         * @warning Only takes effect in the main menu.
         */
        void next() noexcept;

        /**
         * @brief Changes the selector to the previous game.
         * @warning Only takes effect in the main menu.
         */
        void previous() noexcept;

        /**
         * @brief Set the state of the start button.
         * @param state The state of the button. `true` when it is pressed, `false` otherwise.
         */
        void setPressingStart(bool state) noexcept { this->_pressing_start = state; }

        /**
         * @brief Set the state of the exit button.
         * @param state The state of the button. `true` when it is pressed, `false` otherwise.
         */
        void setPressingExit(bool state) noexcept { this->_pressing_exit = state; }

    private:
        //* Starts the selected game / restart current game.
        void _start(arc::ILibrary& lib) noexcept;
        //* Exits the current game.
        void _exit(arc::ILibrary& lib) noexcept;
        // * Gets the names of the games for the menu.
        std::array<std::string, 3> _names() const noexcept;
        //* Load scores into `_scores`.
        void _loadScores() noexcept;
        //* Saves `_scores` into the `.scores` file.
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
