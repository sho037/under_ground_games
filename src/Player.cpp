#include <string>
#include <ncurses.h>
#include "../include/Player.hpp"
#include "../include/common/JsonData.hpp"

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
 * プレイヤーの正解数を設定する
 */
void Player::setPlayerCorrectAnswerCount(int player_correct_answer_count)
{
    this->player_correct_answer_count = player_correct_answer_count;
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

/**
 * プレイヤーのスコアを計算する
*/
void Player::calculatePlayerScore()
{
    this->player_score = (this->player_correct_answer_count * 10000) - (this->player_time * 100000);
}

/**
 * プレイヤーのスコアを表示する
 */
void Player::printPlayerScore()
{
    clear();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    calculatePlayerScore();
    mvprintw(max_y / 2, max_x / 2 - 5, "Your score is %d", this->player_score);
    refresh();
    getch();
}

/**
 * プレイヤーのスコアを保存する
*/
void Player::savePlayerScore()
{
    JsonData json_data;
    json_data.writeScoreData("ScoreData", this->player_name.c_str(), this->player_score);
}
