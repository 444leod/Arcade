/*
** EPITECH PROJECT, 2024
** JAM2
** File description:
** Map
*/

#include "Map.hpp"
#include <functional>

static void addCellsToCluster(std::vector<Vec2i>& cluster, Vec2i pos, std::vector<std::vector<int>>& map)
{
    std::vector<Vec2i> directions = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0},
    };
    for (auto &dir : directions) {
        Vec2i newPos = pos + dir;
        if (newPos.x < 0 || (uint32_t)newPos.x >= map[0].size() || newPos.y < 0 || (uint32_t)newPos.y >= map.size())
            continue;
        if (map[newPos.y][newPos.x] == 0) {
            cluster.push_back(newPos);
            map[newPos.y][newPos.x] = 2;
            addCellsToCluster(cluster, newPos, map);
        }
    }
}

static std::vector<std::vector<Vec2i>> getClustersFromMap(std::vector<std::vector<int>>& map)
{
    std::vector<std::vector<Vec2i>> clusters;
    std::vector<Vec2i> directions = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0},
    };
    for (uint32_t i = 0; i < map.size(); i++) {
        for (uint32_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) {
                map[i][j] = 2;
                std::vector<Vec2i> cluster;
                cluster.push_back(Vec2i(j, i));
                addCellsToCluster(cluster, Vec2i(j, i), map);
                clusters.push_back(cluster);
            }
        }
    }
    return clusters;
}

Map::Map(Vec2i position, Vec2i size, arc::ITextureManager& texs,
    std::vector<std::shared_ptr<pacman::IEntity>>& ghosts) :
    _position(position), _size(size)
{
    std::vector<Vec2i> dirs = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };
    std::vector<int> line(size.x, 0);
    this->_tiles = std::vector(size.y, line);

    std::vector<Vec2i> paths = {};

    for (uint16_t i = 0; i < 10000; ++i) {
        std::vector<std::vector<Vec2i>> clusters;
        clusters = getClustersFromMap(this->_tiles);
        //reset the map
        for (auto &line : clusters) {
            for (auto &pos : line) {
                if (this->_tiles[pos.y][pos.x] == 2)
                    this->_tiles[pos.y][pos.x] = 0;
            }
        }
        //remove clusters with less than 3 cells
        std::vector<std::vector<Vec2i>> goodClusters;
        for (auto &line : clusters)
            if (line.size() > 3)
                goodClusters.push_back(line);
        if (goodClusters.size() == 0)
            break;
        clusters = goodClusters;

        PathFinder pathFinder(this->_tiles);
        pathFinder.setCellType(0, PathFinder::CellType::EMPTY);
        pathFinder.setCellType(1, PathFinder::CellType::WALL);

        Vec2i firstPos = Vec2i(-1, -1);
        Vec2i secondPos = Vec2i(-1, -1);

        uint16_t clusterIndex = (std::rand() % clusters.size());

        int firstPosIndex = std::rand() % clusters[clusterIndex].size();
        firstPos = clusters[clusterIndex][firstPosIndex];

        int secondPosIndex;
        do {
            secondPosIndex = std::rand() % clusters[clusterIndex].size();
        } while (secondPosIndex == firstPosIndex || std::abs(secondPosIndex - firstPosIndex) > 6);
        secondPos = clusters[clusterIndex][secondPosIndex];

        bool isPathFound = pathFinder.pathFind(firstPos, secondPos);
        if (!isPathFound) {
            continue;
        }
        if (isPathFound) {
            auto path = pathFinder.getFastestPath();
            for (auto &pos : path) {
                paths.push_back(pos);
                this->_tiles[pos.y][pos.x] = 1;
            }
            for (auto &pos : path) {
                for (auto &dir : dirs) {
                    Vec2i newPos = pos + dir;
                    if (newPos.x < 0 || newPos.x > size.x || newPos.y < 0 || newPos.y > size.y - 1)
                        continue;
                    this->_tiles[newPos.y][newPos.x] = 1;
                }
            }
        }
    }

    for (auto &line : this->_tiles) {
        for (auto &cell : line) {
            cell = 0;
        }
    }
    for (auto &pos : paths) {
        this->_tiles[pos.y][pos.x] = 1;
    }
    for (auto &line : this->_tiles) {
        for (auto &cell : line) {
            if (std::rand() % 100 < 50)
                cell = 2;
        }
    }


    // GHOOOOSSTTTTSSS
    std::vector<Vec2i> freePos = {};
    std::vector<std::function<std::shared_ptr<pacman::IEntity>()>> ghostFactories = {
        []() { return std::make_shared<pacman::ghosts::Blinky>(); },
        []() { return std::make_shared<pacman::ghosts::Pinky>(); },
        []() { return std::make_shared<pacman::ghosts::Inky>(); },
        []() { return std::make_shared<pacman::ghosts::Clyde>(); }
    };

    for (int y = 0; y < size.y; y++)
        for (int x = 0; x < size.x; x++)
            if (this->_tiles[y][x] == 0)
                freePos.push_back({x, y});
    for (int i = 0; i < 10; i++) {
        Vec2i pos = freePos[std::rand() % (freePos.size() - 1)];
        pos += this->_position * 21;
        ghosts.push_back(ghostFactories[i % ghostFactories.size()]());
        ghosts.back()->setPos(pos);
        ghosts.back()->setPosf(pos);
        ghosts.back()->initTextures(texs);
    }
}

Map::~Map()
{
}

std::vector<std::pair<Vec2i, std::string>> Map::dump() const
{
    const char *texs[] = {
        "empty",
        "wall",
        "coin"
    };
    std::vector<std::pair<Vec2i, std::string>> res;
    for (uint16_t y = 0; y < this->_tiles.size(); ++y) {
        for (uint16_t x = 0; x < this->_tiles[y].size(); ++x) {
            Vec2i pos = Vec2i(
                x + (this->_position.x * this->_size.x),
                y + (this->_position.y * this->_size.y));
            res.push_back({pos, texs[this->_tiles[y][x]]});
        }
    }
    return res;
}

Vec2i Map::getCenterSafePos() const
{
    Vec2i center = this->_size / 2;

    for (int y = center.y - 1; y <= center.y + 1; y++) {
        for (int x = center.x - 1; x <= center.x + 1; x++) {
            if (_tiles[y][x] == 0)
                return Vec2i(x, y);
        }
    }
    // Will never fail.
    return Vec2i(-1, -1);
}

void Map::setTile(Vec2i pos, int value)
{
    _tiles[pos.y][pos.x] = value;
}

int Map::tileAtAbsPos(Vec2i pos) const
{
    int x = (std::abs(this->_position.x * this->_size.x) + pos.x) % 21;
    int y = (std::abs(this->_position.y * this->_size.y) + pos.y) % 21;
    return this->_tiles[y][x];
}

void Map::setAtAbsPos(Vec2i pos, int value)
{
    int x = (std::abs(this->_position.x * this->_size.x) + pos.x) % 21;
    int y = (std::abs(this->_position.y * this->_size.y) + pos.y) % 21;
    _tiles[y][x] = value;
}
