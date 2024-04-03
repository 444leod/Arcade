/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ASnakeObject
*/

#pragma once

#include "Vec2.hpp"
#include "ISnakeObject.hpp"
#include "SnakeLib/SnakeObject/SnakeConstants.hpp"

#include <vector>
#include <string>
#include <map>

class ASnakeObject {
    public:
        ASnakeObject();

        ~ASnakeObject() = default;

        virtual float getSpeed() const {return _speed;}

        virtual bool getAlive() const {return _alive;}

        virtual int getScore() const {return _score;}

        virtual std::vector<Vec2i> getPositions() const;

        virtual Vec2i update(std::vector<Vec2i> objectsPos, float deltaTime);

        virtual bool setDirection(std::pair<int, int> direction);

        virtual std::vector<std::pair<Vec2i, std::string>> dump() const;

        virtual void setSpeed(float speed) {_speed = speed;}

        virtual void setAlive(bool alive) {_alive = alive;}

        virtual void setScore(int score) {_score = score;}

        virtual void setGrowToggle(bool growthToggle) {_growthToggle = growthToggle;}

        virtual void grow(int x, int y, std::size_t size);

        virtual void shrink(size_t size);
        
        virtual Vec2i continueMove(void);

    protected:
        Vec2i move(std::vector<Vec2i> objectsPos);

        bool checkCollision(int oldX, int oldY);

        std::pair<Vec2i, std::string> getDumpHead() const;

        std::pair<Vec2i, std::string> getDumpTail(std::size_t len) const;

        std::pair<Vec2i, std::string> getDumpBody(std::size_t i) const;

        std::vector<Vec2i> _body;
        int _score = 0;
        float _speed = BASE_SPEED;
        float _elapsed = 0;
        bool _alive = true;
        bool _readyToRotate = true;
        bool _growthToggle = true;
        std::pair<int, int> _direction = std::make_pair(1, 0);
        std::pair<int, int> _oldDirection = std::make_pair(1, 0);
        std::map<std::tuple<int, int>, std::string> _headTextures = {
            {{0, -1}, "head_0_south"},
            {{0, 1}, "head_0_north"},
            {{-1, 0}, "head_0_east"},
            {{1, 0}, "head_0_west"},
            {{0, 0}, "empty"}
        };
        std::map<std::tuple<int, int>, std::string> _tailTextures = {
            {{0, -1}, "tail_south"},
            {{0, 1}, "tail_north"},
            {{-1, 0}, "tail_east"},
            {{1, 0}, "tail_west"},
            {{0, 0}, "empty"}
        };
        std::map<std::tuple<int, int, int, int>, std::string> _bodyTextures = {
            {{1, -1, 0, 0}, "body_horizontal"},
            {{-1, 1, 0, 0}, "body_horizontal"},
            {{-1, -1, 0, 0}, "body_horizontal"},
            {{1, 0, 0, 0}, "body_horizontal"},
            {{0, -1, 0, 0}, "body_horizontal"},
            {{-1, 0, 0, 0}, "body_horizontal"},
            {{0, 1, 0, 0}, "body_horizontal"},
            {{0, 0, 1, -1}, "body_vertical"},
            {{0, 0, -1, 1}, "body_vertical"},
            {{0, 0, -1, -1}, "body_vertical"},
            {{0, 0, 1, 0}, "body_vertical"},
            {{0, 0, 0, -1}, "body_vertical"},
            {{0, 0, -1, 0}, "body_vertical"},
            {{0, 0, 0, 1}, "body_vertical"},
            {{0, 1, -1, 0}, "body_south_west"},
            {{1, 0, 0, -1}, "body_south_west"},
            {{-1, 0, 0, 1}, "body_north_east"},
            {{0, -1, 1, 0}, "body_north_east"},
            {{0, 1, 1, 0}, "body_north_west"},
            {{1, 0, 0, 1}, "body_north_west"},
            {{-1, 0, 0, -1}, "body_south_east"},
            {{0, -1, -1, 0}, "body_south_east"},
            {{0, 0, 0, 0}, "empty"},
        };
};
