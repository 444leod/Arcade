/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** GameOver
*/

#pragma once

#include "../IGameState.hpp"
#include <iostream>

class GameOver : public IGameState {
    public:
        GameOver(IGameState::State &currentState, uint64_t &score) : _currentState(currentState), _score(score) {}
        ~GameOver() = default;

        virtual void initialize(arc::ILibrary& lib) override;
        virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key) override;
        virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) override;
        virtual void update(arc::ILibrary& lib, float deltaTime) override;
        virtual void draw(arc::ILibrary& lib) override;
        virtual void onEnter(IGameState::State lastState, arc::ILibrary& lib) override;
        virtual void onExit(IGameState::State nextState, arc::ILibrary& lib) override;

    protected:
    private:
        IGameState::State& _currentState;
        uint64_t &_score;
};
