#include <ncurses.h>
#include <string>
#include <locale.h>

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
 * ゲームモード選択画面を表示する
 * @return ゲームモード
 */
const char *Game::printGameModeSelectionScreen()
{
    clear();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int ch;
    int selected = 0;
    int menu_num = 3;
    int max_y, max_x;
    std::string menu[menu_num];
    menu[0] = "Easy";
    menu[1] = "Normal";
    menu[2] = "Hard";

    getmaxyx(stdscr, max_y, max_x);

    while (1)
    {
        clear();
        for (int i = 0; i < menu_num; i++)
        {
            if (i == selected)
            {
                attron(A_REVERSE);
            }
            // 真ん中に表示させる
            mvprintw(max_y / 2 - menu_num / 2 + i, max_x / 2 - menu[i].length() / 2, menu[i].c_str());
            attroff(A_REVERSE);
        }
        refresh();

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            selected--;
            if (selected < 0)
            {
                selected = 0;
            }
            break;
        case KEY_DOWN:
            selected++;
            if (selected > menu_num - 1)
            {
                selected = menu_num - 1;
            }
            break;
        case '\n':
            switch (selected)
            {
            case 0:
                game_mode = "Easy";
                break;
            case 1:
                game_mode = "Normal";
                break;
            case 2:
                game_mode = "Hard";
                break;
            }
            return game_mode.c_str();
            break;
        }
    }
}