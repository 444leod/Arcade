/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** GameOver
*/

#include "GameOver.hpp"

void GameOver::initialize([[maybe_unused]]arc::ILibrary &lib)
{}

void GameOver::onKeyPressed([[maybe_unused]]arc::ILibrary &lib, [[maybe_unused]] arc::KeyCode key)
{
    _currentState = AScene::Scene::GAME;
}

void GameOver::onJoystickButtonPressed([[maybe_unused]]arc::ILibrary &lib, [[maybe_unused]]arc::JoystickButton button, [[maybe_unused]]std::uint32_t id)
{
    if (id != 0)
        return;
    _currentState = AScene::Scene::GAME;
}

void GameOver::onMouseButtonPressed([[maybe_unused]]arc::ILibrary &lib, [[maybe_unused]]arc::MouseButton button, [[maybe_unused]]int32_t x, [[maybe_unused]]int32_t y)
{
}

void GameOver::update([[maybe_unused]]arc::ILibrary &lib, [[maybe_unused]]float deltaTime)
{
}

void GameOver::draw(arc::ILibrary &lib)
{
    auto font = lib.fonts().get("emulogic");

    std::vector<std::string> strings = {
        "Game Over!",
        "Your score was: " + std::to_string(_score),
        "Press any to retry"
    };

    for (size_t i = 0; i < strings.size(); i++) {
        auto width = lib.display().width();
        auto textWidth = lib.display().measure(strings[i], font, 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(strings[i], font, center, i + 1);
    }
}

void GameOver::onEnter([[maybe_unused]]AScene::Scene previousScene, [[maybe_unused]] arc::ILibrary& lib)
{
}

void GameOver::onExit([[maybe_unused]]AScene::Scene nextScene, [[maybe_unused]] arc::ILibrary& lib)
{
}
