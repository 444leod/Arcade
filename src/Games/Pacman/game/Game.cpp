/*
** EPITECH PROJECT, 2024
** Arcade-Cleaned
** File description:
** Game
*/

#include "Game.hpp"

void Game::initialize(arc::ILibrary &lib)
{
    onEnter(IGameState::State::GAME);
    _map->initTextures(lib.textures());
    // Fonts
    arc::FontSpecification text {
        .color = arc::Color {200, 200, 200, 255},
        .size = 16,
        .path = "assets/pacman/emulogic.ttf"
    };
    lib.fonts().load("emulogic", text);

    _player->initTextures(lib.textures());
    for (auto& ghost : _ghosts) {
        ghost->initTextures(lib.textures());
    }

    arc::TextureSpecification spec;
    spec.textual.character = 'G';
    spec.textual.color = {0, 0, 0, 255};
    for (int i = 0; i < 4; i++) {
        std::stringstream ss;
        ss << "deadghost_" << i;
        spec.graphical = arc::TextureImage{"assets/pacman/entity-tileset.png", arc::Rect<uint32_t>{static_cast<uint32_t>(i * 20), 200, 20, 20}};
        lib.textures().load(ss.str(), spec);
    }
    std::vector<std::vector<int>> mapp = _map->getMap();
    _pathFinder = std::make_shared<PathFinder>(_map->getMap());
    _pathFinder->setCellType(Vec2i(0, 2), PathFinder::CellType::EMPTY);
    _pathFinder->setCellType(0, PathFinder::CellType::WALL);
    _pathFinder->setCellType(1, PathFinder::CellType::EMPTY);
    _pathFinder->setCellType(2, PathFinder::CellType::EMPTY);
    _pathFinder->setCellType(3, PathFinder::CellType::EMPTY);
    _pathFinder->setCellType(4, PathFinder::CellType::WALL);
    _pathFinder->setCellType(5, PathFinder::CellType::WALL);
    _pathFinder->setCellType(6, PathFinder::CellType::WALL);
}

void Game::onKeyPressed([[maybe_unused]] arc::ILibrary& lib, arc::Key key)
{
    switch (key) {
        case arc::Key::Z:
            _player->queueMove({0, -1});
            break;
        case arc::Key::Q:
            _player->queueMove({-1, 0});
            break;
        case arc::Key::S:
            _player->queueMove({0, 1});
            break;
        case arc::Key::D:
            _player->queueMove({1, 0});
            break;
        case arc::Key::ESCAPE:
            _currentState = IGameState::State::PAUSE;
            break;
        default: break;
    }
}

void Game::onMouseButtonPressed(
    [[maybe_unused]] arc::ILibrary& lib,
    [[maybe_unused]] arc::MouseButton button,
    [[maybe_unused]] int32_t x,
    [[maybe_unused]] int32_t y
)
{
}

void Game::update([[maybe_unused]] arc::ILibrary& lib, float deltaTime)
{
    _elapsed += deltaTime;
    _elapsed1 += deltaTime;
    Vec2i playerPos = _player->getPos();

    _player->move(deltaTime, _map);
    for (auto& ghost : _ghosts) {
        ghost->move(deltaTime, _map);
    }
    if (_elapsed1 >= 0.2) {
        for (auto& ghost : _ghosts) {
            if (ghost->getStatus() != pacman::entity::status::DEAD) {
                pacman::Direction direction = pacman::Direction(std::rand() % 4);
                ghost->setMoveQueue({pacman::DirectionToVec2[direction]});
            }
        }
        _elapsed1 -= 0.2;
    }
    if (_elapsed >= 0.1) {
        _ticks++;
        _elapsed -= 0.1;
    }

    _player->movef(deltaTime);

    for (auto& ghost : _ghosts) {
        ghost->movef(deltaTime);
    }

    interactWithMap();
    verifyCollisions();
    updateStatuses();

    if (_player->getStatus() == pacman::entity::status::DEAD) {
        _currentState = IGameState::State::LOSE;
    }
}

void Game::draw(arc::ILibrary& lib)
{
    for (auto [pos, texture] : _map->getTextures()) {
        if (texture == "fruit" && _ticks % 2)
            continue;
        lib.display().draw(lib.textures().get(texture), pos.x, pos.y);
    }

    std::vector<std::shared_ptr<pacman::IEntity>> entities;
    entities.push_back(_player);
    for (auto& ghost : _ghosts) {
        entities.push_back(ghost);
    }

    for (auto& entity : entities) {
        std::string texture = entity->getTexture(_ticks);
        if (texture.length() == 0)
            continue;
        if (entity->getStatus() == pacman::entity::status::SCARED && _ticks - _hungerTick >= 75 && _ticks % 2 == 0) {
            texture += "_";
        }
        lib.display().draw(lib.textures().get(texture), entity->getPosf().x, entity->getPosf().y);
    }

    std::stringstream score;
    score << "Score: " << _score;
    auto width = lib.display().width();
    auto textWidth = lib.display().measure(score.str(), lib.fonts().get("emulogic"), 0, 0).width;
    auto center = (width - textWidth) / 2;
    lib.display().print(score.str(), lib.fonts().get("emulogic"), center, _map->getMapSizeY() + 1);

    if (_player->getStatus() == pacman::entity::status::DEAD) {
        _currentState = IGameState::State::LOSE;
    } else if (_map->getCoinCount() == 0 && _map->getFruitCount() == 0) {
        _currentState = IGameState::State::WIN;
    }
}

