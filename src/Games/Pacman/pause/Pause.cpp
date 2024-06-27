/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Pause
*/

#include "Pause.hpp"

void Pause::initialize([[maybe_unused]]arc::ILibrary &lib)
{}

void Pause::onKeyPressed([[maybe_unused]]arc::ILibrary &lib, arc::KeyCode key)
{
    switch (key) {
        case arc::KeyCode::P:
            _currentState = AScene::Scene::GAME;
            break;
        default:
            break;
    }
}

void Pause::onMouseButtonPressed([[maybe_unused]]arc::ILibrary &lib, [[maybe_unused]]arc::MouseButton button, [[maybe_unused]]int32_t x, [[maybe_unused]]int32_t y)
{
}

void Pause::update([[maybe_unused]]arc::ILibrary &lib, [[maybe_unused]]float deltaTime)
{
}

void Pause::draw(arc::ILibrary &lib)
{
    auto font = lib.fonts().get("emulogic");

    auto width = lib.display().width();
    auto textWidth = lib.display().measure("Pause", font, 0, 0).width;
    auto center = (width - textWidth) / 2;

    lib.display().print("Pause", font, center, 1);
}

void Pause::onEnter([[maybe_unused]]AScene::Scene previousScene, [[maybe_unused]]arc::ILibrary& lib)
{
}

void Pause::onExit([[maybe_unused]]AScene::Scene nextScene, [[maybe_unused]]arc::ILibrary& lib)
{
}
