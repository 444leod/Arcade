/*
** EPITECH PROJECT, 2024
** MyGame.cpp
** File description:
** MyGame.cpp
*/

#include "IGame.hpp"
#include "AScene.hpp"
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
        _scenes = {
            {AScene::Scene::GAME,   std::make_shared<Game>(_currentScene, _score)},
            {AScene::Scene::PAUSE,  std::make_shared<Pause>(_currentScene, _score)},
            {AScene::Scene::WIN,    std::make_shared<Win>(_currentScene, _score)},
            {AScene::Scene::LOSE,   std::make_shared<GameOver>(_currentScene, _score)}
        };
        arc::MusicSpecification musicSpec;
        #if V2
        musicSpec.path = "assets/pacman/sounds/offline.wav";
        #else
        musicSpec.path = "assets/pacman-theme.wav";
        #endif
        musicSpec.loop = true;
        musicSpec.isPlaying = true;
        musicSpec.startOffset = 0;
        lib.musics().load("main-theme", musicSpec);

        for (auto& state : _scenes) {
            state.second->initialize(lib);
        }
    }

    virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key, [[maybe_unused]]bool shift)
    {
        _scenes[_currentScene]->onKeyPressed(lib, key);
    }

    virtual void onKeyDown([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::KeyCode key)
    {
        _scenes[_currentScene]->onKeyDown(lib, key);
    }

    virtual void onKeyReleased([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::KeyCode key)
    {
        _scenes[_currentScene]->onKeyReleased(lib, key);
    }

    virtual void onMouseButtonPressed(
        arc::ILibrary& lib,
        arc::MouseButton button,
        int32_t x,
        int32_t y
    )
    {
        _scenes[_currentScene]->onMouseButtonPressed(lib, button, x, y);
    }

    virtual void onMouseButtonDown(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y
    )
    {
        _scenes[_currentScene]->onMouseButtonDown(lib, button, x, y);
    }

    virtual void onMouseButtonReleased(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y
    )
    {
        _scenes[_currentScene]->onMouseButtonReleased(lib, button, x, y);
    }

    virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id)
    {
        _scenes[_currentScene]->onJoystickButtonPressed(lib, button, id);
    }

    virtual void onJoystickButtonDown(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id)
    {
        _scenes[_currentScene]->onJoystickButtonDown(lib, button, id);
    }

    virtual void onJoystickButtonReleased(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id)
    {
        _scenes[_currentScene]->onJoystickButtonReleased(lib, button, id);
    }

    virtual void onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, uint32_t id)
    {
        _scenes[_currentScene]->onJoystickMove(lib, axis, id);
    }

    virtual void update(arc::ILibrary& lib, float deltaTime)
    {
        if (_currentScene != _previousScene) {
            _scenes[_previousScene]->onExit(_currentScene, lib);
            _scenes[_currentScene]->onEnter(_previousScene, lib);
            _previousScene = _currentScene;
        }
        _scenes[_currentScene]->update(lib, deltaTime);
    }

    virtual void draw(arc::ILibrary& lib)
    {
        lib.display().clear();
        _scenes[_currentScene]->draw(lib);
        lib.display().flush();
    }

    virtual uint64_t score() const
    {
        return _score;
    }

private:
    std::map<AScene::Scene, std::shared_ptr<AScene>> _scenes;
    AScene::Scene _currentScene = AScene::Scene::GAME;
    AScene::Scene _previousScene = AScene::Scene::GAME;

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
    #if V2
    return "Pokman";
    #endif
    return "Pacman";
}
