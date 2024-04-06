/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Score
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

namespace arc
{
    struct Score {
        std::string game;
        std::string player;
        uint64_t hs;
    };

    inline std::ofstream& operator<<(std::ofstream& stream, const Score& score)
    {
        stream << score.game << ":";
        stream << score.player << ":";
        stream << std::to_string(score.hs) << std::endl;
        return stream;
    }

    inline std::ifstream& operator>>(std::ifstream& stream, Score& score)
    {
        std::string g, p, s;

        std::getline(stream, g, ':');
        std::getline(stream, p, ':');
        std::getline(stream, s);
        if (g.empty() || p.empty() || s.empty())
            return stream;
        score.game = g;
        score.player = p;
        score.hs = std::atoi(s.c_str());
        return stream;
    }

    inline void operator>>(std::string& string, Score& score)
    {
        std::string g, p, s;
        std::stringstream ss(string);

        std::getline(ss, g, ':');
        std::getline(ss, p, ':');
        std::getline(ss, s);
        if (g.empty() || p.empty() || s.empty())
            return;
        score.game = g;
        score.player = p;
        score.hs = std::atoi(s.c_str());
    }
};
