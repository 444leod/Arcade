/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** RandomNumberGenerator
*/

#pragma once

#include <random>
#include <ctime>
#include <functional>

namespace rng {
    class RandomNumberGenerator {
    public:
        RandomNumberGenerator() : gen(std::random_device{}()), distrib(0, 1000) {
            gen.seed(std::time(nullptr));
        }

        int generate() {
            return distrib(gen);
        }

        int generate(int lower_bound, int upper_bound) {
            std::uniform_int_distribution<> distrib(lower_bound, upper_bound);
            return distrib(gen);
        }

    private:
        std::mt19937 gen;
        std::uniform_int_distribution<> distrib;
    };

        std::function<int(int, int)> rand = [] (int lower_bound = 0, int upper_bound = 100) {
            rng::RandomNumberGenerator rng_instance;
            return rng_instance.generate(lower_bound, upper_bound);
        };
}

