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
    lib.display().setFramerate(60);
    lib.display().setTileSize(24);
    lib.display().setWidth(24);
    lib.display().setHeight(24);


    arc::FontSpecification normal = {{200, 200, 200, 200}, 16, "assets/regular.ttf"};
    lib.fonts().load("normal", normal);

    arc::FontSpecification name = {{100, 100, 255, 255}, 16, "assets/regular.ttf"};
    lib.fonts().load("name", name);

    arc::FontSpecification game = {{255, 100, 100, 255}, 16, "assets/regular.ttf"};
    lib.fonts().load("game", game);

    arc::FontSpecification library = {{100, 255, 100, 255}, 16, "assets/regular.ttf"};
    lib.fonts().load("library", library);

    this->_running = true;
}

void CoreMenu::onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::Key key)
{
    if (key >= arc::Key::A && key <= arc::Key::Z && this->_player.size() < 5) {
        auto c = 'A' + static_cast<char>(key) - static_cast<char>(arc::Key::A);
        this->_player += c;
    }

    switch (key)
    {
    case arc::Key::UP:
        this->_game = (this->_game + 1) % _games.size();
        break;
    case arc::Key::DOWN:
        this->_game = this->_game ? (this->_game - 1) % _games.size() : _games.size() - 1;
        break;
    case arc::Key::LEFT:
        this->_lib = (this->_lib + 1) % _libs.size();
        break;
    case arc::Key::RIGHT:
        this->_lib = this->_lib ? (this->_lib - 1) % _libs.size() : _libs.size() - 1;
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

void CoreMenu::update(arc::ILibrary &lib, float deltaTime)
{
    (void)lib;
    (void)deltaTime;
}

void CoreMenu::draw(arc::ILibrary &lib)
{
    lib.display().clear();

    this->printCenteredText(lib, "Player's name:", "normal", 1);
    this->printCenteredText(lib, this->_player, "name", 2);

    std::string hs = "High-Score: ";
    if (this->_scores.contains(this->game()->name())) {
        arc::Score score = this->_scores.at(this->game()->name());
        hs = hs + score.player + " - " + std::to_string(score.hs);
    } else
        hs += "NONE";
    this->printCenteredText(lib, hs, "normal", 4);

    this->drawRoulette(lib, "game", this->_games, this->_game, 0, 12);
    this->drawRoulette(lib, "library", this->_libs, this->_lib, 12, 12);

    lib.display().flush();
}

void CoreMenu::printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int y) const
{
    auto width = lib.display().measure(string, lib.fonts().get(font), 0, 0).width;
    auto x = (lib.display().width() - width) / 2;
    lib.display().print(string, lib.fonts().get(font), x, y);
}

void CoreMenu::drawRoulette(
    arc::ILibrary &lib, const std::string& font,
    const std::vector<std::shared_ptr<LibraryObject>>& values,
    int index, int x, int y
) const
{
    for (int i = index - 1; i <= index + 1; i++)
    {
        auto l = i < 0 ? values.back() : values.at(i % values.size());
        auto _font = i == index ? font : std::string("normal");
        auto size = lib.display().measure(l->name(), lib.fonts().get(_font), 0, 0).width;
        auto _x = (lib.display().width() / 2 - size) / 2;
        auto _y = (index - i + 1) * 2;
        lib.display().print(l->name(), lib.fonts().get(_font), x + _x, y + _y);
    }
}
