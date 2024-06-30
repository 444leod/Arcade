/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Win
*/

#pragma once

#include "../AScene.hpp"

class Win : public AScene {
    public:
        Win(AScene::Scene &currentState, uint64_t &score) : _currentState(currentState), _score(score) {}
        ~Win() = default;

        virtual void initialize(arc::ILibrary& lib) override;
        virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key);
        virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) override;

        virtual void update(arc::ILibrary& lib, float deltaTime) override;
        virtual void draw(arc::ILibrary& lib) override;
        virtual void onEnter(AScene::Scene previousScene, arc::ILibrary& lib) override;
        virtual void onExit(AScene::Scene nextScene, arc::ILibrary& lib) override;

    protected:
    private:
        AScene::Scene &_currentState;
        uint64_t &_score;
};
