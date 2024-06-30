/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ChampionManager
*/

#pragma once

#include <vector>
#include "Champion.hpp"

class ChampionManager {
    public:
        ChampionManager(std::uint32_t count);
        ~ChampionManager() = default;

        std::uint32_t count() const { return this->_count; }
        std::vector<std::shared_ptr<Champion>>& champions() { return this->_champions; }
        const std::vector<std::shared_ptr<Champion>>& champions() const { return this->_champions; }

        std::shared_ptr<Champion> getById(std::uint32_t id);
        const std::shared_ptr<Champion> getById(std::uint32_t id) const;

        void input(std::uint32_t id, arc::JoystickButton button);
        void update(arc::ILibrary& lib, double dt);
        void debug(arc::ILibrary& lib) const;
        void draw(arc::ILibrary& lib) const;

    protected:
    private:
        std::uint32_t _count = 0;
        std::vector<std::shared_ptr<Champion>> _champions = {};
        std::vector<std::string> _textures = {
            "red",
            "green",
            "blue",
            "yellow",
            "cyan",
            "purple"
        };
};
