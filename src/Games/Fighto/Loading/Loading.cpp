/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Loading scene
*/

#include "Loading.hpp"
#include <iostream>

using fighto::scene::Loading;

void Loading::load(arc::ILibrary& lib)
{
    arc::TextureSpecification spec;
    arc::TextureImage image;
    image.path = "assets/menu/loader.png";
    image.subrect = {0, 0, 16, 16};

    spec.textual.character = 'O';

    for (uint8_t i = 0; i < 9; i++) {
        spec.graphical = arc::TextureImage{"assets/menu/loader.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 16), 0, 16, 16}};
        lib.textures().load("loader_" + std::to_string(i), spec);
    }
}

void Loading::onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, std::uint32_t id)
{
    (void)lib;
    (void)axis;
    (void)id;
}

void Loading::update([[maybe_unused]] arc::ILibrary& lib, float deltaTime)
{
    if (_areSpritesLoaded) {
        std::cout << "going to versus!" << std::endl;
        //temporarily set to VERSUS
        _currentScene = fighto::Scenes::VERSUS;
        return;
    }
    _passedTime += deltaTime;
    while (_passedTime > 0.2f) {
        _currentLoader++;
        if (_currentLoader == 9)
            _currentLoader = 0;
        _passedTime -= 0.2f;
    }
}

void Loading::draw(arc::ILibrary& lib)
{
    lib.display().clear();
    auto font = lib.fonts().get("normal");
    auto textSize = lib.display().measure("Loading...", font, lib.display().width(), lib.display().height()).width;
    float center = lib.display().width() / 2 - textSize / 2;
    lib.display().print("Loading...", font, center, lib.display().height() / 2 + 3);

    lib.display().draw(lib.textures().get("loader_" + std::to_string(_currentLoader)), lib.display().width() / 2 - 1, lib.display().height() / 2 - 1);
}

void Loading::onEnter(fighto::Scenes previousScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> previousSceneObject)
{
    (void)previousScene;
    (void)lib;
    (void)previousSceneObject;
}

void Loading::onExit(fighto::Scenes nextScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> nextSceneObject)
{
    (void)nextScene;
    (void)lib;
    (void)nextSceneObject;
}
