/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include <vector>
#include <string>
#include <map>

#include "Vec2.hpp"

class SnakeObject {
    public:
        SnakeObject();

        ~SnakeObject() = default;

        float getSpeed() const {return _speed;}

        bool getAlive() const {return _alive;}

        int getScore() const {return _score;}

        std::vector<Vec2i> getPositions() const;

        Vec2i update(std::vector<Vec2i> objectsPos, float deltaTime);

        bool setDirection(std::pair<int, int> direction);

        std::vector<std::pair<Vec2i, std::string>> dump() const;

        void setSpeed(float speed) {_speed = speed;}

        void setAlive(bool alive) {_alive = alive;}

        void setScore(int score) {_score = score;}

        void setGrowToggle(bool growthToggle) {_growthToggle = growthToggle;}

        void grow(int x, int y, std::size_t size);

        void shrink(size_t size);
        
        Vec2i continueMove(void);

    private:
        Vec2i move(std::vector<Vec2i> objectsPos);

        bool checkCollision(int oldX, int oldY);

        std::pair<Vec2i, std::string> getDumpHead() const;

        std::pair<Vec2i, std::string> getDumpTail(std::size_t len) const;

        std::pair<Vec2i, std::string> getDumpBody(std::size_t i) const;

        std::vector<Vec2i> _body;
        int _score;
        float _speed;
        float _elapsed;
        bool _alive;
        bool _readyToRotate;
        bool _growthToggle;
        std::pair<int, int> _direction;
        std::pair<int, int> _oldDirection;
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
