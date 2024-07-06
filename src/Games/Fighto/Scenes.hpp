/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Scenes
*/

#pragma once

#include <map>
#include <string>

namespace fighto {
    enum class Scenes {
        LOADING,
        MENU,
        SETTINGS,
        CREDITS,
        QUIT,
        GAME_SELECT,
        CHAMP_SELECT,
        RULES,
        VERSUS,
        PAUSE,
        WIN,
        TIE,
        STATS
    };

    inline static std::map<Scenes, std::string> sceneToString = {
        {Scenes::LOADING, "Loading"},
        {Scenes::MENU, "Menu"},
        {Scenes::SETTINGS, "Settings"},
        {Scenes::CREDITS, "Credits"},
        {Scenes::QUIT, "Quit"},
        {Scenes::GAME_SELECT, "Game Select"},
        {Scenes::CHAMP_SELECT, "Champion Select"},
        {Scenes::RULES, "Rules"},
        {Scenes::VERSUS, "Versus"},
        {Scenes::PAUSE, "Pause"},
        {Scenes::WIN, "Win"},
        {Scenes::TIE, "Tie"},
        {Scenes::STATS, "Stats"}
    };
}

