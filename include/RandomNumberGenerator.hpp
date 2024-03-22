/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** RandomNumberGenerator
*/

#pragma once

#include <random>
#include <ctime>

class RandomNumberGenerator {
public:
    RandomNumberGenerator() : gen(std::random_device{}()), distrib(0, 99) {
        gen.seed(std::time(nullptr));
    }

    int generate() {
        return distrib(gen);
    }

private:
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib;
};
