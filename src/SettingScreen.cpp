#include <ncurses.h>
#include <string>
#include <ctime>
#include <jansson.h>
#include "../include/SettingScreen.hpp"

// コンストラクタ
SettingScreen::SettingScreen(/* args */)
{
    this->name = "Player";
}

// デストラクタ
SettingScreen::~SettingScreen()
{
}

/**
 * 設定画面を表示する
 * 名前を入力する
 * 入力した値はdata/SettingData.jsonに保存される
 */
void SettingScreen::printSettingScreen()
{
    clear();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int ch;
    int selected = 0;
    int menu_num = 2;
    int max_y, max_x;
    std::string menu[menu_num];
    std::string description = "Chose a selection";
    menu[0] = "Set name";
    menu[1] = "Go back";

    getmaxyx(stdscr, max_y, max_x);

    while (1)
    {
        clear();
        curs_set(0);
        // 何をするか表示する
        mvprintw(max_y / 2 - menu_num / 2 - 2, max_x / 2 - description.length() / 2, description.c_str());
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
                // 名前を入力する
                echo();
                curs_set(1);
                mvprintw(max_y / 2 - menu_num / 2 + selected, max_x / 2 - menu[selected].length() / 2 + menu[selected].length() + 1, ": ");
                refresh();
                char name[256];
                getstr(name);
                // 入力した名前を保存する
                this->name = name;
                break;
            case 1:
                // 戻る
                return;
            }
            break;
        }
    }
}

/**
 * 名前を取得する
*/
std::string SettingScreen::getName()
{
    return this->name;
}