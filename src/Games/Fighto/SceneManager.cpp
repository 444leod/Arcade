/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SceneManager
*/

#include "IGame.hpp"
#include "Color.hpp"
#include "IScene.hpp"
#include "Scenes.hpp"
#include "Versus.hpp"
#include "Loading.hpp"
#include "Button.hpp"
#include <ctime>
#include <iostream>
#include <functional>
#include <thread>
#include <iostream>

class SceneManager : public arc::IGame {
    public:
        SceneManager() = default;
        ~SceneManager() {
            _loadThread.join();
        }

        virtual void initialize(arc::ILibrary& lib)
        {
            std::srand(std::time(nullptr));
            lib.display().setTitle("Fighto - Prototype");
            lib.display().setTileSize(32);
            lib.display().setHeight(16);
            lib.display().setWidth(32);
            lib.display().setFramerate(60);

            arc::Color white = {255, 255, 255, 255};
            lib.fonts().load("font", {
                white, 16, "assets/regular.ttf"
            });

            _sceneBuilder[fighto::Scenes::VERSUS] = [](fighto::Scenes& scene) -> std::shared_ptr<fighto::IScene> { return std::make_shared<fighto::scene::Versus>(scene); };
            _sceneBuilder[fighto::Scenes::LOADING] = [&](fighto::Scenes& scene) -> std::shared_ptr<fighto::IScene> {
                bool temp = true;
                return std::make_shared<fighto::scene::Loading>(scene, temp);
            };

            if (!_sceneBuilder.contains(_currentScene)) {
                if (!fighto::sceneToString.contains(_currentScene))
                    std::cerr << "Scene " << static_cast<int>(_currentScene) << " (string not available) isn't bound." << std::endl;
                else
                    std::cerr << "Scene " << fighto::sceneToString[_currentScene] << " isn't bound" << std::endl;

                std::exit(84);
            }
            _currentSceneObject = std::make_shared<fighto::scene::Loading>(_currentScene, _areSpritesLoaded);

            _loadThread = std::thread([&](){
                fighto::scene::Versus::load(lib);
                fighto::scene::Loading::load(lib);
                std::this_thread::sleep_for(std::chrono::seconds(10));
                _areSpritesLoaded = true;
            });
        }

        virtual void onKeyPressed([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::KeyCode key, [[maybe_unused]] bool shift)
        {
            _currentSceneObject->onKeyPressed(lib, key, shift);
        }

        virtual void onKeyDown([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::KeyCode key)
        {
            _currentSceneObject->onKeyDown(lib, key);
        }

        virtual void onKeyReleased([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::KeyCode key)
        {
            _currentSceneObject->onKeyReleased(lib, key);
        }

        virtual void onMouseButtonPressed([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::MouseButton button, [[maybe_unused]] int32_t x, [[maybe_unused]] int32_t y)
        {
            _currentSceneObject->onMouseButtonPressed(lib, button, x, y);
        }

        virtual void onMouseButtonDown([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::MouseButton button, [[maybe_unused]] int32_t x, [[maybe_unused]] int32_t y)
        {
            _currentSceneObject->onMouseButtonDown(lib, button, x, y);
        }

        virtual void onMouseButtonReleased([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::MouseButton button, [[maybe_unused]] int32_t x, [[maybe_unused]] int32_t y)
        {
            _currentSceneObject->onMouseButtonReleased(lib, button, x, y);
        }

        virtual void onJoystickButtonPressed([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickButton button, [[maybe_unused]] std::uint32_t id)
        {
            _currentSceneObject->onJoystickButtonPressed(lib, button, id);
        }

        virtual void onJoystickButtonDown([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickButton button, [[maybe_unused]] std::uint32_t id)
        {
            _currentSceneObject->onJoystickButtonDown(lib, button, id);
        }

        virtual void onJoystickButtonReleased([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickButton button, [[maybe_unused]] std::uint32_t id)
        {
            _currentSceneObject->onJoystickButtonReleased(lib, button, id);
        }

        virtual void onJoystickMove([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickAxis axis, [[maybe_unused]] std::uint32_t id)
        {
            _currentSceneObject->onJoystickMove(lib, axis, id);
        }

        virtual void update([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] float deltaTime)
        {
            if (_currentScene != _previousScene) {
                if (!_sceneBuilder.contains(_previousScene)) {
                    std::cerr << "Scene not implemented yet (" << fighto::sceneToString[_previousScene] << ")" << std::endl;
                    std::exit(84);
                }
                if (!_sceneBuilder.contains(_currentScene)) {
                    std::cerr << "Scene not implemented yet (" << fighto::sceneToString[_currentScene] << ")" << std::endl;
                    std::exit(84);
                }
                auto nextScene = _sceneBuilder[_currentScene](_currentScene);
                _currentSceneObject->onExit(_currentScene, lib, nextScene);
                nextScene->onEnter(_previousScene, lib, _currentSceneObject);
                _currentSceneObject = nextScene;
                _previousScene = _currentScene;
            }
            auto mousePos = lib.display().mousePosition();
            for (auto& button : _currentSceneObject->buttons()) {
                auto bounds = button->bounds();
                if (mousePos.first >= bounds.x && mousePos.first <= bounds.x + bounds.width &&
                    mousePos.second >= bounds.y && mousePos.second <= bounds.y + bounds.height) {
                    button->state() == components::Button::State::NORMAL ? button->setState(components::Button::State::HOVER) : button->setState(components::Button::State::NORMAL);
                } else {
                    button->state() == components::Button::State::HOVER ? button->setState(components::Button::State::NORMAL) : button->setState(components::Button::State::HOVER);
                }
            }
            _currentSceneObject->update(lib, deltaTime);
        }

        virtual void draw([[maybe_unused]] arc::ILibrary& lib)
        {
            // lib.display().clear();
            _currentSceneObject->draw(lib);
            auto buttons = _currentSceneObject->buttons();
            for (auto& button : buttons) {
                button->draw(lib);
            }
            lib.display().flush();
        }

        virtual uint64_t score() const
        {
            return 0;
        }

    protected:
    private:
        uint64_t _score = 0;
        fighto::Scenes _previousScene = fighto::Scenes::LOADING;
        fighto::Scenes _currentScene = fighto::Scenes::LOADING;
        std::shared_ptr<fighto::IScene> _currentSceneObject = nullptr;
        std::map<fighto::Scenes, std::function<std::shared_ptr<fighto::IScene>(fighto::Scenes&)>> _sceneBuilder = {};
        std::thread _loadThread;
        bool _areSpritesLoaded = false;
};


extern "C" arc::IGame* entrypoint()
{
    return new SceneManager;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::GAME;
}

extern "C" const char *name()
{
    return "Fighto";
}
