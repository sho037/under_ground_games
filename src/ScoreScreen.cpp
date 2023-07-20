#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <string>

#include "../include/ScoreScreen.hpp"
#include "../include/common/JsonData.hpp"

/**
 * スコア画面を表示する
 */
void printScoreScreen()
{
    JsonData json_data;
    int ch;
    int selected = 0;
    int max_y, max_x;
    int score_num = 10;
    std::vector<struct score_data> scores = json_data.getScoreData("ScoreData");

    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, max_y, max_x);

    // スコアの降順にソートする
    std::sort(scores.begin(), scores.end(), [](const struct score_data &a, const struct score_data &b) {
        return a.score > b.score;
    });

    // スコアの数を10個にする
    if (scores.size() < score_num)
    {
        score_num = scores.size();
    }

    while (1)
    {
        clear();
        for (int i = 0; i < score_num; i++)
        {
            if (i == selected)
            {
                attron(A_REVERSE);
            }
            // 真ん中に表示させる name: ?? score: ??
            mvprintw(max_y / 2 - score_num / 2 + i, max_x / 2 - (scores[i].name.length() + 10) / 2,
                 (std::string(scores[i].name) + ": " + std::to_string(scores[i].score)).c_str());
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
            if (selected > score_num - 1)
            {
                selected = score_num - 1;
            }
            break;
        case 10:
            return;
        }
    }
}