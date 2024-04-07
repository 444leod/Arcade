/*
** EPITECH PROJECT, 2024
** MyGame.cpp
** File description:
** MyGame.cpp
*/

#include "IGame.hpp"
#include "IGameState.hpp"
#include "Pacman.hpp"

#include "./game/Game.hpp"
#include "./pause/Pause.hpp"
#include "./win/Win.hpp"
#include "./game-over/GameOver.hpp"
#include "SharedLibraryType.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>

class Pacman : public arc::IGame {
public:
    virtual void initialize(arc::ILibrary& lib)
    {
        lib.display().setTitle("Arcade");
        lib.display().setFramerate(60);
        lib.display().setTileSize(32);
        lib.display().setHeight(_height);
        lib.display().setWidth(_width);
        _states = {
            {IGameState::State::GAME,   std::make_shared<Game>(_currentState, _score)},
            {IGameState::State::PAUSE,  std::make_shared<Pause>(_currentState, _score)},
            {IGameState::State::WIN,    std::make_shared<Win>(_currentState, _score)},
            {IGameState::State::LOSE,   std::make_shared<GameOver>(_currentState, _score)}
        };
        arc::MusicSpecification musicSpec;
        musicSpec.path = "assets/pacman-theme.wav";
        musicSpec.loop = true;
        musicSpec.isPlaying = true;
        musicSpec.startOffset = 0;
        lib.musics().load("pacman-theme", musicSpec);

        for (auto& state : _states) {
            state.second->initialize(lib);
        }
    }

    virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key, [[maybe_unused]] bool shift)
    {
        _states[_currentState]->onKeyPressed(lib, key);
    }

    virtual void onMouseButtonPressed(
        arc::ILibrary& lib,
        arc::MouseButton button,
        int32_t x,
        int32_t y
    )
    {
        _states[_currentState]->onMouseButtonPressed(lib, button, x, y);
    }

    virtual void update(arc::ILibrary& lib, float deltaTime)
    {
        if (_currentState != _oldState) {
            _states[_oldState]->onExit(_currentState, lib);
            _states[_currentState]->onEnter(_oldState, lib);
            _oldState = _currentState;
        }
        _states[_currentState]->update(lib, deltaTime);
    }

    virtual void draw(arc::ILibrary& lib)
    {
        lib.display().clear();
        _states[_currentState]->draw(lib);
        lib.display().flush();
    }

    virtual uint64_t score() const
    {
        return _score;
    }

private:
    std::map<IGameState::State, std::shared_ptr<IGameState>> _states;
    IGameState::State _currentState = IGameState::State::GAME;
    IGameState::State _oldState = IGameState::State::GAME;

    uint64_t _score = 0;
    uint16_t _height = 24;
    uint16_t _width = 19;
};

extern "C" arc::IGame* entrypoint()
{
    return new Pacman;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::GAME;
}

extern "C" const char *name()
{
    return "Pacman";
}
