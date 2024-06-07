/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ChampionManager
*/

#include "ChampionManager.hpp"
#include <random>
#include <algorithm>

#include <iostream>

ChampionManager::ChampionManager(std::uint32_t count)
    : _count(count)
{
    for (std::uint32_t i = 0; i < count; i++) {
        auto index = std::rand() % this->_textures.size();
        auto color = this->_textures.at(index);
        this->_textures.erase(std::next(this->_textures.begin(), index));
        this->_champions.push_back(std::make_shared<Champion>(i, color));
    }
}

std::shared_ptr<Champion> ChampionManager::getById(std::uint32_t id)
{
    auto f = std::find_if(this->_champions.begin(), this->_champions.end(),
        [id](const auto& c){ return c->id() == id; });
    if (f == this->_champions.end())
        return nullptr;
    return *f;
}

const std::shared_ptr<Champion> ChampionManager::getById(std::uint32_t id) const
{
    auto f = std::find_if(this->_champions.begin(), this->_champions.end(),
        [id](const auto& c){ return c->id() == id; });
    if (f == this->_champions.end())
        return nullptr;
    return *f;
}

void ChampionManager::input(std::uint32_t id, arc::JoystickButton button)
{
    auto c = this->getById(id);
    if (c != nullptr)
        c->input(button);
}

void ChampionManager::update(arc::ILibrary& lib, double dt)
{
    for (auto c : this->_champions) {
        auto axis = lib.display().joystick(c->id()).axis();
        c->input(dVector(axis.x, axis.y));
        c->update(dt);
    }
}

void ChampionManager::debug(arc::ILibrary& lib) const
{
    for (auto c : this->_champions)
        c->debug(lib);
}

void ChampionManager::draw(arc::ILibrary& lib) const
{
    for (auto c : this->_champions)
        c->draw(lib);
}
