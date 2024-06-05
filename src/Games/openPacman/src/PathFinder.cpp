/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** PathFinder
*/

#include "PathFinder.hpp"

Node::Node(Vec2i pos, std::shared_ptr<Node> parent)
{
    this->pos = pos;
    this->parent = parent;
}

Node::~Node()
{
}

bool Node::operator==(const Node &other) const
{
    return this->pos == other.pos;
}

PathFinder::PathFinder(std::vector<std::vector<int>> map)
{
    _map = map;
    _cellTypes.reserve(map.size());
    for (auto &line : map) {
        std::vector<CellType> cellTypeLine;
        cellTypeLine.reserve(line.size());
        for (uint16_t i = 0; i < line.size(); i++) {
            cellTypeLine.push_back(CellType::NONE);
        }
        _cellTypes.push_back(cellTypeLine);
    }
}

PathFinder::~PathFinder()
{
}

void PathFinder::setCellType(Vec2i cell, CellType type)
{
    for (uint16_t i = 0; i < _map.size(); i++) {
        for (uint16_t j = 0; j < _map[i].size(); j++) {
            int x = cell.x;
            int y = cell.y;

            for (uint16_t it = x; it != y; it += (x < y) ? 1 : -1) {
                if (_map[i][j] == it) {
                    _cellTypes[i][j] = type;
                }
            }
        }
    }
}

void PathFinder::setCellType(int value, CellType type)
{
    for (uint16_t i = 0; i < _map.size(); i++) {
        for (uint16_t j = 0; j < _map[i].size(); j++) {
            if (_map[i][j] == value) {
                _cellTypes[i][j] = type;
            }
        }
    }
}

bool PathFinder::pathFind(Vec2i start, Vec2i end)
{
    for (uint16_t i = 0; i < _map.size(); i++) {
        for (uint16_t j = 0; j < _map[i].size(); j++) {
            if (_cellTypes[i][j] == CellType::NONE) {
                // std::cout << "map is not ok" << std::endl;
                // std::cout << "cell [" << i << "][" << j << "] is not set" << std::endl;
                // std::cout << "its base value is: " << _map[i][j] << std::endl;
                return false;
            }
        }
    }

    std::vector<Vec2i> path;
    std::list<Node> possibleMoves = {};
    Node currentPos(start, nullptr);

    _fastestPath.clear();
    this->getNeighbours(currentPos, possibleMoves);
    int iterations = 0;
    while (currentPos.pos != end && !possibleMoves.empty() && iterations < 1000) {
        currentPos = this->getNearestNeighbour(end, possibleMoves);
        this->getNeighbours(currentPos, possibleMoves);
        iterations++;
    }
    if (currentPos.pos != end || iterations >= 1000)
        return false;
    while (currentPos.parent != nullptr) {
        path.push_back(currentPos.pos);
        currentPos = *currentPos.parent;
    }
    path.push_back(currentPos.pos);
    _fastestPath = path;
    return true;
}

void PathFinder::getNeighbours(Node pos, std::list<Node> &neighbours)
{
    neighbours.clear();
    std::vector<Direction> directionsVec = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    for (auto dir : directionsVec) {
        Vec2i newPos = pos.pos + directionToVec2i.at(dir);
        if (getCellType(newPos) != CellType::WALL)
            neighbours.push_back(Node(newPos, std::make_shared<Node>(pos)));
    }
}

PathFinder::CellType PathFinder::getCellType(Vec2i pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.y >= static_cast<int>(_cellTypes.size()) || pos.x >= static_cast<int>(_cellTypes[pos.y].size()))
        return CellType::WALL;
    return _cellTypes[pos.y][pos.x];
}

Node PathFinder::getNearestNeighbour(Vec2i end, std::list<Node> &neighbours)
{
    Node nearestNeighbour(Vec2i(0, 0), nullptr);
    float nearestDistance = 1000000;
    int iterations = 0;
    for (auto &neighbour : neighbours) {
        if (iterations >= 1000)
            break;
        iterations++;
        float distance = std::sqrt(std::pow(neighbour.pos.x - end.x, 2) + std::pow(neighbour.pos.y - end.y, 2));
        if (distance < nearestDistance) {
            nearestDistance = distance;
            nearestNeighbour = neighbour;
        }
    }
    neighbours.remove(nearestNeighbour);
    return nearestNeighbour;
}

std::vector<Vec2i> PathFinder::getFastestPath()
{
    return _fastestPath;
}
