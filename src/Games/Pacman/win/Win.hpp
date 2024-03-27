/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Win
*/

#pragma once

#include "../IGameState.hpp"

class Win : public IGameState {
    public:
        Win(IGameState::State &currentState) : _currentState(currentState) {};
        ~Win() = default;

        virtual void initialize(arc::ILibrary& lib) override;
        virtual void onKeyPressed(arc::ILibrary& lib, arc::Key key) override;
        virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) override;
        virtual void update(arc::ILibrary& lib, float deltaTime) override;
        virtual void draw(arc::ILibrary& lib) override;
        virtual void onEnter(IGameState::State lastState) override;
        virtual void onExit(IGameState::State nextState) override;

    protected:
    private:
        IGameState::State &_currentState;
};