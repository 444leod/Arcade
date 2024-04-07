/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** HitResolver
*/

#pragma once

#include <vector>
#include "Hit.hpp"

class Champion;
class Hit;

class HitResolver {
    public:
        HitResolver();
        ~HitResolver();

        void add(const Hit& hit);
        void resolve(std::vector<Champion>& champions);

    protected:
    private:
        std::vector<Hit> _hits = {};
};