void Game::onEnter(IGameState::State lastState)
{
    if (lastState == IGameState::State::PAUSE)
        return;
    _map = std::make_shared<pacman::Map>("assets/pacman/map.csv");
    _player->setSpeed(_speedMultiplier);
    _player->setPos(_map->getPlayerPos());
    _player->setPosf(_map->getPlayerPos());
    auto ghostSpawnPoints = _map->getGhostSpawnPoints();
    for (auto &ghost : _ghosts) {
        Vec2i ghostPos = ghostSpawnPoints[std::rand() % ghostSpawnPoints.size()];
        ghost->setPosf(ghostPos);
        ghost->setPos(ghostPos);
        ghost->setStatus(pacman::entity::status::ALIVE);
        ghost->setSpeed(_speedMultiplier);
        ghost->updateWalkableTiles(pacman::TileType::DOOR, false);
        std::cout << "Ghost pos: " << ghostPos.x << ", " << ghostPos.y << std::endl;
    }
    _player->setStatus(pacman::entity::status::ALIVE);
    _player->setDirection(pacman::Direction::NONE);
    _player->setMoveQueue({});
    _ticks = 0;
    _score = 0;
    _hungerTick = 0;
    _elapsed = 0;
    _elapsed1 = 0;
}

void Game::onExit([[maybe_unused]]IGameState::State nextState)
{
}

void Game::interactWithMap()
{
    Vec2i playerPos = _player->getPos();
    pacman::TileType playerTile = _map->getCellType(playerPos);
    if (playerTile == pacman::TileType::COIN) {
        _score += 10;
        _map->setCellType(playerPos, pacman::TileType::EMPTY);
    } else if (playerTile == pacman::TileType::FRUIT) {
        _score += 100;
        _map->setCellType(playerPos, pacman::TileType::EMPTY);
        _player->setStatus(pacman::entity::status::HUNGRY);
        _hungerTick = _ticks;
        for (auto& ghost : _ghosts) {
            if (ghost->getStatus() == pacman::entity::status::ALIVE) {
                ghost->setStatus(pacman::entity::status::SCARED);
                ghost->setSpeed(_speedMultiplier * 0.7);
            }
        }
    }
}

void Game::verifyCollisions()
{
    Vec2f pacmanPos = _player->getPosf();
    float tolerance = 0.4f;

    for (auto& ghost : _ghosts) {
        Vec2f ghostPos = ghost->getPosf();
        if (std::abs(pacmanPos.x - ghostPos.x) <= tolerance && std::abs(pacmanPos.y - ghostPos.y) <= tolerance) {
            if (ghost->getStatus() == pacman::entity::status::SCARED) {
                ghost->setStatus(pacman::entity::status::DEAD);
                _score += 200;
                ghost->setSpeed(_speedMultiplier);
            } else if (ghost->getStatus() == pacman::entity::status::ALIVE) {
                _player->setStatus(pacman::entity::status::DEAD);
            }
        }
    }
}

void Game::updateStatuses()
{
    if (_player->getDirection() == Vec2i{0, 0} && _ticks == 1) {
        _ticks = 0;
        return;
    }
    if (_ticks == 100)
        for (auto& ghost : _ghosts)
            ghost->updateWalkableTiles(pacman::TileType::DOOR, true);


    for (auto &ghost : _ghosts) {
        if (ghost->getStatus() == pacman::entity::status::DEAD) {
            ghost->updateWalkableTiles(pacman::TileType::DOOR, true);
            continue;
        }
        bool toggle = false;
        for (auto ghostPos : _map->getGhostSpawnPoints()) {
            if (ghost->getPos() == ghostPos) {
                toggle = true;
                break;
            }
        }
        if (!toggle && ghost->getPos() != _map->getDoorPos()) {
            ghost->updateWalkableTiles(pacman::TileType::DOOR, false);
        }
    }
    if (_player->getStatus() == pacman::entity::status::HUNGRY && _ticks - _hungerTick >= 100) {
        _player->setStatus(pacman::entity::status::ALIVE);
        for (auto& ghost : _ghosts) {
            ghost->setStatus(pacman::entity::status::ALIVE);
            ghost->setSpeed(_speedMultiplier);
        }
    }
    for (auto &ghost : _ghosts) {
        if (ghost->getStatus() == pacman::entity::status::DEAD) {
            if (ghost->getPos() == _map->getDoorPos()) {
                ghost->setStatus(pacman::entity::status::ALIVE);
                continue;
            }
            _pathFinder->setCellType(6, PathFinder::CellType::EMPTY);
            if (_pathFinder->pathFind(ghost->getPos(), _map->getDoorPos())) {
                auto fastestPath = _pathFinder->getFastestPath();
                uint16_t i = 0;
                ghost->setMoveQueue({});
                for (auto pos : fastestPath) {
                    if (i < fastestPath.size() - 1)
                        ghost->queueMove(pos - fastestPath[i + 1]);
                    i++;
                }
            }
        }
    }
    _pathFinder->setCellType(6, PathFinder::CellType::WALL);
}
