#include <ncurses.h>
#include <string>

#include "../include/Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

/**
 * ゲームの名前をセットする
 * @param game_name ゲームの名前
 */
void Game::setGameName(std::string game_name)
{
    this->game_name = game_name;
}

/**
 *
 */