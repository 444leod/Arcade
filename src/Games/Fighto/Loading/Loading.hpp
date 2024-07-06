/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Loading scene
*/

#pragma once

#include "Scenes.hpp"
#include "AScene.hpp"
#include <ctime>
#include <iostream>

namespace fighto::scene {
    class Loading : public fighto::AScene {
        public:
            Loading(fighto::Scenes& currentScene, bool& areSpritesLoaded) : AScene(currentScene), _areSpritesLoaded(areSpritesLoaded) {
                if (areSpritesLoaded) {
                    std::cerr << "This scene should not be re-loaded. Exiting." << std::endl;
                    std::exit(84);
                }
            }
            ~Loading() = default;

            static void load(arc::ILibrary& lib);

            void onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, std::uint32_t id) override;

            void update(arc::ILibrary& lib, float deltaTime) override;

            void draw(arc::ILibrary& lib) override;

            void onEnter(fighto::Scenes previousScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> previousSceneObject) override;
            void onExit(fighto::Scenes nextScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> nextSceneObject) override;

        private:
            float _passedTime = 0;
            uint8_t _currentLoader = 0;
            std::pair<int, int> _loadingTextPosition;
            bool& _areSpritesLoaded;
    };
}
