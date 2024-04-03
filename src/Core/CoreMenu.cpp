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
            this->_libs.push_back(l);
}

CoreMenu::~CoreMenu() = default;

std::string CoreMenu::name() const
{
    return "CoreMenu";
}

void CoreMenu::initialize(arc::ILibrary &lib)
{
    lib.display().setTitle("Arcade");
    lib.display().setFramerate(60);
    lib.display().setTileSize(16);
    lib.display().setWidth(25);
    lib.display().setHeight(25);

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
        this->_selection = (this->_selection + 1) % _libs.size();
        break;
    case arc::Key::DOWN:
        this->_selection = this->_selection ? (this->_selection - 1) % _libs.size() : _libs.size() - 1;
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

    for (int i = this->_selection - 1; i <= this->_selection + 1; i++)
    {
        auto l = i < 0 ? _libs.back() : _libs.at(i % _libs.size());
        auto font = i == this->_selection ? "game" : "normal";
        auto size = lib.display().measure(l->name(), lib.fonts().get(font), 0, 0).width;
        auto x = (lib.display().width() - size) / 2;
        auto y = (this->_selection - i + 1) * 2;
        lib.display().print(l->name(), lib.fonts().get(font), x, y + 1);
    }

    for (int i = this->_selection - 1; i <= this->_selection + 1; i++)
    {
        auto l = i < 0 ? _libs.back() : _libs.at(i % _libs.size());
        auto font = i == this->_selection ? "library" : "normal";
        auto size = lib.display().measure(l->name(), lib.fonts().get(font), 0, 0).width;
        auto x = (lib.display().width() - size) / 2;
        auto y = (this->_selection - i + 1) * 2;
        lib.display().print(l->name(), lib.fonts().get(font), x, y + 10);
    }

    lib.display().flush();
}

std::shared_ptr<arc::IGame> CoreMenu::getSelection()
{
    return this->_libs.at(this->_selection)->get<arc::IGame>();
}