/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreMenu
*/

#include "CoreMenu.hpp"

CoreMenu::CoreMenu(const std::vector<std::shared_ptr<LibraryObject>> &libs)
{
    for (auto l : libs)
        if (l->type() == arc::SharedLibraryType::GAME)
            this->_games.push_back(l);
        else if (l->type() == arc::SharedLibraryType::LIBRARY)
            this->_libs.push_back(l);
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

    arc::FontSpecification game = {{255, 100, 100, 255}, 16, "assets/regular.ttf"};
    lib.fonts().load("game", game);

    arc::FontSpecification library = {{100, 255, 100, 255}, 16, "assets/regular.ttf"};
    lib.fonts().load("library", library);
}

void CoreMenu::onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::Key key)
{
    switch (key)
    {
    case arc::Key::UP:
        this->_game = (this->_game + 1) % _games.size();
        break;
    case arc::Key::DOWN:
        this->_game = this->_game ? (this->_game - 1) % _games.size() : _games.size() - 1;
        break;
    case arc::Key::SPACE:
        this->_lib = (this->_lib + 1) % _libs.size();
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

    drawRoulette(lib, "game", this->_games, this->_game, 0, 12);
    drawRoulette(lib, "library", this->_libs, this->_lib, 12, 12);

    lib.display().flush();
}

std::shared_ptr<arc::IGame> CoreMenu::game()
{
    return this->_games.at(this->_game)->get<arc::IGame>();
}

std::shared_ptr<arc::ILibrary> CoreMenu::lib()
{
    return this->_libs.at(this->_lib)->get<arc::ILibrary>();
}

void CoreMenu::drawRoulette(
    arc::ILibrary &lib, const std::string& font,
    const std::vector<std::shared_ptr<LibraryObject>>& values,
    int index, int x, int y)
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
