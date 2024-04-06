/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#pragma once

#include "SnakeLib/SnakeObject/ASnakeObject.hpp"

class Nibbler : public ASnakeObject {
    public:
        Nibbler() = default;

        Nibbler(std::vector<std::vector<int>> map);

        ~Nibbler() = default;

        Vec2i update(std::vector<Vec2i> objectsPos, float deltaTime) override;
        
        Vec2i continueMove(void) override;

        void setDirectionQueue(std::pair<int, int> direction) {_directionQueue = direction;}

        std::pair<int, int> getDirectionQueue() const {return _directionQueue;}

    protected:
    private:        
        std::pair<int, int> _directionQueue = std::make_pair(0, 0);
};
