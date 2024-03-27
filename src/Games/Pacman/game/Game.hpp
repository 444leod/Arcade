/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Game
*/

#pragma once

#include "../IGameState.hpp"
#include "IEntity.hpp"
#include "ghosts/Blinky.hpp"
#include "ghosts/Pinky.hpp"
#include "ghosts/Inky.hpp"
#include "ghosts/Clyde.hpp"
// #include "RandomNumberGenerator.hpp"
#include "PathFinder.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Ghost.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>

class Game : public IGameState {
    public:
        Game(IGameState::State& currentState) : _currentState(currentState) {};
        ~Game() = default;

        virtual void initialize(arc::ILibrary& lib) override;
        virtual void onKeyPressed(arc::ILibrary& lib, arc::Key key) override;
        virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) override;
        virtual void update(arc::ILibrary& lib, float deltaTime) override;
        virtual void draw(arc::ILibrary& lib) override;
        virtual void onEnter(IGameState::State lastState) override;
        virtual void onExit(IGameState::State nextState) override;

    protected:
    private:
        IGameState::State& _currentState;

        uint64_t _ticks = 0;
        float _elapsed = 0;
        float _elapsed1 = 0;
        uint32_t _score = 0;

        float _speedMultiplier = 1.0f;

        uint64_t _hungerTick = 0;

        std::shared_ptr<PathFinder> _pathFinder;
        std::shared_ptr<pacman::Map> _map;

        std::shared_ptr<pacman::player::Player> _player = std::make_shared<pacman::player::Player>();
        Vec2i _nextPlayerPos = {0, 0};
        std::vector<std::shared_ptr<pacman::ghosts::Ghost>> _ghosts = {
            std::make_shared<pacman::ghosts::Blinky>(),
            std::make_shared<pacman::ghosts::Pinky>(),
            std::make_shared<pacman::ghosts::Inky>(),
            std::make_shared<pacman::ghosts::Clyde>()
        };

        void interactWithMap();
        void verifyCollisions();
        void updateStatuses();
};
