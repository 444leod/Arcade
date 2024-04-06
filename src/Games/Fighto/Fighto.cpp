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

            arc::Color color = {255, 100, 100, 255};
            lib.textures().load("player", {
                {'#', color}, color
            });
        }

        virtual void onKeyPressed(arc::ILibrary& lib, arc::Key key)
        {
            (void)lib;

            if (key == arc::Key::Q)     _playerOne.input(-1.f, false);
            if (key == arc::Key::D)     _playerOne.input(+1.f, false);
            if (key == arc::Key::Z)     _playerOne.input( 0.f, true);

            if (key == arc::Key::LEFT)  _playerTwo.input(-1.f, false);
            if (key == arc::Key::RIGHT) _playerTwo.input(+1.f, false);
            if (key == arc::Key::UP)    _playerTwo.input( 0.f, true);
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
            _playerOne.update(deltaTime);
            _playerTwo.update(deltaTime);
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
