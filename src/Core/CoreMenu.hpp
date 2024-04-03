/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreMenu
*/

#pragma once

#include "LibraryLoader.hpp"
#include "IGame.hpp"

class CoreMenu : public arc::IGame
{
public:
    CoreMenu(const std::vector<std::shared_ptr<LibraryObject>> &libs);
    ~CoreMenu();

    virtual void initialize(arc::ILibrary &lib);
    virtual std::string name() const;
    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::Key key);
    virtual void onMouseButtonPressed(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y);
    virtual void update(arc::ILibrary &lib, float deltaTime);
    virtual void draw(arc::ILibrary &lib);
    std::shared_ptr<arc::IGame> game();
    std::shared_ptr<arc::ILibrary> lib();

protected:
private:
    int _game = 0;
    int _lib = 0;
    std::vector<std::shared_ptr<LibraryObject>> _games = {};
    std::vector<std::shared_ptr<LibraryObject>> _libs = {};
};
