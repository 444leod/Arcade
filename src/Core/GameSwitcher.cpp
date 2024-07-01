/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** GameSwitcher
*/

#include "GameSwitcher.hpp"


GameSwitcher::~GameSwitcher()
{
    this->_saveScores();
}

void GameSwitcher::init(const LibraryLoader& loader, arc::ILibrary& lib) noexcept
{
    this->_games = loader.get(arc::SharedLibraryType::GAME);
    this->_menu = std::make_shared<CoreMenu>();
    this->_current = this->_menu;
    this->_current->initialize(lib);
    this->_menu->setGamesNames(this->_names());
    this->_loadScores();
}

void GameSwitcher::update(arc::ILibrary& lib, double dt) noexcept
{
    this->_start_timer = this->_pressing_start ? this->_start_timer + dt : .0;
    this->_exit_timer = this->_pressing_exit ? this->_exit_timer + dt : .0;

    if (this->_start_timer > 0.8)   this->_start(lib);
    if (this->_exit_timer > 1.4)    this->_exit(lib);
    auto start_progress = this->_start_timer / 0.7;
    this->_menu->setStartTimer(start_progress * 8);
}

void GameSwitcher::next() noexcept
{
    if (this->_current != this->_menu)
        return;
    this->_selector_index = (this->_selector_index + 1) % this->_games.size();
    this->_menu->setGamesNames(this->_names());
}

void GameSwitcher::previous() noexcept
{
    if (this->_current != this->_menu)
        return;
    if (this->_selector_index == 0)
        this->_selector_index = this->_games.size() - 1;
    else
        this->_selector_index--;
    this->_menu->setGamesNames(this->_names());
}

void GameSwitcher::_start(arc::ILibrary& lib) noexcept
{
    this->_start_timer = 0.0;
    auto so = this->_games[this->_selector_index];
    this->_current = so->get<arc::IGame>();
    this->_current->initialize(lib);
}

void GameSwitcher::_exit(arc::ILibrary& lib) noexcept
{
    this->_exit_timer = 0.0;
    for (const auto& musics : lib.musics().dump())
        lib.musics().stop(musics.first);
    for (const auto& sound : lib.sounds().dump())
        lib.sounds().stop(sound.first);

    if (this->_current == this->_menu) {
        lib.display().close();
    } else {
        this->_saveScores();
        this->_current = this->_menu;
        this->_current->initialize(lib);
    }
}

std::array<std::string, 3> GameSwitcher::_names() const noexcept
{
    uint32_t prev = (this->_selector_index == 0 ? this->_games.size() : this->_selector_index) - 1;
    uint32_t next = (this->_selector_index + 1) % this->_games.size();

    return {
        this->_games[prev]->name(),
        this->_games[this->_selector_index]->name(),
        this->_games[next]->name(),
    };
}

void GameSwitcher::_loadScores() noexcept
{
    this->_menu->updateScores(this->_scores);

    std::ifstream rstream(".scores");
    if (!rstream.is_open())
        return;

    std::string tmp = "";
    while (std::getline(rstream, tmp)) {
        if (tmp.empty()) break;
        arc::Score score;
        tmp >> score;
        this->_scores[score.game] = score;
    }
    rstream.close();
}

void GameSwitcher::_saveScores() noexcept
{
    std::shared_ptr<LibraryObject> game = this->_games[this->_selector_index];
    if (!this->_scores.contains(game->name()) || this->_scores[game->name()].hs < this->_current->score())
        this->_scores[game->name()] = { game->name(), this->_menu->player(), this->_current->score() };
    this->_menu->updateScores(this->_scores);

    std::ofstream stream(".scores");
    if (!stream.is_open())
        return;
    for (auto entry : this->_scores)
        stream << entry.second;
    stream.close();
}
