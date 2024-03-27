/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** IGameState
*/

#pragma once

#include "IGame.hpp"

class IGameState {
    public:
        IGameState() = default;
        ~IGameState() =  default;

        static enum class State {
            GAME,
            PAUSE,
            WIN,
            LOSE,
        } _state;

        virtual void initialize(arc::ILibrary& lib) = 0;
        virtual void onKeyPressed(arc::ILibrary& lib, arc::Key key) = 0;
        virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) = 0;
        virtual void update(arc::ILibrary& lib, float deltaTime) = 0;
        virtual void draw(arc::ILibrary& lib) = 0;
        virtual void onEnter(IGameState::State lastState) = 0;
        virtual void onExit(IGameState::State nextState) = 0;

    protected:
    private:
};
