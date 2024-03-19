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
            _alive = true;
            _readyToRotate = true;
            _direction = std::make_pair(1, 0);
            _body.push_back(BodyPart {(ARENA_WIDTH + 1) / 2, (ARENA_HEIGHT + 1) / 2});
            _body.push_back(BodyPart {(ARENA_WIDTH + 1) / 2 - 1, (ARENA_HEIGHT + 1) / 2});
            _body.push_back(BodyPart {(ARENA_WIDTH + 1) / 2 - 2, (ARENA_HEIGHT + 1) / 2});
            _body.push_back(BodyPart {(ARENA_WIDTH + 1) / 2 - 3, (ARENA_HEIGHT + 1) / 2});
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
            if ((_direction.first == -direction.first && _direction.second == -direction.second) ||
                (_direction.first == direction.first && _direction.second == direction.second) ||
                _alive == false ||
                _readyToRotate == false)
                return false;
            _direction = direction;
            _readyToRotate = false;
            return true;
        }

        bool move(std::pair<int, int> goalPos)
        {
            int old_x = _body[0].x;
            int old_y = _body[0].y;

            _readyToRotate = true;
            if (_body[0].x + _direction.first ==  goalPos.first && _body[0].y + _direction.second == goalPos.second) {
                grow(goalPos.first, goalPos.second);
                return true;
            }

            if (!(_direction.first == 0 && _direction.second == 0)) {
                for (std::size_t i = _body.size() - 1; i > 0; i--) {
                    _body[i].x = _body[i - 1].x;
                    _body[i].y = _body[i - 1].y;
                }
            }
            if ((_body[0].x > 1 && _direction.first < 0) ||
                (_body[0].x < ARENA_WIDTH  && _direction.first > 0))
                _body[0].x += _direction.first;

            if ((_body[0].y > 1 && _direction.second < 0) ||
                (_body[0].y < ARENA_HEIGHT  && _direction.second > 0))
                _body[0].y += _direction.second;

            if (checkCollision(old_x, old_y))
                _alive = false;
            return false;
        }

        std::vector<std::pair<BodyPart, std::string>> dump() const
        {
            std::vector<std::pair<BodyPart, std::string>> res;
            std::size_t len = _body.size();
            std::size_t i = 0;
            for (auto &part : _body) {
                if (&part == &_body[0])
                    res.push_back(getDumpHead());
                else if (&part == &_body[len - 1])
                    res.push_back(getDumpTail(len));
                else
                    res.push_back(getDumpBody(i));
                i++;
            }
            return res;
        }

        void grow(int x, int y)
        {
            _body.insert(_body.begin(), BodyPart{x, y});
        }

    private:

        bool checkCollision(int oldX, int oldY)
        {
            if (_body[0].x == oldX && _body[0].y == oldY)
                return true;
            for (std::size_t i = 1; i < _body.size(); i++) {
                if (_body[0].x == _body[i].x && _body[0].y == _body[i].y)
                    return true;
            }
            return false;
        }

        std::pair<BodyPart, std::string> getDumpHead() const
        {
            return std::make_pair(_body[0], _headTextures.at(std::make_tuple(
                _direction.first,
                _direction.second
            )));
        }

        std::pair<BodyPart, std::string> getDumpTail(std::size_t len) const
        {
            return std::make_pair(_body[len - 1], _tailTextures.at(std::make_tuple(
                    _body[len - 1].x - _body[len - 2].x,
                    _body[len - 1].y - _body[len - 2].y
            )));
        }

        std::pair<BodyPart, std::string> getDumpBody(std::size_t i) const
        {
            return std::make_pair(_body[i], _bodyTextures.at(std::make_tuple(
                _body[i].x - _body[i - 1].x,
                _body[i].x - _body[i + 1].x,
                _body[i].y - _body[i - 1].y,
                _body[i].y - _body[i + 1].y
            )));
        }

        std::vector<BodyPart> _body;
        int _speed;
        bool _alive;
        bool _readyToRotate;
        std::pair<int, int> _direction;
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
