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
            RandomNumberGenerator() : gen(std::random_device{}()) {
                gen.seed(std::time(nullptr));
            }

            int generate(int lower_bound = 0, int upper_bound = 100) {
                std::uniform_int_distribution<> distrib(lower_bound, upper_bound);
                return distrib(gen);
            }

        private:
            std::mt19937 gen;
        };


    static std::function<int(int, int)> rand = [] (int lower_bound = 0, int upper_bound = 100) {
        RandomNumberGenerator rng_instance;
        return rng_instance.generate(lower_bound, upper_bound);
    };
}