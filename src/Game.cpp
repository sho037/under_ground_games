#include <ncurses.h>
#include <string>
#include <locale.h>

#include "../include/Game.hpp"
#include "../include/QuestionAndAnswer.hpp"

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

/**
 * 出力されるべき選択肢の数を返す
 * @param game_mode ゲームモード
 * @return 選択肢の数
*/
int getQuestionNum(std::string game_mode)
{
    if (game_mode == "Easy")
    {
        return 3;
    }
    else if (game_mode == "Normal")
    {
        return 5;
    }
    else if (game_mode == "Hard")
    {
        return 10;
    }
    else
    {
        fprintf(stderr, "program error: in getQuestionNum: game_modeが不正\n");
        exit(1);
    }
}

/**
 * ゲームを開始する
 * @return 0: 正常終了
 */
int Game::startGame()
{
    // 正解数を保存
    int correct_num = 0;

    // ゲームを開始(10問)
    for (int i = 0; i < 10; i++)
    {
        if (printQuestionScreen(game_name.c_str(), getQuestionNum(game_mode)))
        {
            correct_num++;
        }
    }

    // 結果を表示
    clear();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(max_y / 2, max_x / 2 - 5, "Result");
    mvprintw(max_y / 2 + 1, max_x / 2 - 5, "%d / 10", correct_num);
    refresh();
    getch();

    return correct_num;
}

