#include <stdio.h> // 後で削除 (for debug)
#include <ncurses.h>
#include <unistd.h>
#include "../include/CheckScreenSize.h"

ScreenSize getScreenSizeFromConfig()
{
  ScreenSize ScreenSize;
  ScreenSize.width = 800;
  ScreenSize.height = 600;
  return ScreenSize;
}

int checkScreenSize()
{
  ScreenSize ScreenSize = getScreenSizeFromConfig();
  initscr();

  return 0;
}
