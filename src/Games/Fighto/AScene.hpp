/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IScene
*/

#pragma once

#include "IScene.hpp"
#include "Button.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace fighto {
    class AScene : public fighto::IScene {
        public:
            AScene(fighto::Scenes& currentScene) : _currentScene(currentScene) {}
            // static void load(arc::ILibrary& lib); need to be implemented in the child class

            virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key, bool shift) {};
            virtual void onKeyDown(arc::ILibrary& lib, arc::KeyCode key) {};
            virtual void onKeyReleased(arc::ILibrary& lib, arc::KeyCode key) {};

            virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) {};
            virtual void onMouseButtonDown(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) {};
            virtual void onMouseButtonReleased(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) {};

            virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) {};
            virtual void onJoystickButtonDown(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) {};
            virtual void onJoystickButtonReleased(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) {};

            virtual void onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, uint32_t id) {};

            virtual std::vector<std::shared_ptr<components::Button>> buttons() { return _buttons; }

        protected:
            fighto::Scenes& _currentScene;
            std::vector<std::shared_ptr<components::Button>> _buttons = {};
        private:
    };
}

#pragma GCC diagnostic pop
