/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Fighto
*/

#include "ChampionManager.hpp"
#include "IGame.hpp"
#include "SharedLibraryType.hpp"
#include "HitSolver.cpp"
#include <ctime>

class Fighto : public arc::IGame
{
    public:
        Fighto() = default;
        ~Fighto() = default;

        virtual void initialize(arc::ILibrary& lib)
        {
            std::srand(std::time(nullptr));
            lib.display().setTitle("Fighto - Prototype");
            lib.display().setTileSize(32);
            lib.display().setHeight(16);
            lib.display().setWidth(32);
            lib.display().setFramerate(60);

            // Setup text and hit color
            arc::Color white = {255, 255, 255, 255};
            arc::Color hit = {255, 50, 50, 255};
            lib.textures().load("hit", {
                {'X', hit}, hit
            });
            lib.fonts().load("font", {
                white, 16, "assets/regular.ttf"
            });

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
        }

        virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key, bool shift)
        {
            (void)lib;
            (void)key;
            (void)shift;
        }

        virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y)
        {
            (void)lib;
            (void)button;
            (void)x;
            (void)y;
        }

        virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id)
        {
            (void)lib;
            this->_champs.input(id, button);
        }

        virtual void update(arc::ILibrary& lib, float deltaTime)
        {
            this->_champs.update(lib, deltaTime);

            lib.display().clear(); // Debug only
            this->_champs.debug(lib);

            HitSolver::solve(this->_champs);
        }

        virtual void draw(arc::ILibrary& lib)
        {
            //lib.display().clear();
            this->_champs.draw(lib);
            lib.display().flush();
        }

        virtual uint64_t score() const
        {
            return 0;
        }

    private:
        ChampionManager _champs = ChampionManager(2);

};

extern "C" arc::IGame* entrypoint()
{
    return new Fighto;
}

extern "C" arc::SharedLibraryType type()
{
    return arc::SharedLibraryType::GAME;
}

extern "C" const char *name()
{
    return "Fighto";
}
