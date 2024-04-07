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

            arc::Color color = {255, 100, 100, 255};
            lib.textures().load("player", {
                {'#', color}, color
            });
        }

        virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key, [[maybe_unused]] bool shift)
        {
            (void)lib;

            if (key == arc::KeyCode::Q)     this->_champs.at(0).input(-1.f, false);
            if (key == arc::KeyCode::D)     this->_champs.at(0).input(+1.f, false);
            if (key == arc::KeyCode::Z)     this->_champs.at(0).input( 0.f, true);

            if (key == arc::KeyCode::LEFT)  this->_champs.at(1).input(-1.f, false);
            if (key == arc::KeyCode::RIGHT) this->_champs.at(1).input(+1.f, false);
            if (key == arc::KeyCode::UP)    this->_champs.at(1).input( 0.f, true);
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
            this->_champs.at(0).update(deltaTime);
            this->_champs.at(1).update(deltaTime);
        }

        virtual void draw(arc::ILibrary& lib)
        {
            lib.display().clear();
            this->_champs.at(0).draw(lib);
            this->_champs.at(1).draw(lib);
            lib.display().flush();
        }

        virtual uint64_t score() const
        {
            return 0;
        }


    private:
        HitResolver _hits;
        std::vector<Champion> _champs = {
            Champion(), Champion()
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
