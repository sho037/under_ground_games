/**
 * @file ScreenSetting.h
 * @brief ncurses screen setting
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
int setScreenSize();