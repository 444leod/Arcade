/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** AScene
*/

#pragma once

#include "IGame.hpp"

class AScene {
    public:
        AScene() = default;
        ~AScene() =  default;

        static enum class Scene {
            GAME,
            PAUSE,
            WIN,
            LOSE,
        } _state;

        virtual void initialize(arc::ILibrary& lib) = 0;

        virtual void onKeyPressed([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::KeyCode key) {}
        virtual void onKeyDown([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::KeyCode key) {}
        virtual void onKeyReleased([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::KeyCode key) {}

        virtual void onMouseButtonPressed([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::MouseButton button, [[maybe_unused]] int32_t x, [[maybe_unused]] int32_t y) {}
        virtual void onMouseButtonDown([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::MouseButton button, [[maybe_unused]] int32_t x, [[maybe_unused]] int32_t y) {}
        virtual void onMouseButtonReleased([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::MouseButton button, [[maybe_unused]] int32_t x, [[maybe_unused]] int32_t y) {}

        virtual void onJoystickButtonPressed([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickButton button, [[maybe_unused]] std::uint32_t id) {}
        virtual void onJoystickButtonDown([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickButton button, [[maybe_unused]] std::uint32_t id) {}
        virtual void onJoystickButtonReleased([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickButton button, [[maybe_unused]] std::uint32_t id) {}

        virtual void onJoystickMove([[maybe_unused]] arc::ILibrary& lib, [[maybe_unused]] arc::JoystickAxis axis, [[maybe_unused]] std::uint32_t id) {}

        virtual void update(arc::ILibrary& lib, float deltaTime) = 0;
        virtual void draw(arc::ILibrary& lib) = 0;
        virtual void onEnter(AScene::Scene previousScene, arc::ILibrary& lib) = 0;
        virtual void onExit(AScene::Scene nextScene, arc::ILibrary& lib) = 0;

    protected:
    private:
};
