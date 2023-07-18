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
 * ゲームモードをセットする
 * @param game_name ゲームモード
 */
void Game::setGameName(std::string game_name)
{
    this->game_name = game_name;
}

/**
 *
 */