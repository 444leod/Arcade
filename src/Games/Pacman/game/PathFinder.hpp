/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** PathFinder
*/

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <list>
#include <memory>
#include <utility>
#include <cmath>

#include "Vec2.hpp"

class Node {
    public:
        Node(Vec2i pos, std::shared_ptr<Node> parent);
        ~Node();

        Vec2i pos;
        std::shared_ptr<Node> parent;

        bool operator==(const Node &other) const;
};

class PathFinder {
    public:
        PathFinder() = delete;
        PathFinder(std::vector<std::vector<int>> map);
        ~PathFinder();

        enum class CellType {
            EMPTY,
            WALL,
            NONE,
            VISITED
        };

        enum class Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        std::map<Direction, Vec2i> directionToVec2i = {
            {Direction::UP, Vec2i(0, -1)},
            {Direction::DOWN, Vec2i(0, 1)},
            {Direction::LEFT, Vec2i(-1, 0)},
            {Direction::RIGHT, Vec2i(1, 0)}
        };

        void setCellType(Vec2i range, CellType type);
        void setCellType(int val, CellType type);
        bool pathFind(Vec2i start, Vec2i end);
        std::vector<Vec2i> getFastestPath();

    protected:
    private:
        std::vector<std::vector<int>> _map;
        std::vector<std::vector<CellType>> _cellTypes;
        std::vector<Vec2i> _fastestPath = {};

        void getNeighbours(std::shared_ptr<Node> current, std::list<std::shared_ptr<Node>> &neighbours);
        CellType getCellType(Vec2i pos);
        std::shared_ptr<Node> getNearestNeighbour(Vec2i end, std::list<std::shared_ptr<Node>> &neighbours);

};
