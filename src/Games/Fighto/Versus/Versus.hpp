/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Fighto
*/

#pragma once

#include "AScene.hpp"
#include "Scenes.hpp"
#include "Physics.hpp"
#include "ChampionManager.hpp"
#include "HitSolver.cpp"
#include <ctime>

namespace fighto::scene {
    class Versus : public fighto::AScene {
        public:
            Versus(fighto::Scenes& currentScene) : AScene(currentScene) {}
            ~Versus() = default;

            static void load(arc::ILibrary& lib);

            void onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, std::uint32_t id) override;

            void update(arc::ILibrary& lib, float deltaTime) override;

            void draw(arc::ILibrary& lib) override;

            void onEnter(fighto::Scenes previousScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> previousSceneObject) override;
            void onExit(fighto::Scenes nextScene, arc::ILibrary& lib, std::shared_ptr<fighto::IScene> nextSceneObject) override;

        private:
            ChampionManager _champs = ChampionManager(2);
    };
}
