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
    CoreMenu(const std::vector<std::shared_ptr<LibraryObject>> &libs, std::shared_ptr<LibraryObject> start);
    ~CoreMenu();

    virtual void initialize(arc::ILibrary &lib);
    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::Key key);
    virtual void onMouseButtonPressed(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y);
    virtual void update(arc::ILibrary &lib, float deltaTime);
    virtual void draw(arc::ILibrary &lib);
    virtual uint64_t score() const { return 0; }

    std::shared_ptr<LibraryObject> game() const { return this->_games.at(this->_game); };
    std::shared_ptr<LibraryObject> lib() const { return this->_libs.at(this->_lib); };

    void nextGraphicalLib();

    bool running() const { return this->_running; }
    void setRunning(bool run) { this->_running = run; }

protected:
private:
    void drawRoulette(
        arc::ILibrary &lib, const std::string& name,
        const std::vector<std::shared_ptr<LibraryObject>>& values,
        int index, int x, int y) const;
private:
    bool _running = false;
    int _game = 0;
    int _lib = 0;
    std::vector<std::shared_ptr<LibraryObject>> _games = {};
    std::vector<std::shared_ptr<LibraryObject>> _libs = {};
};
