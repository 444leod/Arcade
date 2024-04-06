/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreMenu
*/

#pragma once

#include "LibraryLoader.hpp"
#include "IGame.hpp"
#include "Score.hpp"

class CoreMenu : public arc::IGame
{
public:
    CoreMenu(const std::vector<std::shared_ptr<LibraryObject>> &libs, std::shared_ptr<LibraryObject> start);
    ~CoreMenu();

    virtual void initialize(arc::ILibrary &lib);
    virtual void onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::KeyCode key, bool shift);
    virtual void onMouseButtonPressed(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y);
    virtual void update(arc::ILibrary &lib, float deltaTime);
    virtual void draw(arc::ILibrary &lib);
    virtual uint64_t score() const { return 0; }

    std::shared_ptr<LibraryObject> game() const { return this->_games.at(this->_game); };
    std::shared_ptr<LibraryObject> lib() const { return this->_libs.at(this->_lib); };

    bool running() const { return this->_running; }
    void setRunning(bool run) { this->_running = run; }
    const std::string& player() const { return this->_player; }
    void updateScores(const std::map<std::string, arc::Score>& scores) { this->_scores = scores; }

protected:
private:
    void drawRoulette(
        arc::ILibrary &lib, const std::string& name,
        const std::vector<std::shared_ptr<LibraryObject>>& values,
        int index, int x, int y) const;
    void printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int y) const;
    void printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int x, int y, int w) const;
private:
    bool _running = false;
    bool _naming = false;
    float _nameBlink = 0;
    std::string _player = "GUEST";
    int _game = 0;
    int _lib = 0;
    std::vector<std::shared_ptr<LibraryObject>> _games = {};
    std::vector<std::shared_ptr<LibraryObject>> _libs = {};
    std::map<std::string, arc::Score> _scores = {};
};
