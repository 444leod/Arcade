/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreMenu
*/

#pragma once

#include "LibraryLoader.hpp"
#include "IGame.hpp"
#include "Score.hpp"

class CoreMenu : public arc::IGame
{
    public:
        CoreMenu() = default;
        ~CoreMenu() = default;

        virtual void initialize(arc::ILibrary &lib);
        void setGamesNames(std::array<std::string, 3> names) { this->_games = names; }
        void updateScores(const std::map<std::string, arc::Score>& scores) { this->_scores = scores; }
        void setStartTimer(uint16_t frame) { this->_enter_loader_state = frame; }

        virtual void onKeyPressed([[maybe_unused]] arc::ILibrary &lib, arc::KeyCode key, bool shift);
        virtual void onKeyDown([[maybe_unused]] arc::ILibrary &lib, arc::KeyCode key);
        virtual void onKeyReleased([[maybe_unused]] arc::ILibrary &lib, arc::KeyCode key);

        virtual void onMouseButtonPressed(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y);
        virtual void onMouseButtonDown(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y);
        virtual void onMouseButtonReleased(arc::ILibrary &lib, arc::MouseButton button, int32_t x, int32_t y);

        virtual void onJoystickButtonPressed(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id);
        virtual void onJoystickButtonDown(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id);
        virtual void onJoystickButtonReleased(arc::ILibrary& lib, arc::JoystickButton button, std::uint32_t id);
        virtual void onJoystickMove(arc::ILibrary& lib, arc::JoystickAxis axis, uint32_t id);

        virtual void update(arc::ILibrary &lib, float deltaTime);
        virtual void draw(arc::ILibrary &lib);
        virtual uint64_t score() const { return 0; }
        const std::string& player() const { return this->_player; }

    private:
        void _drawGameDecorations(arc::ILibrary& lib, int y) const;
        void _drawRoulette(arc::ILibrary &lib, int y) const;
        void _printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int y) const;
        void _printCenteredText(arc::ILibrary& lib, const std::string& string, const std::string& font, int x, int y, int w) const;

    private:
        bool _naming = false;
        float _nameBlink = 0;
        std::string _player = "GUEST";
        std::map<std::string, arc::Score> _scores = {};
        std::array<std::string, 3> _games = { };
        uint16_t _enter_loader_state = 0;
};
