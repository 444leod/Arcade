/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include <vector>
#include <string>
#include <map>

class SnakeObject {
    private:
        struct BodyPart {
            int x;
            int y;
        };

    public:
        SnakeObject();

        ~SnakeObject() = default;

        bool getAlive() const {return _alive;}

        std::pair<int, int> getHeadPos() const {return std::make_pair(_body[0].x, _body[0].y);}

        std::pair<int, int> getDirection() const {return _direction;}

        bool setDirection(std::pair<int, int> direction);

        bool move(std::pair<int, int> goalPos);

        std::vector<std::pair<SnakeObject::BodyPart, std::string>> dump() const;

    private:
        void grow(int x, int y, std::size_t size);

        bool checkCollision(int oldX, int oldY);

        std::pair<SnakeObject::BodyPart, std::string> getDumpHead() const;

        std::pair<SnakeObject::BodyPart, std::string> getDumpTail(std::size_t len) const;

        std::pair<SnakeObject::BodyPart, std::string> getDumpBody(std::size_t i) const;

        std::vector<SnakeObject::BodyPart> _body;
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
