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
 * @param game_mode ゲームモード
*/
void Game::setGameMode(std::string game_mode)
{
  this->game_mode = game_mode;
}

/**
 * 
*/