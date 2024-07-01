/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreMenu
*/

#include "CoreMenu.hpp"

void CoreMenu::initialize(arc::ILibrary &lib)
{
    lib.display().setTitle("Arcade");
    lib.display().setFramerate(30);
    lib.display().setTileSize(32);
    #ifdef ARCADE
    lib.display().setWidth(20);
    lib.display().setHeight(20);
    #else
    lib.display().setWidth(30);
    lib.display().setHeight(30);
    #endif

    std::string font = "assets/pacman/emulogic.ttf";
    arc::FontSpecification normal = {{200, 200, 200, 200}, 32, font};
    lib.fonts().load("normal", normal);
    arc::FontSpecification name = {{100, 100, 255, 255}, 32, font};
    lib.fonts().load("name", name);
    arc::FontSpecification hs = {{255, 200, 100, 255}, 32, font};
    lib.fonts().load("hs", hs);
    arc::FontSpecification game = {{255, 100, 100, 255}, 32, font};
    lib.fonts().load("game", game);
    arc::FontSpecification small = {{200, 200, 200, 200}, 16, font};
    lib.fonts().load("small", small);

    //buttons
    std::map<std::string, arc::Rect<uint32_t>> buttons = {
        {"CROSS", {32, 48, 16, 16}},
        {"SQUARE", {32, 64, 16, 16}},
        {"TRIANGLE", {32, 80, 16, 16}},
        {"CIRCLE", {32, 96, 16, 16}},
        {"L1", {48, 0, 16, 16}},
        {"L2", {48, 16, 16, 16}},
        {"R1", {48, 32, 16, 16}},
        {"R2", {48, 48, 16, 16}},
    };
    arc::TextureSpecification spec;

    arc::TextureImage tex_btn;
    tex_btn.path = "assets/menu/buttons.png";
    for (auto& [name, rect] : buttons) {
        tex_btn.subrect = rect;
        spec.graphical = tex_btn;
        lib.textures().load(name, spec);
    }

    std::map<std::string, arc::Rect<uint32_t>> loader_states = {
        {"0", {0, 0, 16, 16}},
        {"1", {16, 0, 16, 16}},
        {"2", {32, 0, 16, 16}},
        {"3", {48, 0, 16, 16}},
        {"4", {64, 0, 16, 16}},
        {"5", {80, 0, 16, 16}},
        {"6", {96, 0, 16, 16}},
        {"7", {112, 0, 16, 16}},
        {"8", {128, 0, 16, 16}},
    };
    arc::TextureImage tex_loader;
    tex_loader.path = "assets/menu/loader.png";
    for (auto& [name, rect] : loader_states) {
        tex_loader.subrect = rect;
        spec.graphical = tex_loader;
        lib.textures().load(name, spec);
    }

    arc::TextureImage tex_select;
    tex_select.path = "assets/menu/selector.png";
    tex_select.subrect = { 0, 0, 16, 16 };
    spec.graphical = tex_select;
    lib.textures().load("selector", spec);
}

void CoreMenu::onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::KeyCode key, [[maybe_unused]]bool shift)
{
    if (key == arc::KeyCode::TAB)
        this->_naming = !this->_naming;

    if (this->_naming) {
        if (key == arc::KeyCode::DELETE)
            this->_player = this->_player.substr(0, this->_player.size() - 1);
        else if (key >= arc::KeyCode::A && key <= arc::KeyCode::Z && this->_player.size() < 10) {
            auto c = 'A' + static_cast<char>(key) - static_cast<char>(arc::KeyCode::A);
            this->_player += c;
        }
    }
}

