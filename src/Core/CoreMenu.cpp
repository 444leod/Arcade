/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreMenu
*/

#include "CoreMenu.hpp"

CoreMenu::CoreMenu(const std::vector<std::shared_ptr<LibraryObject>> &libs, std::shared_ptr<LibraryObject> start)
{
    for (auto l : libs)
        if (l->type() == arc::SharedLibraryType::GAME)
            this->_games.push_back(l);
        else if (l->type() == arc::SharedLibraryType::LIBRARY)
            this->_libs.push_back(l);

    for (auto l : this->_libs) {
        if (l == start) break;
        this->_lib++;
    }
}

CoreMenu::~CoreMenu() = default;

void CoreMenu::initialize(arc::ILibrary &lib)
{
    lib.display().setTitle("Arcade");
    lib.display().setFramerate(30);
    lib.display().setTileSize(32);
    lib.display().setWidth(20);
    lib.display().setHeight(20);

    std::string font = "assets/pacman/emulogic.ttf";
    arc::FontSpecification normal = {{200, 200, 200, 200}, 32, font};
    lib.fonts().load("normal", normal);
    arc::FontSpecification name = {{100, 100, 255, 255}, 32, font};
    lib.fonts().load("name", name);
    arc::FontSpecification hs = {{255, 200, 100, 255}, 32, font};
    lib.fonts().load("hs", hs);
    arc::FontSpecification game = {{255, 100, 100, 255}, 32, font};
    lib.fonts().load("game", game);

    this->_running = true;
}

void CoreMenu::onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::KeyCode key, [[maybe_unused]]bool shift)
{
    if (key == arc::KeyCode::TAB)
        this->_naming = !this->_naming;

    if (this->_naming && this->_running) {
        if (key == arc::KeyCode::DELETE)
            this->_player = this->_player.substr(0, this->_player.size() - 1);
        else if (key >= arc::KeyCode::A && key <= arc::KeyCode::Z && this->_player.size() < 10) {
            auto c = 'A' + static_cast<char>(key) - static_cast<char>(arc::KeyCode::A);
            this->_player += c;
        }
    }

    if (this->_naming)
        return;
    switch (key)
    {
    case arc::KeyCode::I:
        this->_game = (this->_game + 1) % _games.size();
        break;
    case arc::KeyCode::K:
        this->_game = this->_game ? (this->_game - 1) % _games.size() : _games.size() - 1;
        break;
    default:
        break;
    }
}

void CoreMenu::onMouseButtonPressed(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y)
{
    (void)lib;
    (void)button;
    (void)x;
    (void)y;
}

void CoreMenu::onJoystickButtonPressed(
    [[maybe_unused]] arc::ILibrary& lib,
    [[maybe_unused]] arc::JoystickButton button,
    [[maybe_unused]] std::uint32_t id)
{
}

void CoreMenu::update(arc::ILibrary &lib, float deltaTime)
{
    (void)lib;
    if (this->_naming)
        this->_nameBlink = (this->_nameBlink > 0.f) ? this->_nameBlink - deltaTime : 0.9f;
}

void CoreMenu::draw(arc::ILibrary &lib)
{
    lib.display().clear();

    this->printCenteredText(lib, "Player's name:", "normal", 1);
    if (this->_nameBlink > 0.4f || !this->_naming)
        this->printCenteredText(lib, this->_player, "name", 2);

    this->printCenteredText(lib, "Highest Score", "normal", 4);
    std::string hs = "";
    if (this->_scores.contains(this->game()->name())) {
        arc::Score score = this->_scores.at(this->game()->name());
        hs = hs + score.player + ": " + std::to_string(score.hs);
    } else
        hs += "NONE";
    this->printCenteredText(lib, hs, "hs", 5);

    auto y = lib.display().height() / 2;
    this->drawRoulette(lib, "game", this->_games, this->_game, y);

    lib.display().flush();
}

void CoreMenu::printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int y) const
{
    this->printCenteredText(lib, string, font, 0, y, lib.display().width());
}

void CoreMenu::printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int x, int y, int w) const
{
    auto width = lib.display().measure(string, lib.fonts().get(font), 0, 0).width;
    auto _x = (w - width) / 2;
    lib.display().print(string, lib.fonts().get(font), _x + x, y);
}

void CoreMenu::drawRoulette(
    arc::ILibrary &lib, const std::string& font,
    const std::vector<std::shared_ptr<LibraryObject>>& values,
    int index, int y
) const
{
    for (int i = index - 1; i <= index + 1; i++)
    {
        auto l = i < 0 ? values.back() : values.at(i % values.size());
        auto _font = i == index ? font : std::string("normal");
        auto _y = (index - i + 1) * 2;
        this->printCenteredText(lib, l->name(), _font, y + _y);
    }
}
