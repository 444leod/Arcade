/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include <vector>
#include <string>
#include <map>

#include "SnakeGame.hpp"

struct BodyPart {
    int x;
    int y;
};

class Snake {
    public:
        Snake()
        {
            _size = 1;
            _alive = true;
            _direction = std::make_pair(0, 0);
            _body.push_back(BodyPart {ARENA_WIDTH / 2, ARENA_HEIGHT / 2});
        }

        ~Snake() = default;

        bool getAlive() const
        {
            return _alive;
        }

        std::pair<int, int> getHeadPos() const
        {
            return std::make_pair(_body[0].x, _body[0].y);
        }

        std::pair<int, int> getDirection() const
        {
            return _direction;
        }

        bool setDirection(std::pair<int, int> direction)
        {
            if ((_direction.first == -direction.first && _direction.second == -direction.second)
                || (_direction.first == direction.first && _direction.second == direction.second))
                return false;
            _direction = direction;
            return true;
        }

        void move()
        {
            if ((_body[0].x > 0 && _direction.first < 0) ||
                (_body[0].x < ARENA_WIDTH - 1 && _direction.first > 0))
                _body[0].x += _direction.first;

            if ((_body[0].y > 0 && _direction.second < 0) ||
                (_body[0].y < ARENA_HEIGHT - 1 && _direction.second > 0))
                _body[0].y += _direction.second;
        }


        std::vector<std::pair<BodyPart, std::string>> dump() const
        {
            std::vector<std::pair<BodyPart, std::string>> res;
            for (auto &part : _body) {
                if (&part == &_body[0])
                    res.push_back(getDumpHead());
                else
                    res.push_back(std::make_pair(part, "body_0_north"));
            }
            return res;
        }

    private:
        std::pair<BodyPart, std::string> getDumpHead() const
        {
            return std::make_pair(_body[0], _headTextures.at(std::make_tuple(_direction.first, _direction.second)));
        }
        std::vector<BodyPart> _body;
        int _size;
        int _speed;
        bool _alive;
        std::pair<int, int> _direction;
        std::map<std::tuple<int, int>, std::string> _headTextures = {
            {{0, -1}, "head_0_south"},
            {{0, 1}, "head_0_north"},
            {{-1, 0}, "head_0_east"},
            {{1, 0}, "head_0_west"},
            {{0, 0}, "head_0_east"}
        };
};