void CoreMenu::onKeyDown([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::KeyCode key)
{
}

void CoreMenu::onKeyReleased([[maybe_unused]] arc::ILibrary &lib, [[maybe_unused]] arc::KeyCode key)
{
}

void CoreMenu::onMouseButtonPressed(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y)
{
    (void)lib;
    (void)button;
    (void)x;
    (void)y;
}

void CoreMenu::onMouseButtonDown(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y)
{
    (void)lib;
    (void)button;
    (void)x;
    (void)y;
}

void CoreMenu::onMouseButtonReleased(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y)
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

void CoreMenu::onJoystickButtonDown(
    [[maybe_unused]] arc::ILibrary& lib,
    [[maybe_unused]] arc::JoystickButton button,
    [[maybe_unused]] std::uint32_t id)
{
}

void CoreMenu::onJoystickButtonReleased(
    [[maybe_unused]] arc::ILibrary& lib,
    [[maybe_unused]] arc::JoystickButton button,
    [[maybe_unused]] std::uint32_t id)
{
}

void CoreMenu::onJoystickMove(
    [[maybe_unused]] arc::ILibrary& lib,
    [[maybe_unused]] arc::JoystickAxis axis,
    [[maybe_unused]] uint32_t id)
{
}

void CoreMenu::update([[maybe_unused]] arc::ILibrary &lib, float deltaTime)
{
    if (this->_naming)
        this->_nameBlink = (this->_nameBlink > 0.f) ? this->_nameBlink - deltaTime : 0.9f;
}

void CoreMenu::draw(arc::ILibrary &lib)
{
    lib.display().clear();
    #ifdef ARCADE
    this->_printCenteredText(lib, "Player's name:", "normal", 1);
    if (this->_nameBlink > 0.4f || !this->_naming)
        this->_printCenteredText(lib, this->_player, "name", 2);

    this->_printCenteredText(lib, "Highest Score", "normal", 4);
    std::string hs = "";
    /*if (this->_scores.contains(this->game()->name())) {
        arc::Score score = this->_scores.at(this->game()->name());
        hs = hs + score.player + ": " + std::to_string(score.hs);
    } else
        hs += "NONE";*/
    this->_printCenteredText(lib, hs, "hs", 5);

    auto y = lib.display().height() / 2;
    this->drawRoulette(lib, "game", this->_games, this->_game, y);

    #else
    this->_printCenteredText(lib, "Player's name:", "normal", 6);
    if (this->_nameBlink > 0.4f || !this->_naming)
        this->_printCenteredText(lib, this->_player, "name", 7);

    this->_printCenteredText(lib, "Highest Score", "normal", 9);
    std::string hs = "";
    if (this->_scores.contains(this->_games.at(1))) {
        arc::Score score = this->_scores.at(this->_games.at(1));
        hs = hs + score.player + ": " + std::to_string(score.hs);
    } else
        hs += "NONE";
    this->_printCenteredText(lib, hs, "hs", 10);

    auto y = lib.display().height() / 2;
    this->_drawRoulette(lib, y);

    auto bottom = lib.display().height() - 2;
    lib.display().draw(lib.textures().get("R1"), 0, bottom - 1.4f);
    lib.display().print("HOLD to start", lib.fonts().get("small"), 1.2f, bottom - 1);
    lib.display().draw(lib.textures().get("R2"), 0, bottom - 0.4f);
    lib.display().print("HOLD to exit", lib.fonts().get("small"), 1.2f, bottom);
    #endif
    lib.display().flush();
}

void CoreMenu::_printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int y) const
{
    this->_printCenteredText(lib, string, font, 0, y, lib.display().width());
}

void CoreMenu::_printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int x, int y, int w) const
{
    auto width = lib.display().measure(string, lib.fonts().get(font), 0, 0).width;
    auto _x = (w - width) / 2;
    lib.display().print(string, lib.fonts().get(font), _x + x, y);
}

void CoreMenu::_drawRoulette(arc::ILibrary &lib, int y) const
{
    for (int8_t i = 0; i < 3; i++)
    {
        auto name = this->_games[i];
        std::string font = i == 1 ? "game" : "normal";
        int8_t offset = i * 2 - 1;
        this->_printCenteredText(lib, name, font, y + offset);
        if (i == 1)
            this->_drawGameDecorations(lib,  y + offset);
    }
}

void CoreMenu::_drawGameDecorations(arc::ILibrary& lib, int y) const
{
    std::shared_ptr<arc::ITexture> tex = nullptr;
    auto w = lib.display().measure(this->_games[1], lib.fonts().get("game"), 0, 0).width;
    auto start = (lib.display().width() - w) / 2;
    auto end = (lib.display().width() + w) / 2;

    tex = lib.textures().get("selector");
    lib.display().draw(tex, start - 2, y);

    tex = lib.textures().get(std::to_string(this->_enter_loader_state));
    lib.display().draw(tex, end + 1, y);
}
