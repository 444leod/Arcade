/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** HitResolver
*/

#include "HitResolver.hpp"

HitResolver::HitResolver()
{
}

HitResolver::~HitResolver()
{
}

void HitResolver::add(const Hit& hit)
{
    this->_hits.push_back(hit);
}

void HitResolver::resolve(std::vector<Champion>& champions)
{
    for (const auto& h : this->_hits) {
        for (auto& c : champions) {
            if (!h.overlaps(c))
                continue;
            // damage c
        }
    }
    this->_hits.clear();
}
