#include <string>
#include <ncurses.h>
#include "../include/QuestionAndAnswer.hpp"
#include "../include/common/JsonData.hpp"

/**
 * 問題を表示する
 * 引数として与えられた問題数文のoutputを表示し、
 * その中から選択させる。正解を選択した場合はtrueを返す。
 * @param question_num 問題数
 * @return 正解したかどうか
*/
bool printQuestionScreen(const char *game_name, int question_num)
{
    JsonData json_data;
    int ch;
    int selected = 0;
    int max_y, max_x;
    struct question_data questions[question_num];

    for (int i = 0; i < question_num; i++)
    {
        questions[i] = json_data.getRandomQuestionData(game_name);
    }

    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, max_y, max_x);

    // 正解の問題を選ぶ
    int randn = rand() % question_num;
    std::string correct_question_id = questions[randn].id;
    std::string correct_question_question = questions[randn].question;

    // 問題を表示する
    while (1)
    {
        clear();
        for (int i = 0; i < question_num; i++)
        {
            if (i == selected)
            {
                attron(A_REVERSE);
            }
            // 真ん中に表示させる
            mvprintw(max_y / 2 - question_num / 2 + i, max_x / 2 - questions[i].output.length() / 2, questions[i].output.c_str());
            attroff(A_REVERSE);
        }
        // 下に正解の問題文を表示する
        mvprintw(max_y / 2 + question_num / 2 + question_num, max_x / 2 - correct_question_question.length() / 2, correct_question_question.c_str());
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
            if (selected > question_num - 1)
            {
                selected = question_num - 1;
            }
            break;
        case '\n':
            if (questions[selected].id == correct_question_id)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        default:
            break;
        }
    }
    

    return false;
}