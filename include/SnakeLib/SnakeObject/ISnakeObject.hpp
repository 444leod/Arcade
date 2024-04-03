/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IISnakeObject
*/

#pragma once

#include "Vec2.hpp"

#include <vector>
#include <string>

class ISnakeObject {
    public:
        ~ISnakeObject() = default;

        virtual float getSpeed() const = 0;

        virtual bool getAlive() const = 0;

        virtual int getScore() const = 0;

        virtual std::vector<Vec2i> getPositions() const = 0;

        virtual Vec2i update(std::vector<Vec2i> objectsPos, float deltaTime) = 0;

        virtual bool setDirection(std::pair<int, int> direction) = 0;

        virtual std::vector<std::pair<Vec2i, std::string>> dump() const = 0;

        virtual void setSpeed(float speed) = 0;

        virtual void setAlive(bool alive) = 0;

        virtual void setScore(int score) = 0;

        virtual void setGrowToggle(bool growthToggle) = 0;

        virtual void grow(int x, int y, std::size_t size) = 0;

        virtual void shrink(size_t size) = 0;
        
        virtual Vec2i continueMove(void) = 0;
};
