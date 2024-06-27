/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Win
*/

#include "Win.hpp"

void Win::initialize([[maybe_unused]]arc::ILibrary &lib)
{}

void Win::onKeyPressed([[maybe_unused]]arc::ILibrary &lib, arc::KeyCode key)
{
    switch (key) {
        case arc::KeyCode::W:
            _currentState = AScene::Scene::GAME;
            break;
        default:
            break;
    }
}

void Win::update([[maybe_unused]]arc::ILibrary &lib, [[maybe_unused]]float deltaTime)
{
}

void Win::draw(arc::ILibrary &lib)
{
    auto font = lib.fonts().get("emulogic");

    std::vector<std::string> strings = {
        "You win!",
        "Your score was: " + std::to_string(_score),
        "Press W to continue"
    };

    for (size_t i = 0; i < strings.size(); i++) {
        auto width = lib.display().width();
        auto textWidth = lib.display().measure(strings[i], font, 0, 0).width;
        auto center = (width - textWidth) / 2;

        lib.display().print(strings[i], font, center, i + 1);
    }
}

void Win::onEnter([[maybe_unused]]AScene::Scene previousScene, [[maybe_unused]]arc::ILibrary& lib)
{
}

void Win::onExit([[maybe_unused]]AScene::Scene nextScene, [[maybe_unused]]arc::ILibrary& lib)
{
}
