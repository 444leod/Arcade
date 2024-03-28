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

        //? No need for deinitalize, the destructor will do the job

        /**
         * @brief Called when a key is pressed
         * @param event the event
         */
        virtual void onKeyPressed(ILibrary& lib, Key key) = 0;

        /**
         * @brief Called when a mouse button is pressed
         * @param event the event
         */
        virtual void onMouseButtonPressed(ILibrary& lib, MouseButton button, int32_t x, int32_t y) = 0;

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
