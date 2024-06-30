/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Pause
*/

#pragma once

#include "../AScene.hpp"

class Pause : public AScene {
    public:
        Pause(AScene::Scene &currentState, uint64_t &score) : _currentState(currentState), _score(score) {}
        ~Pause() = default;

        virtual void initialize(arc::ILibrary& lib) override;
        virtual void onKeyPressed(arc::ILibrary& lib, arc::KeyCode key) override;
        virtual void onMouseButtonPressed(arc::ILibrary& lib, arc::MouseButton button, int32_t x, int32_t y) override;
        virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id) override;
        virtual void update(arc::ILibrary& lib, float deltaTime) override;
        virtual void draw(arc::ILibrary& lib) override;
        virtual void onEnter(AScene::Scene previousScene, arc::ILibrary& lib) override;
        virtual void onExit(AScene::Scene nextScene, arc::ILibrary& lib) override;

    protected:
    private:
        AScene::Scene& _currentState;
        uint64_t &_score;
};
