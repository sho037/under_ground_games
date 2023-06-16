/**
 * @file CheckScreenSize.h
 * @brief ncurses で画面サイズを取得する
 */

/**
 * 画面サイズを挿入する構造体
 */
typedef struct
{
  int width;
  int height;
} ScreenSize;

/**
 * 画面サイズを設定する
 */
int checkScreenSize();