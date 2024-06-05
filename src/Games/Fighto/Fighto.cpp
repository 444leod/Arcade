/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Fighto
*/

#include "HitResolver.hpp"
#include "Champion.hpp"
#include "IGame.hpp"
#include "SharedLibraryType.hpp"

class Fighto : public arc::IGame
{
    public:
        Fighto() = default;
        ~Fighto() = default;

        virtual void initialize(arc::ILibrary& lib)
        {
            lib.display().setTitle("Fighto - Prototype");
            lib.display().setTileSize(16);
            lib.display().setHeight(16);
            lib.display().setWidth(32);
            lib.display().setFramerate(60);

            arc::Color white = {255, 255, 255, 255};
            arc::Color green = {100, 255, 100, 255};
            arc::Color red = {255, 100, 100, 255};

            lib.textures().load("player", {
                {'P', green}, green
            });
            lib.textures().load("hit", {
                {'X', red}, red
            });
            lib.fonts().load("font", {
                white, 16, "assets/regular.ttf"
            });
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

        virtual void update(arc::ILibrary& lib, float deltaTime)
        {
            arc::JoyAxis axis;
            axis = lib.display().joystick(0).axis();
            this->_champs.at(0).input(axis.x, axis.y);
            axis = lib.display().joystick(1).axis();
            this->_champs.at(1).input(axis.x, axis.y);

            this->_champs.at(0).update(deltaTime);
            this->_champs.at(1).update(deltaTime);
            this->_hits.resolve(this->_champs);
        }

        virtual void draw(arc::ILibrary& lib)
        {
            lib.display().clear();
            this->_champs.at(0).draw(lib);
            this->_champs.at(1).draw(lib);
            this->_hits.debug(lib);
            lib.display().flush();
        }

        virtual uint64_t score() const
        {
            return 0;
        }


    private:
        HitResolver _hits;
        std::vector<Champion> _champs = {
            Champion(0), Champion(1)
        };

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
