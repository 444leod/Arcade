/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Fighto
*/

#include "Versus.hpp"

using fighto::scene::Versus;

void Versus::load(arc::ILibrary& lib)
{
    // init colors
    arc::Color hit = {255, 50, 50, 255};
    lib.textures().load("hit", {
        {'X', hit}, hit
    });

    // Ground
    arc::Color grey = {85, 85, 85, 255};
    lib.textures().load("ground", {{'M', grey}, grey });

    // Setup player colors
    arc::Color red = {255, 85, 85, 255};
    lib.textures().load("red", {{'X', red}, red });
    arc::Color green = {85, 255, 85, 255};
    lib.textures().load("green", {{'X', green}, green });
    arc::Color blue = {85, 85, 255, 255};
    lib.textures().load("blue", {{'X', blue}, blue });
    arc::Color yellow = {255, 255, 85, 255};
    lib.textures().load("yellow", {{'X', yellow}, yellow });
    arc::Color cyan = {85, 255, 255, 255};
    lib.textures().load("cyan", {{'X', cyan}, cyan });
    arc::Color purple = {255, 85, 255, 255};
    lib.textures().load("purple", {{'X', purple}, purple });

    arc::TextureSpecification spec;
    arc::TextureImage image;
    image.path = "assets/fighto/character1.png";
    for (uint32_t i = 0; i < 10; i++) {
        image.subrect = {i * 320, 0, 320, 320};
        spec.graphical = image;
        lib.textures().load("character1_idle_" + std::to_string(i), spec);
    }
}

void Versus::onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, std::uint32_t id)
{
    (void)lib;
    if (id > 1)
        return;
    auto champ = this->_champs.getById(id);
    if (champ == nullptr)
        return;
    champ->input(dVector(axis.x, axis.y));
}

void Versus::update(arc::ILibrary& lib, float deltaTime)
{
    //change scene to winner scene
    // if (this->_champs.count() == 1 || this->_champs.count() == 0)
    //     return;

    this->_champs.update(lib, deltaTime);

    lib.display().clear(); // Debug only
    this->_champs.debug(lib);

    HitSolver::solve(this->_champs);
}

void Versus::draw(arc::ILibrary& lib)
{
    this->_champs.draw(lib);

    auto ground = lib.textures().get("ground");
    for (uint32_t x = 0; x < lib.display().width(); x++)
        for (uint32_t y = FLOOR + 1; y < lib.display().height(); y++)
        lib.display().draw(ground, x, y);

}

void Versus::onEnter(fighto::Scenes previousScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> previousSceneObject)
{
    (void)previousScene;
    (void)lib;
    (void)previousSceneObject;
}

void Versus::onExit(fighto::Scenes nextScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> nextSceneObject)
{
    (void)nextScene;
    (void)lib;
    (void)nextSceneObject;
}
