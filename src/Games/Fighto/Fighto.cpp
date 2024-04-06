/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Fighto
*/

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
        }

        virtual void onKeyPressed(arc::ILibrary& lib, arc::Key key)
        {
            (void)lib;
            (void)key;
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
            (void)lib;
            (void)deltaTime;
        }

        virtual void draw(arc::ILibrary& lib)
        {
            lib.display().clear();
            _playerOne.draw(lib);
            _playerTwo.draw(lib);
            lib.display().flush();
        }

        virtual uint64_t score() const
        {
            return 0;
        }


    private:
        Champion _playerOne;
        Champion _playerTwo;

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
