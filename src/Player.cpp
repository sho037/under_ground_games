#include <string>
#include "../include/Player.hpp"
Player::Player()
{
    this->player_name = "Player";
    this->player_score = 0;
}

Player::~Player()
{
}

/**
 * プレイヤー名を設定する
 */
void Player::setPlayerName(std::string player_name)
{
    this->player_name = player_name;
}

/**
 * プレイヤーのスコアを設定する
 */
void Player::setPlayerScore(int player_score)
{
    this->player_score = player_score;
}

/**
 * プレイヤーのタイムを設定する
 */
void Player::setPlayerTime(double player_time)
{
    this->player_time = player_time;
}


/**
 * プレイヤー名を取得する
 */
std::string Player::getPlayerName()
{
    return this->player_name;
}

/**
 * プレイヤーのスコアを取得する
 */
int Player::getPlayerScore()
{
    return this->player_score;
}

/**
 * プレイヤーのタイムを取得する
 */
double Player::getPlayerTime()
{
    return this->player_time;
}

