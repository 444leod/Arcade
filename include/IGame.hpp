/*
** EPITECH PROJECT, 2024
** IGame.hpp
** File description:
** IGame.hpp
*/

#pragma once

#include "ILibrary.hpp"

namespace arc {

    /**
     * @brief Represents a game that is exported by a shared library.
     */
    class IGame {
    public:
        virtual ~IGame() = default;

        /**
         * @brief Called once when the game is created. It should be used to
         *        load the textures.
         * @param lib the current library
         */
        virtual void initialize(ILibrary& lib) = 0;

        /**
         * @brief Called when a key is pressed
         */
        virtual void onKeyPressed(ILibrary& lib, KeyCode key, bool shift) = 0;

        virtual void onKeyDown(ILibrary& lib, KeyCode key) = 0;

        virtual void onKeyReleased(ILibrary& lib, KeyCode key) = 0;

        /**
         * @brief Called when a mouse button is pressed
         */
        virtual void onMouseButtonPressed(ILibrary& lib, MouseButton button, int32_t x, int32_t y) = 0;

        virtual void onMouseButtonDown(ILibrary& lib, MouseButton button, int32_t x, int32_t y) = 0;

        virtual void onMouseButtonReleased(ILibrary& lib, MouseButton button, int32_t x, int32_t y) = 0;

        /**
         * @brief Called when a joystick button is pressed
        */
        virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) = 0;

        virtual void onJoystickButtonDown(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) = 0;

        virtual void onJoystickButtonReleased(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) = 0;

        virtual void onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, uint32_t id) = 0;

        /**
         * @brief Updates the game. It should be used to update the game state.
         *
         * @param deltaTime the time since the last update
         */
        virtual void update(ILibrary& lib, float deltaTime) = 0;

        /**
         * @brief This function is called to draw the game. It should be used
         *        to draw based on the current game state and not do any logic.
         * @param lib the current library
         */
        virtual void draw(ILibrary& lib) = 0;

        /**
         * @brief This function is called to get current score of the game.
         *        It should be used in the core to handle the highscore mechanism.
         * @param lib the current library
         */
        virtual uint64_t score() const = 0;
    };
}
