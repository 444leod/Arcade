/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IScene
*/

#pragma once

#include "Scenes.hpp"
#include "ILibrary.hpp"
#include "Button.hpp"
#include <vector>
#include <memory>

namespace fighto {
    class IScene {
        public:
            virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key, bool shift) = 0;
            virtual void onKeyDown(arc::ILibrary& lib, arc::KeyCode key) = 0;
            virtual void onKeyReleased(arc::ILibrary& lib, arc::KeyCode key) = 0;

            virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) = 0;
            virtual void onMouseButtonDown(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) = 0;
            virtual void onMouseButtonReleased(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) = 0;

            virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) = 0;
            virtual void onJoystickButtonDown(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) = 0;
            virtual void onJoystickButtonReleased(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) = 0;

            virtual void onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, uint32_t id) = 0;

            virtual void update(arc::ILibrary& lib, float deltaTime) = 0;

            virtual void draw(arc::ILibrary& lib) = 0;

            virtual void onEnter(fighto::Scenes previousScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> previousSceneObject) = 0;
            virtual void onExit(fighto::Scenes nextScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> nextSceneObject) = 0;

            virtual std::vector<std::shared_ptr<components::Button>> buttons() = 0;
    };
}

