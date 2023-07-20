#include <ncurses.h>
#include <string>
#include <ctime>
#include "../include/Game.hpp"
#include "../include/Player.hpp"

/**
 * メニュー画面を表示させる
 *
 * @return 選択されたメニューの番号
 * @return 0: 終了
 * @return 1: ゲーム１を開始
 * @return 2: ゲーム２を開始
 * @return 10: スコア表示
 * @return 11: 設定画面表示
 */
int printMenu()
{
  int ch;
  int selected = 0;
  int menu_num = 5;
  int max_y, max_x;
  std::string menu[menu_num];
  menu[0] = "HTTPer";
  menu[1] = "Ubuntur";
  menu[2] = "Score";
  menu[3] = "Settings";
  menu[4] = "Exit";

  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
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
      endwin();
      return selected;
      break;
    }
  }
}

int UGGames()
{
  Game myGame;
  Player myPlayer;
  bool is_game = false;
  switch (printMenu())
  {
  case 0:
    myGame.setGameName("HTTPer");
    is_game = true;
    break;
  case 1:
    myGame.setGameName("Ubuntur");
    is_game = true;
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    return 0;
    break;
  default:
    return -501;
    break;
  }

  int correct_num = 0;

  if (is_game)
  {
    myGame.printGameModeSelectionScreen();
    clock_t start = clock();
    correct_num = myGame.startGame();
    clock_t end = clock();
    myPlayer.setPlayerTime((double)(end - start) / CLOCKS_PER_SEC);
    myPlayer.setPlayerCorrectAnswerCount(correct_num);
    myPlayer.printPlayerScore();
  }

  UGGames();

  return 0;
}